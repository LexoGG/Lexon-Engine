#include "ImGuiVulkan.h"

#include "../Core/Window.h"
#include "../Vulkan/VulkanContext.h"
#include "../Vulkan/Swapchain.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"

#include <algorithm>
#include <stdexcept>

namespace {

VkDescriptorPool g_DescriptorPool = VK_NULL_HANDLE;

void CreateDescriptorPool(VkDevice device) {
    constexpr VkDescriptorPoolSize poolSizes[] = {
        { VK_DESCRIPTOR_TYPE_SAMPLER,                1000 },
        { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
        { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,          1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,        1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,   1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,   1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,       1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,       1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
        { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,     1000 },
    };

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    poolInfo.maxSets = 1000 * static_cast<uint32_t>(std::size(poolSizes));
    poolInfo.poolSizeCount = static_cast<uint32_t>(std::size(poolSizes));
    poolInfo.pPoolSizes = poolSizes;

    if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &g_DescriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("ImGui: failed to create descriptor pool");
    }
}

}  // namespace

namespace ImGuiVulkan {

void Init(VulkanContext& context, const Swapchain& swapchain, VkRenderPass renderPass) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForVulkan(Window::getGLFWwindow(), true);

    VkDevice device = VulkanContext::getDevice();
    CreateDescriptorPool(device);

    auto queueFamilies = context.findQueueFamilies(context.getPhysicalDevice());
    const uint32_t imageCount = static_cast<uint32_t>(swapchain.getFramebuffers().size());
    const uint32_t minImages = std::max(2u, imageCount);

    ImGui_ImplVulkan_InitInfo initInfo{};
    initInfo.ApiVersion = VK_API_VERSION_1_0;
    initInfo.Instance = context.getInstance();
    initInfo.PhysicalDevice = context.getPhysicalDevice();
    initInfo.Device = device;
    initInfo.QueueFamily = queueFamilies.graphicsFamily.value();
    initInfo.Queue = context.getGraphicsQueue();
    initInfo.DescriptorPool = g_DescriptorPool;
    initInfo.DescriptorPoolSize = 0;
    initInfo.MinImageCount = minImages;
    initInfo.ImageCount = std::max(minImages, imageCount);
    initInfo.PipelineCache = VK_NULL_HANDLE;
    initInfo.PipelineInfoMain.RenderPass = renderPass;
    initInfo.PipelineInfoMain.Subpass = 0;
    initInfo.PipelineInfoMain.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    initInfo.UseDynamicRendering = false;
    initInfo.Allocator = nullptr;
    initInfo.CheckVkResultFn = nullptr;

    ImGui_ImplVulkan_Init(&initInfo);
}

void Shutdown(VkDevice device) {
    ImGui_ImplVulkan_Shutdown();

    if (g_DescriptorPool != VK_NULL_HANDLE) {
        vkDestroyDescriptorPool(device, g_DescriptorPool, nullptr);
        g_DescriptorPool = VK_NULL_HANDLE;
    }

    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void BeginFrame() {
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void EndFrame() {
    ImGui::Render();
}

void RenderDrawData(VkCommandBuffer commandBuffer) {
    ImDrawData* drawData = ImGui::GetDrawData();
    if (drawData != nullptr) {
        ImGui_ImplVulkan_RenderDrawData(drawData, commandBuffer, VK_NULL_HANDLE);
    }
}

void NotifySwapchainImageCount(uint32_t imageCount) {
    const uint32_t safeCount = std::max(1u, imageCount);
    ImGui_ImplVulkan_SetMinImageCount(std::max(2u, safeCount));
}

}  // namespace ImGuiVulkan
