#include "lve_pipeline.hpp"

namespace lve {
    LvePipeline::LvePipeline
    (
        LveDevice &device_p,
        const std::string &vertFilePath_p,
        const std::string &fragFilePath_p,
        const PipelineConfigInfo configInfo_p) : m_device(device_p) {
        createGraphicsPipeline(vertFilePath_p, fragFilePath_p, configInfo_p);
    };

    LvePipeline::~LvePipeline() {
        vkDestroyShaderModule(m_device.device(), m_vertShaderModule, nullptr);
        vkDestroyShaderModule(m_device.device(), m_fragShaderModule, nullptr);
        vkDestroyPipeline(m_device.device(), m_graphicsPipeline, nullptr);
    }


    std::vector<char> LvePipeline::readFile(const std::string &filepath) {
        std::ifstream file{filepath, std::ios::ate | std::ios::binary};

        if (!file) {
            throw std::runtime_error("failed to open file: " + filepath);
        }

        size_t file_size = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(file_size);

        file.seekg(0);
        file.read(buffer.data(), file_size);

        file.close();
        return buffer;
    }


    void LvePipeline::createGraphicsPipeline
    (
        const std::string &vertFilePath,
        const std::string &fragFilePath,
        const PipelineConfigInfo configInfo_p
    ) {
        auto vertCode = readFile(vertFilePath);
        auto fragCode = readFile(fragFilePath);

        std::cout << "Vertex Shader Code Size: " << vertCode.size() << std::endl;
        std::cout << "Frag Shader Code Size: " << fragCode.size() << std::endl;
    }

    void LvePipeline::createShaderModule
    (
        const std::vector<char> &code,
        VkShaderModule *shaderModule
    ) const {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        if (vkCreateShaderModule(this->m_device.device(),&createInfo, nullptr, shaderModule ) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create shader module");
        }
    }



    PipelineConfigInfo LvePipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height) {
        PipelineConfigInfo configInfo{};

        return configInfo;
    }
}
