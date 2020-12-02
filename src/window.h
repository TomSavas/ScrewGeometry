#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window 
{
private:
    const char *title;

    GLFWwindow *window;

public:
    Window(const char *title, int width, int height);
    virtual ~Window();

    GLFWwindow *GlfwWindow();
private:
    static void ResizeCallbackProxy(GLFWwindow *window, int width, int height);
    virtual void ResizeCallback(int width, int height);
};

#endif
