#include "lve_model.hpp"


namespace lve
{
	LveModel::LveModel(LveDevice &device, const std::vector <Vertex> &vertices)
	: m_lveDevice(device) {
		this->createVertexBuffers(vertices);
	}

	LveModel::~LveModel() {
		vkDestroyBuffer(m_lveDevice.device(), m_vertexBuffer, nullptr);
		vkFreeMemory(m_lveDevice.device(), m_vertexBufferMemory, nullptr);
	}


	// Public Methodes

	void LveModel::draw(VkCommandBuffer commandBuffer) {
		vkCmdDraw(commandBuffer, m_vertexCount, 1, 0, 0);
	}

	void LveModel::bind(VkCommandBuffer commandBuffer) {
		VkBuffer     buffers[] = { m_vertexBuffer };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
	}


	// Private Methodes

	void LveModel::createVertexBuffers(const std::vector <Vertex> &vertices) {
		m_vertexCount = static_cast <uint32_t>(vertices.size());
		assert(m_vertexCount >= 3 && "Vertex count must be at least 3");

		VkDeviceSize bufferSize = sizeof(vertices[0]) * m_vertexCount;
		m_lveDevice.createBuffer
			(
				bufferSize,
				VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
				m_vertexBuffer,
				m_vertexBufferMemory
			);

		void *data;
		vkMapMemory
			(
				m_lveDevice.device(),
				m_vertexBufferMemory,
				0,
				bufferSize,
				0,
				&data
			);
		mempcpy
			(
				data,
				vertices.data(),
				static_cast <size_t>(bufferSize)
			);
		vkUnmapMemory
			(
				m_lveDevice.device(),
				m_vertexBufferMemory
			);
	}

	// Inside Struct Methodes


	std::vector <VkVertexInputBindingDescription> LveModel::Vertex::getBindingDescriptions() {
		std::vector <VkVertexInputBindingDescription> bindingDescriptions(1);
		bindingDescriptions[0].binding   = 0;
		bindingDescriptions[0].stride    = sizeof(Vertex);
		bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescriptions;
	}

	std::vector <VkVertexInputAttributeDescription> LveModel::Vertex::getAttributeDescriptions() {
		std::vector <VkVertexInputAttributeDescription> atributeDescriptions(2);

		atributeDescriptions[0].binding  = 0;
		atributeDescriptions[0].location = 0;
		atributeDescriptions[0].format   = VK_FORMAT_R32G32_SFLOAT;
		atributeDescriptions[0].offset   = offsetof(Vertex, m_position);

		atributeDescriptions[1].binding  = 0;
		atributeDescriptions[1].location = 1;
		atributeDescriptions[1].format   = VK_FORMAT_R32G32B32_SFLOAT;
		atributeDescriptions[1].offset   = offsetof(Vertex, m_color);

		return atributeDescriptions;
	}
}
