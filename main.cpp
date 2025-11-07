#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* vertexSource = R"(#version 460 core
                              
                              layout ( location = 0) in vec3 aPos;

                              uniform mat4 uModel;
                              
                              void main() {
                                    gl_Position = uModel * vec4(aPos, 1.0f);
                              })";

const char* fragmentSource = R"(#version 460 core
                              
                              out vec4 aColor;
                              uniform vec4 uColor;
                              
                              void main() {
                                    aColor = uColor;
                              })";

unsigned int createProgram(const char* vertexsrc, const char* fragmentsrc);
unsigned int compileShader(unsigned int type, const char* source);

int main (int argc, char** argv)
{

    if(!glfwInit())
    {
        std::cout << "Couldn't initialize glfw" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "HelloWindow", nullptr, nullptr);

    if(!window)
    {
        std::cout << "can not create a window" << std::endl;
        glfwDestroyWindow(window);
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "can't load GLAD!!" << std::endl;
        return -1;
    }

    std::cout << "OPENGL: "     << std::endl;
    std::cout << "  VENDOR: "   << glGetString(GL_VENDOR) << std::endl;
    std::cout << "  VERSION: "  << glGetString(GL_VERSION) << std::endl;
    std::cout << "  RENDERER: " << glGetString(GL_RENDERER) << std::endl;

    unsigned int program = createProgram(vertexSource, fragmentSource);

    float triangle [] = {
        // x,    y,    z
         0.5f,  0.5f, 0.0f,   // 0   
        -0.5f, -0.5f, 0.0f,   // 1  
         0.5f, -0.5f, 0.0f,   // 2
        -0.5f,  0.5f, 0.0f    // 3
    };

    unsigned int indices [] = {
        0, 1, 2, 
        0, 1, 3
    };

    unsigned int VAO;
    unsigned int VBO;
    unsigned int IBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glUseProgram(program);

    unsigned int location = glGetUniformLocation(program, "uColor");
    unsigned int modelLocation = glGetUniformLocation(program, "uModel");

    glm::mat4 model{1.0f};

    srand(time(NULL));

    float r;
    float g = 0.0f;
    float b = 0.0f;

    glfwSwapInterval(1);

    float incremento = 0.01;

    float xValue = 0.0f;

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        r = (float)rand()/RAND_MAX;
        g = (float)rand()/RAND_MAX;
        b = (float)rand()/RAND_MAX;

        glUniform4f(location, r, g, b, 1.0f);

        if(xValue < -0.5f)  
            incremento =  0.01f;
        if(xValue > 0.5f)
            incremento = -0.01f;

        xValue += incremento; 

        model = glm::translate(model, glm::vec3(incremento, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(program);

    return 0;

}

unsigned int createProgram(const char *vertexsrc, const char *fragmentsrc)
{

    unsigned int program = glCreateProgram();

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexsrc);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentsrc);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    int sucess;
    glGetProgramiv(program, GL_LINK_STATUS, &sucess);

    if(!sucess)
    {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length);
        glGetProgramInfoLog(program, length, nullptr, log.data());

        std::cout << "Link error: " << log.data() << std::endl;

    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int compileShader(unsigned int type, const char* source)
{

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);

    glCompileShader(shader);

    int sucess;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &sucess);

    if(!sucess)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length);
        glGetShaderInfoLog(shader, length, nullptr, log.data());

        std::cout << "Compile error: " << log.data() << std::endl;

    }

    return shader;
}
