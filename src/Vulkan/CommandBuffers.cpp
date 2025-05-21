#include "CommandBuffers.h"

#include <stdexcept>
#include <iostream>

void CommandBuffers::init(VulkanContext& context, Swapchain& swapchain) {
    createCommandPool(context);
    createCommandBuffers(context);

    // Record initial commands for each swapchain image
    for (size_t i = 0; i < commandBuffers.size(); i++) {

    }
}

void CommandBuffers::cleanup(VulkanContext& context) {
    if (commandPool != VK_NULL_HANDLE) {
        vkDestroyCommandPool(context.getDevice(), commandPool, nullptr);
    }
}

VkCommandBuffer CommandBuffers::getCommandBuffer(size_t index) const {
    return commandBuffers[index];
}

void CommandBuffers::createCommandPool(VulkanContext& context) {
    auto queueFamilyIndices = context.findQueueFamilies(context.getPhysicalDevice());

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(context.getDevice(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }
}

void CommandBuffers::createCommandBuffers(VulkanContext& context) {
    commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

    if (vkAllocateCommandBuffers(context.getDevice(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void CommandBuffers::recordCommandBuffer(VulkanContext& context, Swapchain& swapchain, Pipeline& pipeline, VertexBuffer& vertexBuffer, uint32_t imageIndex, uint32_t frameIndex) {

    VkCommandBuffer commandBuffer = commandBuffers[frameIndex];

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    auto renderPass = pipeline.getRenderPass();
    auto framebuffer = swapchain.getFramebuffers()[imageIndex];

    if (renderPass == VK_NULL_HANDLE) {
        throw std::runtime_error("RenderPass is VK_NULL_HANDLE in recordCommandBuffer");
    }
    if (framebuffer == VK_NULL_HANDLE) {
        throw std::runtime_error("Framebuffer is VK_NULL_HANDLE in recordCommandBuffer");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPass;
    renderPassInfo.framebuffer = framebuffer;
    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = swapchain.getExtent();

    VkClearValue clearColor = { { 0.0f, 0.0f, 0.0f, 1.0f } };
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    // Bind pipeline
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.getGraphicsPipeline());

    vertexBuffer.bind(commandBuffer);



    // Viewport
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(swapchain.getExtent().width);
    viewport.height = static_cast<float>(swapchain.getExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    // Scissor
    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = swapchain.getExtent();
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

    vertexBuffer.bind(commandBuffer);




    // ¡Dibuja!
    vkCmdDraw(commandBuffer, vertexBuffer.getVertexCount(), 1, 0, 0);

    vkCmdEndRenderPass(commandBuffer);

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }



}


