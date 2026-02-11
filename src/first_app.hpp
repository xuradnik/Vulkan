#ifndef VULKAN_FIRST_APP_HPP
#define VULKAN_FIRST_APP_HPP

#include "lve_window.hpp"
#include "lve_pipeline.hpp"
#include "lve_device.hpp"
#include "lv_swap_chain.hpp"
#include  "lve_model.hpp"

#include <memory>
#include <vector>
#include <stdexcept>

namespace lve
{
	class FirstApp {
		private:
			LveWindow                      m_lveWindow { WIDTH, HEIGHT, "Vulkan" };
			LveDevice                      m_lveDevice { m_lveWindow };
			std::unique_ptr <LveSwapChain> m_lveSwapChain;

			std::unique_ptr <LvePipeline> m_lve_pipeline;
			VkPipelineLayout              m_pipelineLayout;
			std::vector <VkCommandBuffer> m_commandBuffers;
			std::unique_ptr <LveModel>    m_lveModel;


			void createPipelineLayout();
			void createPipeline();
			void createCommandBuffers();
			void drawFrame();
			void loadModels();
			void recreateSwapChain();
			void recordCommandBuffer(int imageIndex_p) const;

		public:
			static constexpr int WIDTH  = 800;
			static constexpr int HEIGHT = 600;

			FirstApp();
			~FirstApp();

			FirstApp(const FirstApp &)             = delete;
			FirstApp &operator =(const FirstApp &) = delete;


			void run();
	};
}


#endif //VULKAN_FIRST_APP_HPP
