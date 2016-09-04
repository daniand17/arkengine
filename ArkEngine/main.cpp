#include <string>
#include <iostream>

#include "VkRenderer.h"
#include "Shared.h"

int main(int argc, char ** argv)
{

	VkRenderer renderer;

	//renderer.CreateArkWindow(512, 512, "New Ark Window");

	
	return 0;
}

//VkDevice device = renderer.GetDevice();
//VkQueue queue = renderer.GetQueue();

//VkFence fence;
//VkFenceCreateInfo fenceCreateInfo{};
//fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
//vkCreateFence(device, &fenceCreateInfo, NULL, &fence);

//VkSemaphore semaphore;
//VkSemaphoreCreateInfo semaphoreCreateInfo{};
//semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
//vkCreateSemaphore(device, &semaphoreCreateInfo, NULL /* TODO mem alloc */, &semaphore);

//VkCommandPool commandPool;
//VkCommandPoolCreateInfo poolCreateInfo{};
//poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
//poolCreateInfo.queueFamilyIndex = renderer.GetQueueFamilyIndex();
//poolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
//vkCreateCommandPool(device, &poolCreateInfo, NULL /* TODO mem alloc */, &commandPool);

//VkCommandBuffer commandBuffers[2];
//VkCommandBufferAllocateInfo commandBufferAllocateInfo{};
//commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//commandBufferAllocateInfo.commandPool = commandPool;
//commandBufferAllocateInfo.commandBufferCount = 2;
//commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

//vkAllocateCommandBuffers(device, &commandBufferAllocateInfo, commandBuffers);

//{
//	VkCommandBufferBeginInfo beginInfo{};
//	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

//	VkCommandBuffer & commandBuffer = commandBuffers[0];

//	vkBeginCommandBuffer(commandBuffer, &beginInfo); // can start recording commands to gpu once this is called

//	// command buffers are sort of a 'to do' list for the GPU to execute
//	// pipeline barries: which stage of the pipeline "needs to be done" before continuing execution
//	vkCmdPipelineBarrier(
//		commandBuffer,
//		VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
//		VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
//		0,
//		0, NULL,
//		0, NULL,
//		0, NULL);

//	// TODO put commands here
//	// anything starting with vkCmd is something that is sent to the GPU

//	// Need to set viewport per command viewport (set every time you render a mesh, etc)
//	VkViewport viewport{};
//	viewport.maxDepth = 1.0f;
//	viewport.minDepth = 0.0f;
//	viewport.width = 512;
//	viewport.height = 512;
//	viewport.x = 0;
//	viewport.y = 0;
//	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

//	vkEndCommandBuffer(commandBuffer);				// compiles command buffer into executable onto gpu
//}

//{
//	VkCommandBuffer & commandBuffer = commandBuffers[1];
//	VkCommandBufferBeginInfo beginInfo{};
//	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

//	vkBeginCommandBuffer(commandBuffers[1], &beginInfo); // can start recording commands to gpu once this is called

//	// Need to set viewport per command viewport (set every time you render a mesh, etc)
//	VkViewport viewport{};
//	viewport.maxDepth = 1.0f;
//	viewport.minDepth = 0.0f;
//	viewport.width = 512;
//	viewport.height = 512;
//	viewport.x = 0;
//	viewport.y = 0;
//	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

//	vkEndCommandBuffer(commandBuffer);				// compiles command buffer into executable onto gpu
//}

//// This is submitted....
//{
//	// Submits command buffers to queue
//	VkSubmitInfo submitInfo{};
//	submitInfo.sType				= VK_STRUCTURE_TYPE_SUBMIT_INFO;
//	submitInfo.commandBufferCount	= 1;
//	submitInfo.pCommandBuffers		= &commandBuffers[0];	// list of command buffers
//	submitInfo.signalSemaphoreCount = 1;
//	submitInfo.pSignalSemaphores	= &semaphore;
//	vkQueueSubmit(queue, 1, &submitInfo, NULL);
//}
//// Then this is submitted... but by the time we reach the fragment shader, it will wait for the first command buffer to be fully executed
//// This ensures none of the work on the second pipeline is finished before the work on the first one.. if you want it to wait earlier, set an earlier bit
//{
//	// Submits command buffers to queue
//	VkPipelineStageFlags flags[]	{ VK_PIPELINE_STAGE_ALL_COMMANDS_BIT };
//	VkSubmitInfo submitInfo{};
//	submitInfo.sType				= VK_STRUCTURE_TYPE_SUBMIT_INFO;
//	submitInfo.commandBufferCount	= 1;
//	submitInfo.pCommandBuffers		= &commandBuffers[1];	// list of command buffers
//	submitInfo.waitSemaphoreCount	= 1;		// size of flags
//	submitInfo.pWaitSemaphores		= &semaphore;
//	submitInfo.pWaitDstStageMask	= flags;		// wehre in the pipeline we will wait for the semaphore to signal
//	vkQueueSubmit(queue, 1, &submitInfo, NULL);
//}

//ErrorCheck(vkWaitForFences(device, 1, &fence, VK_TRUE /* All fences need to be set before we continue*/, /* in ns */ UINT64_MAX));

//vkQueueWaitIdle(queue); // waits for queue to be idle (bad/slow for now)

//vkDestroyCommandPool(device, commandPool, NULL /* TODO mem allloc */);
//vkDestroyFence(device, fence, NULL);
//vkDestroySemaphore(device, semaphore, NULL);