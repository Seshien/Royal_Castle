#include "window.h"

Window::Window()
{
    Init();
    std::cout << "GLFW Init Completed" << std::endl;
    if (CreateWindow()) std::cout << "Mozna w sumie jakies ladne logi zrobic" << std::endl;
    std::cout << "Window Creation Completed" << std::endl;
    if (CreateGlad()) std::cout << "Taka mala ambicja" << std::endl;
    std::cout << "GLAD init Completed" << std::endl;
    std::cout << "Graphic dependiences ready" << std::endl;
}

void Window::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

bool Window::CreateGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    return 0;
}


void Window::ChangeViewSize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool Window::CreateWindow()
{
    window_ptr = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window_ptr == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window_ptr);
    glfwSetFramebufferSizeCallback(window_ptr, ChangeViewSize);
    return 0;
}

bool Window::StartWindow()
{
    while (!glfwWindowShouldClose(window_ptr))
    {
        processInput();
        glfwSwapBuffers(window_ptr);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void Window::processInput()
{

}