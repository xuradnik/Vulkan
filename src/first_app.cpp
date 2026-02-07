
#include "first_app.h"

namespace lve {
    void First_App::run() {
        while (!m_vulcan_engine_window.shouldClose()) {
            glfwPollEvents();
        }
    }
}
