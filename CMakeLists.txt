cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
project(gd-hacks VERSION 0.1.0)

file(GLOB_RECURSE SOURCES
	src/*.cpp
    src/*.hpp
)

if(${CMAKE_SYSTEM} MATCHES "Darwin" OR ${CMAKE_SYSTEM} MATCHES "Linux")
	message(FATAL_ERROR "Unsupported operating system. Only Windows is supported right now.")
endif()


add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories( ${PROJECT_NAME} PRIVATE
    libraries/imgui
    libraries/imgui-hook
    libraries/minhook/include
	libraries/cocos-headers/cocos2dx/
	libraries/cocos-headers/cocos2dx/include
	libraries/cocos-headers/cocos2dx/kazmath/include
	libraries/cocos-headers/cocos2dx/platform/win32
	libraries/cocos-headers/cocos2dx/platform/third_party/win32
	libraries/cocos-headers/cocos2dx/platform/third_party/win32/OGLES
)

add_subdirectory(libraries/minhook)
add_subdirectory(libraries/imgui-hook)
add_subdirectory(libraries/cocos-headers)

target_link_libraries(${PROJECT_NAME}
	${CMAKE_SOURCE_DIR}/libraries/cocos-headers/cocos2dx/libcocos2d.lib
	imgui-hook
	minhook
	opengl32
	cocos2d
)
