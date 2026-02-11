cmake_minimum_required(VERSION 3.24)
project(Vulkan)

set(CMAKE_CXX_STANDARD 17)

# 1. FIND VULKAN
message(STATUS "Vulkan SDK Path: $ENV{VULKAN_SDK}")
find_package(Vulkan REQUIRED)

# 2. SETUP LOCAL LIBRARIES

# --- GLFW (Build from local source) ---
# Turn off GLFW options we don't need
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Add the subdirectory.
add_subdirectory(external/glfw)

# --- GLM (Header only) ---
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE external)

# 3. YOUR EXECUTABLE
add_executable(Vulkan src/main.cpp
        src/first_app.cpp
        src/first_app.hpp
        src/lve_window.cpp
        src/lve_window.hpp
        src/lve_pipeline.cpp
        src/lve_pipeline.hpp
        src/lve_device.hpp
        src/lve_device.cpp
        src/lv_swap_chain.cpp
        src/lv_swap_chain.hpp
        src/lve_model.cpp
        src/lve_model.hpp)

# 4. LINKING
target_link_libraries(Vulkan
        PRIVATE
        Vulkan::Vulkan
        glfw
        glm
)

# 5. SHADER COMPILER FINDER (Standard)
find_program(GLSLC_EXECUTABLE NAMES glslc HINTS "$ENV{VULKAN_SDK}/Bin")