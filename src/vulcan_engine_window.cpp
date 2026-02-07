#include "vulcan_engine_window.h"


namespace lve {
    Vulcan_Engine_Window::Vulcan_Engine_Window
    (const int width_p, const int height_p, const std::string &window_name_p)
        : m_width(width_p), m_height(height_p), m_window_name(window_name_p), m_window(nullptr) {
        initWindow();
    }

    Vulcan_Engine_Window::~Vulcan_Engine_Window() {
        glfwDestroyWindow(this->m_window);
        glfwTerminate();
    }


    void Vulcan_Engine_Window::initWindow() {
        if (this->m_window) {
            return;
        }
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_window = glfwCreateWindow(this->m_width, this->m_height, this->m_window_name.c_str(), nullptr, nullptr);
    }

    bool Vulcan_Engine_Window::shouldClose() const {
        return glfwWindowShouldClose(this->m_window);
    }
}
