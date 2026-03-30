// Application.cpp
#include "Application.h"
#include "../ImGui/ImGuiVulkan.h"
#include "imgui.h"
#include <stdexcept>
#include <iostream>
#include <chrono>




void Application::run() {
    // Se inicializa la aplicacion y se crean los elementos necesarios
    init();

    // Bucle de trabajo una vez la aplicacion ha iniciado
    mainLoop();
    
    // Destruccion y limpieza de elementos antes del cierre de la aplicacion
    cleanup();
}

void Application::init() {

    //Creacion de una ventana grafica 
    std::cout << "Creando la ventana" << std::endl;
    window.init();

    // Creacion de objetos vulkan y dispositivos
    std::cout << "Creando contexto" << std::endl;
    context.init(window);


    const std::vector<Vertex> vertices = {
        //Posicion en -1,1 de la pantalla y color en RGB
        {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}

    };

    std::vector<uint32_t> indices = { 0, 1, 2, 2, 3, 0 }; // cuadrado con dos triángulos
    indexBuffer.create(context.getDevice(), context.getPhysicalDevice(), indices);



    std::cout << "[INFO] Vertices cargados: " << vertices.size() << std::endl;
    vertexBuffer.create(context.getDevice(), context.getPhysicalDevice(), vertices);
    std::cout << "[DEBUG] VertexBuffer creado: " << (vertexBuffer.getBuffer() != VK_NULL_HANDLE) << std::endl;






    std::cout << "Creando la cadena de intercambio (swapchain)" << std::endl;
    swapchain.init(context, window);  // 🔄 sin renderPass aún

    std::cout << "Creando la pipeline grafica" << std::endl;
    pipeline.init(context, swapchain);  // 🔄 crea el renderPass

    std::cout << "Creando los framebuffers" << std::endl;
    swapchain.createFramebuffers(context, pipeline.getRenderPass());  // ✅ renderPass ya existe





    std::cout << "Creando el buffer de comandos" << std::endl;
    commandBuffers.init(context, swapchain); // ✅ DESPUÉS de que el buffer exista

    std::cout << "Creando los semaforos" << std::endl;
    syncObjects.init(context);

    std::cout << "Inicializando ImGui" << std::endl;
    ImGuiVulkan::Init(window, context, swapchain, pipeline.getRenderPass());
}

void Application::mainLoop() {
    int frameCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose()) {
        window.pollEvents();

        ImGuiVulkan::BeginFrame();

        // Ancla la demo al borde izquierdo del viewport (misma ventana GLFW).
        // SetNext* afecta solo a la siguiente ventana -> ShowDemoWindow().
        static bool demoAbierta = true;
        {
            const ImGuiIO& io = ImGui::GetIO();
            const float anchoPanel = 520.f;
            ImGui::SetNextWindowPos(ImVec2(0.f, 0.f), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(anchoPanel, io.DisplaySize.y), ImGuiCond_Always);
        }
        ImGui::ShowDemoWindow(&demoAbierta);
        static bool ventanaSaludoAbierta = true;
        if (ventanaSaludoAbierta) {
            if (ImGui::Begin("Ventana", &ventanaSaludoAbierta)) {
                ImGui::Text("Hola");
            }
            ImGui::End();
        }

        ImGuiVulkan::EndFrame();

        syncObjects.drawFrame(context, swapchain, pipeline, commandBuffers, vertexBuffer, indexBuffer, window, pipeline.getRenderPass());

        frameCount++;

        auto currentTime = std::chrono::high_resolution_clock::now();
        float elapsed = std::chrono::duration<float>(currentTime - startTime).count();

        if (elapsed >= 1.0f) {
            std::cout << "FPS: " << frameCount << std::endl;
            frameCount = 0;
            startTime = currentTime;
        }
    }

    vkDeviceWaitIdle(context.getDevice());
}

void Application::cleanup() {

    ImGuiVulkan::Shutdown(context.getDevice());

    indexBuffer.destroy(context.getDevice());
    syncObjects.cleanup(context);
    commandBuffers.cleanup(context);
    pipeline.cleanup(context);
    
    swapchain.cleanup(context);

    vertexBuffer.destroy(context.getDevice()); ///// 1 2
    context.cleanup(window);//3
    window.cleanup();

}
