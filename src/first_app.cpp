#include "first_app.hpp"

namespace lve
{
	FirstApp::FirstApp() {
		loadModels();
		createPipelineLayout();
		recreateSwapChain();
		createCommandBuffers();
	}

	FirstApp::~FirstApp() {
		vkDestroyPipelineLayout
			(
				m_lveDevice.device(),
				m_pipelineLayout,
				nullptr
			);
	}


	void FirstApp::run() {
		while (!m_lveWindow.shouldClose()) {
			glfwPollEvents();
			drawFrame();
		}

		vkDeviceWaitIdle(m_lveDevice.device());
	}


	// Private Methodes

	void FirstApp::createPipelineLayout() {
		VkPipelineLayoutCreateInfo pipelineLayoutInfo { };
		pipelineLayoutInfo.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount         = 0;
		pipelineLayoutInfo.pSetLayouts            = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges    = nullptr;

		if (vkCreatePipelineLayout
			(
				m_lveDevice.device(),
				&pipelineLayoutInfo,
				nullptr,
				&m_pipelineLayout
			) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create pipeline layout.");
		}
	}

	void FirstApp::createPipeline() {
		assert(m_lveSwapChain != nullptr && "Cannot create pipeline before swap chain");
		assert(m_pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

		PipelineConfigInfo pipelineConfig { };
		LvePipeline::defaultPipelineConfigInfo(pipelineConfig);

		pipelineConfig.renderPass     = m_lveSwapChain->getRenderPass();
		pipelineConfig.pipelineLayout = m_pipelineLayout;
		m_lve_pipeline                = std::make_unique <LvePipeline>
			(
				m_lveDevice,
				"../shaders/simple_shader.vert.spv",
				"../shaders/simple_shader.frag.spv",
				pipelineConfig
			);
	}

	void FirstApp::recreateSwapChain() {
		auto extent = m_lveWindow.getExtent();
		while (extent.width == 0 || extent.height == 0) {
			extent = m_lveWindow.getExtent();
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(m_lveDevice.device());
		if (m_lveSwapChain == nullptr) {
			m_lveSwapChain = std::make_unique <LveSwapChain>(m_lveDevice, extent);
		} else {
			std::shared_ptr <LveSwapChain> oldSwapChain = std::move(m_lveSwapChain);
			m_lveSwapChain = std::make_unique <LveSwapChain>(m_lveDevice, extent, oldSwapChain);

			if (!oldSwapChain->compareSwapFormats(*m_lveSwapChain.get())) {
				throw std::runtime_error("Swap chain image(or depth) format has changed!");
			}
		}
		createPipeline();
	}

	void FirstApp::createCommandBuffers() {
		m_commandBuffers.resize(m_lveSwapChain->imageCount());
		VkCommandBufferAllocateInfo allocInfo { };
		allocInfo.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool        = m_lveDevice.getCommandPool();
		allocInfo.commandBufferCount = static_cast <uint32_t>(m_commandBuffers.size());

		if (vkAllocateCommandBuffers
					(
						m_lveDevice.device(),
						&allocInfo,
						m_commandBuffers.data()
					) != VK_SUCCESS
			) {
			throw std::runtime_error("Failed to allocate command buffers.");
		}
	}

	void FirstApp::recordCommandBuffer(int imageIndex_p) const {
		VkCommandBufferBeginInfo beginInfo { };
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(m_commandBuffers[imageIndex_p], &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("Failed to begin recording command buffer!");
		}

		VkRenderPassBeginInfo renderPassInfo { };
		renderPassInfo.sType             = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass        = m_lveSwapChain->getRenderPass();
		renderPassInfo.framebuffer       = m_lveSwapChain->getFrameBuffer(imageIndex_p);
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = m_lveSwapChain->getSwapChainExtent();

		std::array <VkClearValue, 2> clearValues { };
		clearValues[0].color        = { 0.1f, 0.1f, 0.1f, 1.0f };
		clearValues[1].depthStencil = { 1.0f, 0 };

		renderPassInfo.clearValueCount = static_cast <uint32_t>(clearValues.size());
		renderPassInfo.pClearValues    = clearValues.data();

		vkCmdBeginRenderPass
			(
				m_commandBuffers[imageIndex_p],
				&renderPassInfo,
				VK_SUBPASS_CONTENTS_INLINE
			);

		VkViewport viewport { };
		viewport.x        = 0.0f;
		viewport.y        = 0.0f;
		viewport.width    = static_cast <float>(m_lveSwapChain->getSwapChainExtent().width);
		viewport.height   = static_cast <float>(m_lveSwapChain->getSwapChainExtent().height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		VkRect2D scissor { { 0, 0 }, m_lveSwapChain->getSwapChainExtent() };
		vkCmdSetViewport(m_commandBuffers[imageIndex_p], 0, 1, &viewport);
		vkCmdSetScissor(m_commandBuffers[imageIndex_p], 0, 1, &scissor);

		this->m_lve_pipeline->bind(m_commandBuffers[imageIndex_p]);
		this->m_lveModel->bind((m_commandBuffers[imageIndex_p]));
		this->m_lveModel->draw((m_commandBuffers[imageIndex_p]));

		vkCmdEndRenderPass(m_commandBuffers[imageIndex_p]);
		if (vkEndCommandBuffer(m_commandBuffers[imageIndex_p]) != VK_SUCCESS) {
			throw std::runtime_error("Failed to record command buffer!");
		}
	}

	void FirstApp::drawFrame() {
		uint32_t imageIndex;
		auto     result = m_lveSwapChain->acquireNextImage(&imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapChain();
			return;
		}

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("Failed to acquire swap chain image.");
		}

		recordCommandBuffer(imageIndex);
		result = m_lveSwapChain->submitCommandBuffers(&m_commandBuffers[imageIndex], &imageIndex);

		if (
				result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR ||
				m_lveWindow.wasWindowResized()
			) {
			m_lveWindow.resetWindowResizeFlag();
			recreateSwapChain();
			return;
		}

		if (result != VK_SUCCESS) {
			throw std::runtime_error("Failed to present swap chain image.");
		}
	}

	void FirstApp::loadModels() {
		std::vector <LveModel::Vertex> vertices = {
			{ { 0.0f, -0.5f }, { 1.0f, 0.0f, 0.0f } },
			{ { 0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f } },
			{ { -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f } },
		};

		this->m_lveModel = std::make_unique <LveModel>(this->m_lveDevice, vertices);
	}
}
