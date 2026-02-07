#ifndef VULKANTEST_VULCAN_ENGINE_WINDOW_H
#define VULKANTEST_VULCAN_ENGINE_WINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace lve {

    class Vulcan_Engine_Window {
    private:
        GLFWwindow         *m_window;
        const int           m_width;
        const int           m_height;
        const std::string   m_window_name;

        void initWindow();

    public:
        Vulcan_Engine_Window(const int width_p, const int height_p, const std::string& window_name_p);
        ~Vulcan_Engine_Window();
        bool shouldClose() const;
    };

}


#endif //VULKANTEST_VULCAN_ENGINE_WINDOW_H