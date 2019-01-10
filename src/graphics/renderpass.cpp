#include "graphics/renderpass.hpp"

void RenderPass::create(vk::Device device, vk::Format swapChainImageFormat) {
	vk::AttachmentDescription colorAttachment(
	{}, swapChainImageFormat, vk::SampleCountFlagBits::e1,
		vk::AttachmentLoadOp::eClear, vk::AttachmentStoreOp::eStore,
		vk::AttachmentLoadOp::eDontCare, vk::AttachmentStoreOp::eDontCare,
		vk::ImageLayout::eUndefined, vk::ImageLayout::ePresentSrcKHR
	);

	vk::AttachmentReference colorAttachmentRef(0, vk::ImageLayout::eColorAttachmentOptimal);

	vk::SubpassDescription subpass({}, vk::PipelineBindPoint::eGraphics, 0, nullptr, 1, &colorAttachmentRef);

	vk::SubpassDependency dependency(
		VK_SUBPASS_EXTERNAL, 0,
		vk::PipelineStageFlagBits::eColorAttachmentOutput, vk::PipelineStageFlagBits::eColorAttachmentOutput,
		{}, vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite
	);

	vk::RenderPassCreateInfo renderPassInfo({}, 1, &colorAttachment, 1, &subpass, 1, &dependency);

	device.createRenderPass(&renderPassInfo, nullptr, &renderPass);

	this->device = device;
}

RenderPass::operator vk::RenderPass() const {
	return renderPass;
}

void RenderPass::destroy() {
	device.destroyRenderPass(renderPass, nullptr);
}
