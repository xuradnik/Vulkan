#ifndef VULKAN_VULCAN_ENGINE_PIPELINE_HPP
#define VULKAN_VULCAN_ENGINE_PIPELINE_HPP

#include "lve_device.hpp"
#include "lve_model.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <cassert>

namespace lve
{
	struct PipelineConfigInfo {
		PipelineConfigInfo()                                      = default;
		PipelineConfigInfo(const PipelineConfigInfo &)            = delete;
		PipelineConfigInfo &operator=(const PipelineConfigInfo &) = delete;

		VkPipelineViewportStateCreateInfo      vieportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo   multisampleInfo;
		VkPipelineColorBlendAttachmentState    colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo    colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo  depthStencilInfo;
		std::vector <VkDynamicState>           dynamicStateEnable;
		VkPipelineDynamicStateCreateInfo       dynamicStateInfo;
		VkPipelineLayout                       pipelineLayout = nullptr;
		VkRenderPass                           renderPass     = nullptr;
		uint32_t                               subpass        = 0;
	};


	class LvePipeline {
		private:
			LveDevice &    m_device;
			VkPipeline     m_graphicsPipeline;
			VkShaderModule m_vertShaderModule;
			VkShaderModule m_fragShaderModule;


			static std::vector <char> readFile(const std::string &filepath);

			void createGraphicsPipeline(
					const std::string &       vertFilePath,
					const std::string &       fragFilePath,
					const PipelineConfigInfo &configInfo
				);

			void createShaderModule(const std::vector <char> &code, VkShaderModule *shaderModule) const;

		public:
			LvePipeline(
					LveDevice &               device_p,
					const std::string &       vertFilePath_p,
					const std::string &       fragFilePath_p,
					const PipelineConfigInfo &configInfo_p
				);
			~LvePipeline();

			LvePipeline(const LvePipeline &)            = delete;
			LvePipeline &operator=(const LvePipeline &) = delete;

			void        bind(VkCommandBuffer commandBuffer);
			static void defaultPipelineConfigInfo(PipelineConfigInfo &configInfo);
	};
}


#endif //VULKAN_VULCAN_ENGINE_PIPELINE_HPP
