#include "graphics/graphics_pipeline.hpp"

void GraphicsPipeline::create(vk::Device device, vk::Extent2D swapChainExtent, vk::RenderPass renderPass) {
	ShaderModule vertShaderModule = ShaderModule();
	ShaderModule fragShaderModule = ShaderModule();

	vertShaderModule.create(device, "bin/shader/vert.spv", vk::ShaderStageFlagBits::eVertex);
	fragShaderModule.create(device, "bin/shader/frag.spv", vk::ShaderStageFlagBits::eFragment);

	vk::PipelineShaderStageCreateInfo shaderStages[] = { vertShaderModule.getStageCreateInfo(), fragShaderModule.getStageCreateInfo() };

	vk::PipelineInputAssemblyStateCreateInfo inputAssembly({}, vk::PrimitiveTopology::eTriangleList, VK_FALSE);

	vk::Viewport viewport(
		0.0f, 0.0f,
		(float)swapChainExtent.width, (float)swapChainExtent.height,
		0.0f, 1.0f
	);

	vk::Rect2D scissor({ 0, 0 }, swapChainExtent);
	vk::PipelineViewportStateCreateInfo viewportState({}, 1, &viewport, 1, &scissor);
	vk::PipelineRasterizationStateCreateInfo rasterizer({}, VK_FALSE, VK_FALSE, vk::PolygonMode::eFill, vk::CullModeFlagBits::eBack, vk::FrontFace::eClockwise, VK_FALSE, 0.0f, 0.0f, 0.0f, 1.0f);

	vk::PipelineMultisampleStateCreateInfo multisampling({}, vk::SampleCountFlagBits::e1, VK_FALSE, 1.0f, nullptr, VK_FALSE, VK_FALSE);
	
	vk::PipelineColorBlendAttachmentState colorBlendAttachment(
		VK_FALSE,
		vk::BlendFactor::eOne, vk::BlendFactor::eZero, vk::BlendOp::eAdd,
		vk::BlendFactor::eOne, vk::BlendFactor::eZero, vk::BlendOp::eAdd,
		{ vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA }
	);

	vk::PipelineColorBlendStateCreateInfo colorBlending({}, VK_FALSE, vk::LogicOp::eCopy, 1, &colorBlendAttachment, { {0.0f, 0.0f, 0.0f, 0.0f} });

	vk::DynamicState dynamicStates[] = {
		vk::DynamicState::eViewport,
		vk::DynamicState::eLineWidth
	};
	vk::PipelineDynamicStateCreateInfo dynamicState({}, 2, dynamicStates);
	vk::PipelineLayoutCreateInfo pipelineLayoutInfo({}, 0, nullptr, 0, nullptr);

	device.createPipelineLayout(&pipelineLayoutInfo, nullptr, &layout);

	// TODO: move this into the shader namespace if possible

	auto bindingDescription = Vertex::getBindingDescription();
	auto attributeDescriptions = Vertex::getAttributeDescriptions();
	vk::PipelineVertexInputStateCreateInfo vertexInputInfo(
		{},
		1, &bindingDescription,
		static_cast<uint32_t>(attributeDescriptions.size()), attributeDescriptions.data()
	);

	vk::GraphicsPipelineCreateInfo pipelineInfo({}, 2, shaderStages, &vertexInputInfo, &inputAssembly, nullptr, &viewportState, &rasterizer, &multisampling, nullptr, &colorBlending, nullptr, layout, renderPass, 0, nullptr, -1);
	auto pipelineCache = device.createPipelineCache(vk::PipelineCacheCreateInfo());

	pipeline = device.createGraphicsPipeline(pipelineCache, pipelineInfo);

	fragShaderModule.destroy();
	vertShaderModule.destroy();

	this->device = device;

}

GraphicsPipeline::operator vk::Pipeline() const {
	return pipeline;
}

void GraphicsPipeline::destroy() {
	device.destroyPipeline(pipeline, nullptr);
	device.destroyPipelineLayout(layout, nullptr);
}
