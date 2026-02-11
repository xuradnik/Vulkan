#ifndef LVE_WINDOW_HPP
#define LVE_WINDOW_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include <array>

namespace lve
{
	class LveWindow {
		private:
			GLFWwindow *      m_window;
			int               m_width;
			int               m_height;
			const std::string m_window_name;
			bool              m_framebufferResized = false;

			void        initWindow();
			static void framebufferResizeCallback(GLFWwindow *window_p, int width_p, int height_p);

		public:
			LveWindow(const int width_p, const int height_p, const std::string &window_name_p);
			~LveWindow();

			LveWindow(const LveWindow &)             = delete;
			LveWindow &operator =(const LveWindow &) = delete;

			bool shouldClose() const;

			VkExtent2D getExtent() const {
				return { static_cast <uint32_t>(m_width), static_cast <uint32_t>(m_height) };
			}

			bool wasWindowResized() const { return m_framebufferResized; }
			void resetWindowResizeFlag() { m_framebufferResized = false; }
			void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
	};
}


#endif //LVE_WINDOW_HPP
