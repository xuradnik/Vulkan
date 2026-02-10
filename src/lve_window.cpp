#include "lve_window.hpp"

#include <stdexcept>


namespace lve
{
	LveWindow::LveWindow
		(const int width_p, const int height_p, const std::string &window_name_p)
	: m_width(width_p)
	, m_height(height_p)
	, m_window_name(window_name_p)
	, m_window(nullptr) {
		initWindow();
	}

	LveWindow::~LveWindow() {
		glfwDestroyWindow(this->m_window);
		glfwTerminate();
	}


	void LveWindow::initWindow() {
		if (this->m_window) {
			return;
		}
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_window = glfwCreateWindow
			(this->m_width, this->m_height, this->m_window_name.c_str(), nullptr, nullptr);
	}

	bool LveWindow::shouldClose() const {
		return glfwWindowShouldClose(this->m_window);
	}

	void LveWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
		if (glfwCreateWindowSurface(instance, this->m_window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create window surface");
		}
	}
}
