#include "graphics/window.hpp"

class HelloTriangleApplication {
public:

	HelloTriangleApplication() {
	}

	void run() {
		window = new Window();
		window->create();
		mainLoop();
		cleanup();
	}

private:

	Window * window;

	void mainLoop() {
		while (!glfwWindowShouldClose(*window)) {
			glfwPollEvents();
			window->drawFrame();
		}

		window->waitForIdle();
	}

	void cleanup() {
		window->destroy();
	}
};

int main() {
	HelloTriangleApplication app;
	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		int x;
		std::cin >> x;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}