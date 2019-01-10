#include "graphics/shader.hpp"

void ShaderModule::create(vk::Device device, const std::string& filename, vk::ShaderStageFlagBits stage) {
	auto code = Util::readFile(filename);
	vk::ShaderModuleCreateInfo createInfo({}, code.size(), reinterpret_cast<const uint32_t*>(code.data()));

	device.createShaderModule(&createInfo, nullptr, &module);


	stageCreateInfo = vk::PipelineShaderStageCreateInfo({}, stage, module, "main");

	this->device = device;
}

vk::PipelineShaderStageCreateInfo ShaderModule::getStageCreateInfo() {
	return stageCreateInfo;
}

void ShaderModule::destroy() {
	device.destroy(module, nullptr);
}