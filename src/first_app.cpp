
#include "first_app.hpp"

namespace lve {
    void First_App::run() {
        while (!lveWindow.shouldClose()) {
            glfwPollEvents();
        }
    }
}
