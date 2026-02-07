#ifndef LVE_WINDOW_H
#define LVE_WINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace lve {

    class LveWindow {
    private:
        GLFWwindow         *m_window;
        const int           m_width;
        const int           m_height;
        const std::string   m_window_name;

        void initWindow();

    public:
        LveWindow(const int width_p, const int height_p, const std::string& window_name_p);
        ~LveWindow();

        LveWindow(const LveWindow&) = delete;
        LveWindow &operator =(const LveWindow&) = delete;

        bool shouldClose() const;
        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
    };

}


#endif //LVE_WINDOW_H