#ifndef VULKANTEST_FIRST_APP_H
#define VULKANTEST_FIRST_APP_H

#include "lve_window.hpp"
#include "lve_pipeline.hpp"
#include "lve_device.hpp"
#include "lv_swap_chain.hpp"

#include <memory>
#include <vector>
#include <stdexcept>

namespace lve {
    class FirstApp {
    private:
        LveWindow lveWindow{WIDTH, HEIGHT, "Vulkan"};
        LveDevice lveDevice{lveWindow};
        LveSwapChain lveSwapChain{lveDevice, lveWindow.getExtent()};

        std::unique_ptr<LvePipeline> lvePipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;


        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();

    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 800;

        FirstApp();
        ~FirstApp();

        FirstApp(const FirstApp &) = delete;

        FirstApp &operator =(const FirstApp &) = delete;


        void run();
    };
}


#endif //VULKANTEST_FIRST_APP_H
