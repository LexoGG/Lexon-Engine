// Application.cpp
#include "Application.h"
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
        {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
    };

    std::vector<uint32_t> indices = { 0, 1, 2, 2, 3, 0 }; // cuadrado con dos triángulos
    indexBuffer.create(context.getDevice(), context.getPhysicalDevice(), indices);



    std::cout << "[INFO] Vertices cargados: " << vertices.size() << std::endl;
    vertexBuffer.create(context.getDevice(), context.getPhysicalDevice(), vertices); // ✅ ANTES
    std::cout << "[DEBUG] VertexBuffer creado: " << (vertexBuffer.getBuffer() != VK_NULL_HANDLE) << std::endl;

    vertexBuffer.create(context.getDevice(), context.getPhysicalDevice(), vertices);






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





}

void Application::mainLoop() {
    int frameCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose()) {
        window.pollEvents();
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

    vertexBuffer.destroy(context.getDevice());
    syncObjects.cleanup(context);
    commandBuffers.cleanup(context);
    pipeline.cleanup(context);
    swapchain.cleanup(context);
    context.cleanup(window);
    window.cleanup();

}
