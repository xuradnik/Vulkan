#ifndef VULKAN_LVE_MODEL_HPP
#define VULKAN_LVE_MODEL_HPP


#include "lve_device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>
#include <cassert>
#include <cstring>

namespace lve
{
	class LveModel {
		public:
			struct Vertex {
				glm::vec2 m_position;
				glm::vec3 m_color;

				static std::vector <VkVertexInputBindingDescription>   getBindingDescriptions();
				static std::vector <VkVertexInputAttributeDescription> getAttributeDescriptions();
			};

			LveModel(LveDevice &device, const std::vector <Vertex> &vertices);
			~LveModel();

			LveModel(const LveModel &)            = delete;
			LveModel &operator=(const LveModel &) = delete;

			void bind(VkCommandBuffer commandBuffer);
			void draw(VkCommandBuffer commandBuffer);

		private:
			LveDevice &    m_lveDevice;
			VkBuffer       m_vertexBuffer;
			VkDeviceMemory m_vertexBufferMemory;
			uint32_t       m_vertexCount;

			void createVertexBuffers(const std::vector <Vertex> &vertices);
	};
}


#endif //VULKAN_LVE_MODEL_HPP
