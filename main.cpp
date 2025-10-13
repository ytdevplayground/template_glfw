#include <iostream>
#include <GLFW/glfw3.h>


int main (int argc, char** argv)
{

    glfwInit();

    GLFWwindow* window = glfwCreateWindow(800, 600, "HelloWindow", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    return 0;

}
