// Application.h
#pragma once
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_raii.hpp>


#include "Window.h"
#include "../Vulkan/VulkanContext.h"
#include "../Vulkan/Swapchain.h"
#include "../Vulkan/Pipeline.h"
#include "../Vulkan/CommandBuffers.h"
#include "../Vulkan/SyncObjects.h"
#include "../Vulkan/VertexBuffer.h"
#include "../Vulkan/IndexBuffer.h"
#include "../Vulkan/UniformBuffer.h"
#include "../Vulkan/DescriptorPool.h"
#include "../Vulkan/DephtBuffer.h"  
#include "../Math/MatrixCalc.h"
#include "../Renderer/OffscreenRenderer.h"

#include "../Assets/Square.h"
#include "../Assets/Textures.h"
#include "../ImGui/ImGuiVulkan.h"
#include "../Core/ImguiHUD.h"
#include "Globals.h"
#include "imgui.h"

#include <stdexcept>
#include <iostream>
#include <chrono>



class Application {
public:
    void run();
    static OffscreenRenderer& GetOffscreenRenderer() { return offscreenRenderer; }
    static float deltaTime;


private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
    void CheckInputs();


    Window window;
    VulkanContext context;
    Swapchain swapchain;
    Pipeline pipeline;
    CommandBuffers commandBuffers;
    SyncObjects syncObjects;
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;
    UniformBuffer uniformbuffer;
    Descriptors descriptors;
	Textures textura;   
    DepthBuffer depthbuffer;
    LoaderModels loadermodel;

    static OffscreenRenderer offscreenRenderer;


};
