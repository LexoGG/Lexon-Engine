// Application.h
#pragma once

#include "Window.h"
#include "../Vulkan/VulkanContext.h"
#include "../Vulkan/Swapchain.h"
#include "../Vulkan/Pipeline.h"
#include "../Vulkan/CommandBuffers.h"
#include "../Vulkan/SyncObjects.h"
#include "../Vulkan/VertexBuffer.h"
#include "../Vulkan/IndexBuffer.h"


class Application {
public:
    void run();
    IndexBuffer indexBuffer;


private:
    void init();
    void mainLoop();
    void cleanup();

    Window window;
    VulkanContext context;
    Swapchain swapchain;
    Pipeline pipeline;
    CommandBuffers commandBuffers;
    SyncObjects syncObjects;
    VertexBuffer vertexBuffer;


};
