#pragma once

#define GLFW_DLL
#include "GLFW/glfw3.h"

#include "graphics/vulkan.hpp"

class Window {
public:
	void create();
	operator GLFWwindow*() const;
	void drawFrame();
	void waitForIdle();
	void destroy();
private:
	Vulkan vulkan;
	GLFWwindow * window;

	bool framebufferResized = false;

	void initWindow();

	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
};
