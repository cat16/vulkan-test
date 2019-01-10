#pragma once

#include <vector>

#include "graphics/vertex.hpp"

namespace Game {
	const int WIDTH = 800;
	const int HEIGHT = 600;

	const int MAX_FRAMES_IN_FLIGHT = 2;

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation",
	};

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	#ifdef NDEBUG
	const bool enableValidationLayers = false;
	#else
	const bool enableValidationLayers = true;
	#endif

	const std::vector<Vertex> vertices = {
		{ { -0.5f, -0.5f },{ 1.0f, 0.1f, 0.0f } },
		{ { +0.5f, -0.5f },{ 0.5f, 0.0f, 1.0f } },
		{ { -0.5f, +0.5f },{ 0.5f, 0.5f, 0.0f } },
		{ { +0.5f, +0.5f },{ 1.0f, 0.1f, 0.0f } },
		{ { -0.5f, +0.5f },{ 0.5f, 0.5f, 0.0f } },
		{ { +0.5f, -0.5f },{ 0.5f, 0.0f, 1.0f } },
		{ { -0.5f, -0.5f },{ 1.0f, 0.1f, 0.0f } },
		{ { +0.0f, -1.0f },{ 0.5f, 0.5f, 0.0f } },
		{ { +0.5f, -0.5f },{ 0.5f, 0.0f, 1.0f } }
	};
}
