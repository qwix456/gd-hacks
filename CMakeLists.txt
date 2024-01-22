cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT GDHacks)
project(${PROJECT})


file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp src/other/*.cpp src/other/*.hpp)
add_library(${PROJECT} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT} PRIVATE
  libraries/minhook/include
  libraries/imgui-hook
  libraries/imgui
  libraries/cocos-headers/cocos2dx/
	libraries/cocos-headers/cocos2dx/include
	libraries/cocos-headers/cocos2dx/kazmath/include
	libraries/cocos-headers/cocos2dx/platform/win32
	libraries/cocos-headers/cocos2dx/platform/third_party/win32
	libraries/cocos-headers/cocos2dx/platform/third_party/win32/OGLES
  libraries/cocos-headers/cocos2dx/platform/third_party/win32/curl
  libraries/discord-rpc/include
  libraries
)

add_subdirectory(libraries/cocos-headers)
add_subdirectory(libraries/minhook)
add_subdirectory(libraries/imgui-hook)

target_link_libraries(${PROJECT} minhook imgui-hook opengl32 ${CMAKE_SOURCE_DIR}/libraries/cocos-headers/cocos2dx/libcocos2d.lib ${CMAKE_SOURCE_DIR}/libraries/cocos-headers/cocos2dx/robtop/glfw/glfw3.lib ${CMAKE_SOURCE_DIR}/libraries/discord-rpc/extensions/discord-rpc.lib)