// Window.h
#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class Window {
public:
    void init();
    void cleanup();
    bool shouldClose() const;
    void pollEvents() const;

    GLFWwindow* getGLFWwindow() const;
    bool wasResized() const;
    void resetResizedFlag();

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

private:
    //Objeto ventana usado
    GLFWwindow* window = nullptr;

    bool framebufferResized = false;

    //Tamaño inicial de la ventana
    static const uint32_t WIDTH = 800;
    static const uint32_t HEIGHT = 600;
};
