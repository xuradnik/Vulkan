#ifndef VULKANTEST_FIRST_APP_H
#define VULKANTEST_FIRST_APP_H

#include "lve_window.hpp"
#include "lve_pipeline.hpp"
#include "lve_device.hpp"

namespace lve {
    class First_App {
    private:
        LveWindow lveWindow{WIDTH, HEIGHT, "Vulkan"};
        LveDevice lveDevice{lveWindow};
        LvePipeline lvePipeline
        {
            lveDevice,
            "../shaders/simple_shader.vert.spv",
            "../shaders/simple_shader.frag.spv",
            LvePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)
        };

    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 800;

        void run();
    };
}


#endif //VULKANTEST_FIRST_APP_H
