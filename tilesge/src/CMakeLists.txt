include_directories(${CMAKE_SOURCE_DIR}/tilesge/include ${CMAKE_SOURCE_DIR}/tilesge/inclib)

file(GLOB_RECURSE helloworld_SRC CONFIGURE_DEPENDS "*.cpp")

include(${CMAKE_SOURCE_DIR}/cmakerc/CMakeRC.cmake)

add_executable(TilesGE main.cpp ${helloworld_SRC})

target_link_libraries(TilesGE shaders textures fonts)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++0x")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_include_directories(TilesGE PRIVATE ${MINGW_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
target_include_directories(TilesGE PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(TilesGE ${OPENGL_gl_LIBRARY})

target_link_libraries(TilesGE glfw)
target_link_libraries(TilesGE glad)
target_link_libraries(TilesGE glm)
target_link_libraries(TilesGE lodepng)
target_link_libraries(TilesGE freetype)
target_link_libraries(TilesGE spdlog)
