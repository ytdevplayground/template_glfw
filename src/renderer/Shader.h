#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Shader {

    public:
        Shader(const std::string vertexPath, const std::string fragmentPath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void SetBool    (const char* name,  bool  value) const;
        void SetInt     (const char* name,  int   value) const;
        void SetFloat   (const char* name,  float value) const;
        void SetVec3    (const char* name,  glm::vec3& value)const;
        void SetMat4    (const char* name,  glm::mat4& matrix)const;

    private:
        unsigned int m_ShaderID;

        unsigned int createProgram(const char* vertexsrc, const char* fragmentsrc);
        unsigned int compileShader(unsigned int type, const char* source);

        std::string ReadFile(const std::string path);

        int GetUniformLocation(const char* name) const;

};

#endif