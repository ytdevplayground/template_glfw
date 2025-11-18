#include "Shader.h"

#include <fstream>
#include <sstream>
#include <vector>

Shader::Shader(const std::string vertexPath, const std::string fragmentPath)
{
    std::string vertexSrc = ReadFile(vertexPath);
    std::string fragmentSrc = ReadFile(fragmentPath);

    m_ShaderID = createProgram(vertexSrc.c_str(), fragmentSrc.c_str());

}

Shader::~Shader()
{
    glDeleteProgram(m_ShaderID);
}

void Shader::Bind() const
{
    glUseProgram(m_ShaderID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetBool(const char *name, bool value) const
{
    glUniform1i(GetUniformLocation(name), (int)value);
}

void Shader::SetInt(const char *name, int value) const
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetFloat(const char *name, float value) const
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetVec3(const char *name, glm::vec3& value) const
{
    glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetMat4(const char *name, glm::mat4& matrix) const
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE,  glm::value_ptr(matrix));
}

unsigned int Shader::createProgram(const char *vertexsrc, const char *fragmentsrc)
{
    m_ShaderID = glCreateProgram();

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexsrc);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentsrc);

    glAttachShader(m_ShaderID, vs);
    glAttachShader(m_ShaderID, fs);

    glLinkProgram(m_ShaderID);

    int sucess;
    glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &sucess);

    if(!sucess)
    {
        int length;
        glGetProgramiv(m_ShaderID, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length);
        glGetProgramInfoLog(m_ShaderID, length, nullptr, log.data());

        std::cout << "Link error: " << log.data() << std::endl;

    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return m_ShaderID;
}

unsigned int Shader::compileShader(unsigned int type, const char *source)
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

        std::cout << "Compile error: " 
                  << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
                  << "Shader: "
                  << log.data() << std::endl;

    }

    return shader;
}

std::string Shader::ReadFile(const std::string path)
{

    std::ifstream file(path);
    if(!file)
    {
        std::cout << "Couldn't read file." << std::endl;
        return {};
    }

    std::stringstream ss;
    ss << file.rdbuf();

    return ss.str();
}

int Shader::GetUniformLocation(const char *name) const
{
    int loc = glGetUniformLocation(m_ShaderID, name);
    if(loc == -1)
    {
        std::cout << "Location not found." << std::endl;
    }
    return loc;
}
