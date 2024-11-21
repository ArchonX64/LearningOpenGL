cmake_minimum_required(VERSION 3.29)
project(glfw2)
set(CMAKE_CXX_STANDARD 20)

find_package(glad)
find_package(glfw3)
find_package(stb)
find_package(glm)
find_package(freetype)

add_executable(glfw2 src/gfx/Window.cpp
        src/util.h
        src/gfx/Window.h
        src/main.cpp
        src/gfx/Shader.cpp
        src/gfx/Shader.h
        src/util.cpp
        src/gfx/Texture.cpp
        src/gfx/Texture.h
        src/gfx/stbi_image.cpp
        src/gfx/BlockRenderer.cpp
        src/gfx/BlockRenderer.h
        src/gfx/Camera.cpp
        src/gfx/Camera.h
        src/gfx/FontRenderer.h
        src/gfx/FontRenderer.cpp
        src/windows_f.h
        src/game/Button.cpp
        src/game/Button.h
        src/gfx/BoxRenderer.cpp
        src/gfx/BoxRenderer.h
)

target_link_libraries(glfw2 glfw
        glad::glad
        stb::stb
        glm::glm
        Freetype::Freetype)
