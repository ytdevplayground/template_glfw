#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <memory>

#include "Shader.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"

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

    std::shared_ptr<Shader> shader = std::make_shared<Shader>("../res/shaders/textured.vert", "../res/shaders/textured.frag");

    float vertices[] = {
        // Frente
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        // Trás
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

        // Direita
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        // Esquerda
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

        // Topo
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,

        // Fundo
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,       // frente
        4, 5, 6, 6, 7, 4,       // trás
        8, 9, 10, 10, 11, 8,       // direita
        12, 13, 14, 14, 15, 12,       // esquerda
        16, 17, 18, 18, 19, 16,       // topo
        20, 21, 22, 22, 23, 20        // fundo
    };

    int width, height, channel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("../cobblestone.png", &width, &height, &channel, 0);

    unsigned int VAO;
    unsigned int texture;

    glGenVertexArrays(1, &VAO);
    glGenTextures(1, &texture);

    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format =  (channel == 4 ? GL_RGBA : GL_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glBindVertexArray(0);

    vertexBuffer->Unbind();
    indexBuffer->Unbind();
    glBindTexture(GL_TEXTURE_2D, 0);

    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model{1.0f};
        glm::mat4 view{1.0f};
        glm::mat4 projection;

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        projection = glm::perspective(glm::radians(75.0f), 800.0f/600.0f, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        shader->Bind();
        
        shader->SetMat4("uModel", model);
        shader->SetMat4("uProjection", projection);
        shader->SetMat4("uView", view);
        shader->SetInt("uTexture", 0);


        glActiveTexture(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        shader->Unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;

}