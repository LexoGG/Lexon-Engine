// Window.h
#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include "Globals.h"

class Window {
public:
    void init();
    void cleanup();
    bool shouldClose() const;
    static void pollEvents();

    static GLFWwindow* getGLFWwindow();
	static bool getFramebufferResized();

    static bool wasResized();
    static void resetResizedFlag();

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

private:
    static GLFWwindow* window;
    static bool framebufferResized;

};

