#include <stdio.h>
#include <stdlib.h>
#include <functional>

#include "window.h"

Window::Window(const char *title, int width, int height)
{
    title = title;
    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window)
    {
        fprintf(stderr, "Failed initializing a window!\n");

        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, Window::ResizeCallbackProxy);
}

Window::~Window() 
{
    glfwTerminate();
}

GLFWwindow *Window::GlfwWindow()
{
    return window;
}

void Window::ResizeCallbackProxy(GLFWwindow *window, int width, int height) 
{
    ((Window*) glfwGetWindowUserPointer(window))->ResizeCallback(width, height);
}

void Window::ResizeCallback(int width, int height) 
{
    glViewport(0, 0, width, height);
}
