// Application.cpp
#include "Application.h"

void Application::run() {

    // Se crea la ventana
	initWindow();

    // Se inicializa la aplicacion y se crean los elementos necesarios
    initVulkan();

    // Bucle de trabajo una vez la aplicacion ha iniciado
    mainLoop();
    
    // Destruccion y limpieza de elementos antes del cierre de la aplicacion
    cleanup();
}

void Application::initWindow() {
    //Creacion de una ventana grafica 
    std::cout << "[!] Creando la ventana: " << std::endl;
    window.init();
}

void Application::initVulkan() {


    //createInstance
    std::cout << "[!] Creando instancia: " << std::endl;
    context.createInstance();

    //    setupDebugMessenger(); createSurface(); pickPhysicalDevice(); createLogicalDevice();
    // Creacion de objetos vulkan y dispositivos
    std::cout << "[!] Creando contexto: " << std::endl;
    context.init();

    //createSwapChain
    std::cout << "[!] Creando la cadena de intercambio (swapchain)" << std::endl;
    swapchain.init(context, window);  // 🔄 sin renderPass aún

    //        createRenderPass();    createDescriptorSetLayout();    createGraphicsPipeline();
    std::cout << "[!] Creando el descriptor set:" << std::endl;
    pipeline.init();// 🔄 crea el renderPass

    std::cout << "Creando los framebuffers" << std::endl;


    commandBuffers.init(); //createCommandPool

    depthbuffer.createDepthResources();
    swapchain.createFramebuffers();  // ✅ renderPass ya existe



    // 3 copias del mismo modelo
    loadermodel.loadModel("viking room", MODEL_PATH);








    textura.createTextureImage();
    textura.createTextureImageView();
    textura.createTextureSampler();

    std::cout << "[!] Creando buffer de vertices: "<<std::endl;
    vertexBuffer.createVertexBuffer();


    std::cout << "[!] Cargando vertices: " << std::endl;
    indexBuffer.createIndexBuffer();
    std::cout << "\t[INFO] Vertices cargados: " << LoaderModels::vertices.size() << std::endl;
    std::cout << "\t[INFO] Indices cargados: " << LoaderModels::indices.size() << std::endl;

    uniformbuffer.createUniformBuffers();

    descriptors.createDescriptorPool();
    descriptors.createDescriptorSets();

    std::cout << "Creando el buffer de comandos" << std::endl;
    commandBuffers.createCommandBuffers();

    std::cout << "Creando los semaforos" << std::endl;
    syncObjects.createSyncObjects();


    std::cout << "Inicializando ImGui" << std::endl;
    ImGuiVulkan::Init(context, swapchain, pipeline.getRenderPass());

    offscreenRenderer.Init();
}


void Application::mainLoop() {
    int frameCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose()) {

        InitImgui();
        CheckInputs();
        window.pollEvents();
        

        syncObjects.drawFrame();


        // === CÁLCULO DEL DELTA TIME ===
        static double lastTime = glfwGetTime();
        double currentTime = glfwGetTime();
        deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;



        frameCount++;
    
    }

    vkDeviceWaitIdle(VulkanContext::getDevice());


}


void Application::cleanup() {
    offscreenRenderer.Cleanup();
    ///
    swapchain.cleanup(context);
    ///
    pipeline.cleanup(context);

    ImGuiVulkan::Shutdown(VulkanContext::getDevice());


    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroyBuffer(VulkanContext::getDevice(), UniformBuffer::getuniformBuffers()[i], nullptr);
        vkFreeMemory(VulkanContext::getDevice(), UniformBuffer::getuniformBuffersMemory()[i], nullptr);
    }

    ///
    descriptors.destroyDescriptorPool();//Testeoaqui
    descriptors.destroyDescriptorSets();
    ///
    indexBuffer.destroy(VulkanContext::getDevice());
    vertexBuffer.destroy(); ///// vkDestroyBuffer
    ///
    commandBuffers.cleanup(context);
    //
    syncObjects.cleanup(context);
    //
    context.cleanup();//3

    //
    window.cleanup();

}

void Application::CheckInputs() {

    if (glfwGetKey(Window::getGLFWwindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(Window::getGLFWwindow(), GLFW_TRUE);
    }

}



// Definición del miembro estático
OffscreenRenderer Application::offscreenRenderer;
float Application::deltaTime;
