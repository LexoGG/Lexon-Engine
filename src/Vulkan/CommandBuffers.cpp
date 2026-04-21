#include "CommandBuffers.h"
#include <stdexcept>
#include "../Core/Application.h"


void CommandBuffers::init() {
    createCommandPool();


}

void CommandBuffers::cleanup(VulkanContext& context) {

        vkDestroyCommandPool(VulkanContext::getDevice(), commandPool, nullptr);
 
}

VkCommandBuffer CommandBuffers::getCommandBuffer(size_t index) {
    return commandBuffers[index];
}

void CommandBuffers::createCommandPool() {
    QueueFamilyIndices queueFamilyIndices = Swapchain::findQueueFamilies(VulkanContext::getPhysicalDevice());

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(VulkanContext::getDevice(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics command pool!");
    }
}

void CommandBuffers::createCommandBuffers() {
    commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

    if (vkAllocateCommandBuffers(VulkanContext::getDevice(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void CommandBuffers::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = Pipeline::getRenderPass();
    renderPassInfo.framebuffer = Swapchain::getIndexFramebuffers(imageIndex);
    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = Swapchain::getExtent();

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };
    clearValues[1].depthStencil = { 1.0f, 0 };

    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();


    ////
// =============================================
//  1. RENDER ESCENA AL OFFSCREEN (Viewport)
    OffscreenRenderer& offscreen = Application::GetOffscreenRenderer();
    offscreen.BeginRenderPass(commandBuffer);

    // === TU CÓDIGO DE DIBUJO DE LA ESCENA (sin ImGui) ===
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, Pipeline::getGraphicsPipeline());

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(offscreen.GetWidth());     // ← CAMBIADO (importante)
    viewport.height = static_cast<float>(offscreen.GetHeight());    // ← CAMBIADO (importante)
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = { offscreen.GetWidth(), offscreen.GetHeight() }; // ← CAMBIADO
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

    VkBuffer vertexBuffers[] = { VertexBuffer::getBuffer() };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

    vkCmdBindIndexBuffer(commandBuffer, IndexBuffer::getIndexVertexCount(), 0, VK_INDEX_TYPE_UINT32);

    VkDescriptorSet* descriptorSet =
        Descriptors::getdescriptorsetsIndex(SyncObjects::getCurrentFrame());

    vkCmdBindDescriptorSets(
        commandBuffer,
        VK_PIPELINE_BIND_POINT_GRAPHICS,
        Pipeline::getPipelineLayout(),
        0,
        1,
        descriptorSet, 
        0,
        nullptr
    );

    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(LoaderModels::indices.size()), 1, 0, 0, 0);

    // Fin del dibujo de la escena
    offscreen.EndRenderPass(commandBuffer);

    // =============================================
    //  2. RENDER SWAPCHAIN (solo ImGui + fondo del editor)

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    ImGuiVulkan::RenderDrawData(commandBuffer);

    vkCmdEndRenderPass(commandBuffer);



    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}


VkCommandPool CommandBuffers::commandPool = VK_NULL_HANDLE;
std::vector<VkCommandBuffer> CommandBuffers::commandBuffers;