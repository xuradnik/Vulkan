#ifndef VULKAN_VULCAN_ENGINE_PIPELINE_H
#define VULKAN_VULCAN_ENGINE_PIPELINE_H

#include "lve_device.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <cassert>

namespace lve {
    struct PipelineConfigInfo {
        VkViewport viewport;
        VkRect2D scissor;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };


    class LvePipeline {
    private:

        LveDevice& m_device;
        VkPipeline m_graphicsPipeline;
        VkShaderModule m_vertShaderModule;
        VkShaderModule m_fragShaderModule;


        static std::vector<char> readFile(const std::string &filepath);

        void createGraphicsPipeline(
            const std::string &vertFilePath,
            const std::string &fragFilePath,
            const PipelineConfigInfo configInfo
        );

        void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule) const;

    public:
        LvePipeline(
            LveDevice &device_p,
            const std::string &vertFilePath_p,
            const std::string &fragFilePath_p,
            const PipelineConfigInfo configInfo_p
        );
        ~LvePipeline();

        LvePipeline(const LvePipeline&) = delete;
        void operator=(const LvePipeline&) = delete;

        void bind(VkCommandBuffer commandBuffer);

        static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);
    };
}


#endif //VULKAN_VULCAN_ENGINE_PIPELINE_H
