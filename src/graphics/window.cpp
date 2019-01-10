#include "graphics/window.hpp"

void Window::create() {
	initWindow();
	vulkan.init(window);
}

Window::operator GLFWwindow*() const {
	return window;
}

void Window::drawFrame() {
	vulkan.drawFrame(framebufferResized);
}

void Window::waitForIdle() {
	vulkan.waitForDeviceIdle();
}

void Window::destroy() {
	vulkan.cleanup();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::initWindow() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(Game::WIDTH, Game::HEIGHT, "Vulkan", nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	app->framebufferResized = true;
}