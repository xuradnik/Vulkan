#ifndef VULKANTEST_FIRST_APP_H
#define VULKANTEST_FIRST_APP_H

#include "vulcan_engine_window.h"

namespace lve {
    class First_App {
    private:
        Vulcan_Engine_Window m_vulcan_engine_window{WIDTH, HEIGHT, "Vulkan"};

    public:
        static constexpr int WIDTH  = 800;
        static constexpr int HEIGHT = 800;

        void run();
    };
}


#endif //VULKANTEST_FIRST_APP_H
