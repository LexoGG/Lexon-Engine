// Application.cpp
#include "Application.h"
#include <stdexcept>
#include <iostream>
#include <chrono>




void Application::run() {
    init();
    mainLoop();
    cleanup();
}

void Application::init() {

    std::cout << "Creando la ventana" << std::endl;
    window.init();

    std::cout << "Creando contexto" << std::endl;
    context.init(window);


    std::vector<Vertex> vertices = {
        {{ 0.0f, -0.5f }, { 1.0f, 0.0f, 0.0f }},
        {{ 0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f }},
        {{-0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f }}
    };

    std::cout << "[INFO] Vertices cargados: " << vertices.size() << std::endl;
    vertexBuffer.create(context.getDevice(), context.getPhysicalDevice(), vertices); // ✅ ANTES
    std::cout << "[DEBUG] VertexBuffer creado: " << (vertexBuffer.getBuffer() != VK_NULL_HANDLE) << std::endl;

    


    std::cout << "Creando la cadena de intercambio (swapchain)" << std::endl;
    swapchain.init(context, window);  // 🔄 sin renderPass aún

    std::cout << "Creando la pipeline gráfica" << std::endl;
    pipeline.init(context, swapchain);  // 🔄 crea el renderPass

    std::cout << "Creando los framebuffers" << std::endl;
    swapchain.createFramebuffers(context, pipeline.getRenderPass());  // ✅ renderPass ya existe





    std::cout << "Creando el buffer de comandos" << std::endl;
    commandBuffers.init(context, swapchain); // ✅ DESPUÉS de que el buffer exista

    std::cout << "Creando los semáforos" << std::endl;
    syncObjects.init(context);





}


void Application::mainLoop() {
    int frameCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose()) {
        window.pollEvents();
        syncObjects.drawFrame(context, swapchain, pipeline, commandBuffers, vertexBuffer, window, pipeline.getRenderPass());

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
