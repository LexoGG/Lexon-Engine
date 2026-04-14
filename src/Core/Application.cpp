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


    textura.createTextureImage();
    textura.createTextureImageView();
    textura.createTextureSampler();

    loadermodel.loadModel();

    std::cout << "[!] Creando buffer de vertices: "<<std::endl;
    vertexBuffer.createVertexBuffer();
    

    std::cout << "[!] Cargando vertices: " << std::endl;
    indexBuffer.createIndexBuffer();
    std::cout << "\t[INFO] Vertices cargados: " << LoaderModels::vertices.size() << std::endl;

    uniformbuffer.createUniformBuffers();

    descriptors.createDescriptorPool();
    descriptors.createDescriptorSets();

    std::cout << "Creando el buffer de comandos" << std::endl;
    commandBuffers.createCommandBuffers();

    std::cout << "Creando los semaforos" << std::endl;
    syncObjects.createSyncObjects();

    std::cout << "Inicializando ImGui" << std::endl;
    ImGuiVulkan::Init(context, swapchain, pipeline.getRenderPass());
}


void Application::mainLoop() {
    int frameCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose()) {


        CheckInputs();
        window.pollEvents();
        syncObjects.drawFrame();
        InitImgui();

        frameCount++;
    
    }

    vkDeviceWaitIdle(VulkanContext::getDevice());
}


void Application::cleanup() {
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
    descriptors.destroyDescriptorPool();
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

    if (glfwGetKey(Window::getGLFWwindow(), GLFW_KEY_E) == GLFW_PRESS) {

        unsigned imax = unsigned(LoaderModels::vertices.size());

        for (unsigned i = 0; i < imax; i++) {           // ← aquí estaba el error
            ImpulsoejeY(LoaderModels::vertices[i].pos, -0.001f);
        }


        //UniformBuffer::CameraPositionInit[2] = UniformBuffer::CameraPositionInit[2] +  0.001f;
    }

    if (glfwGetKey(Window::getGLFWwindow(), GLFW_KEY_Q) == GLFW_PRESS) {

        unsigned imax = unsigned(LoaderModels::vertices.size());

        for (unsigned i = 0; i < imax; i++) {
            ImpulsoejeY(LoaderModels::vertices[i].pos, 0.001f);
        }

        //UniformBuffer::CameraPositionInit[2] = UniformBuffer::CameraPositionInit[2] - 0.001f;
    }

    if (glfwGetKey(Window::getGLFWwindow(), GLFW_KEY_A) == GLFW_PRESS) {

        glm::vec3 directionmove = (glm::vec3(0.0f, 1.0f, 0.0f) / TamanoVector(UniformBuffer::CameraDirectionInit)) * (glm::vec3(0.0f, -0.001f,0.0f));
        UniformBuffer::CameraPositionInit[1] = UniformBuffer::CameraPositionInit[1] + directionmove[1];
    }

    if (glfwGetKey(Window::getGLFWwindow(), GLFW_KEY_D) == GLFW_PRESS) {
        UniformBuffer::CameraPositionInit[1] = UniformBuffer::CameraPositionInit[1] + 0.001f;
    }

    if (glfwGetKey(Window::getGLFWwindow(), GLFW_KEY_W) == GLFW_PRESS) {
        glm::vec3 directionmove = (UniformBuffer::CameraDirectionInit / TamanoVector(UniformBuffer::CameraDirectionInit)) * glm::vec3(0.001f, 0.0f, 0.0f);
        UniformBuffer::CameraPositionInit = UniformBuffer::CameraPositionInit + directionmove;
    }

    if (glfwGetKey(Window::getGLFWwindow(), GLFW_KEY_S) == GLFW_PRESS) {
        UniformBuffer::CameraPositionInit[0] = UniformBuffer::CameraPositionInit[0] - 0.001f;
    }







};


