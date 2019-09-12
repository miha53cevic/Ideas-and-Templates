#pragma once
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <iostream>

class ShaderProgram
{
public:
    ShaderProgram(std::string vertexFile, std::string fragmentFile)
    {
        m_vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
        m_fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

        m_programID = glCreateProgram();
        glAttachShader(m_programID, m_vertexShaderID);
        glAttachShader(m_programID, m_fragmentShaderID);
        glLinkProgram(m_programID);
        glValidateProgram(m_programID);
        bindAttributes();
    }

    ~ShaderProgram()
    {
        stop();
        glDetachShader(m_programID, m_vertexShaderID);
        glDetachShader(m_programID, m_fragmentShaderID);
        glDeleteShader(m_vertexShaderID);
        glDeleteShader(m_fragmentShaderID);
        glDeleteProgram(m_programID);
    }

    void start()
    {
        glUseProgram(m_programID);
    }

    void stop()
    {
        glUseProgram(0);
    }

protected:
    virtual void bindAttributes() {};

    void bindAttribute(int attribute, std::string variableName)
    {
        const char* varName = variableName.c_str();

        glBindAttribLocation(m_programID, attribute, varName);
    }

private:
    GLuint m_programID;
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;

    GLuint loadShader(std::string file, int type)
    {
        std::ifstream reader(file);
        if (reader.bad())
            std::cout << "Could not not open shader file!\n";
        else
        {
            std::string shader;
            while (!reader.eof())
            {
                std::string line;
                std::getline(reader, line);

                shader += line;
                shader += "\n";
            }

            const char* shaderSource = shader.c_str();

            GLuint shaderID = glCreateShader(type);
            glShaderSource(shaderID, 1, &shaderSource, NULL);
            glCompileShader(shaderID);

            // Check for errors
            GLint success;
            char infoLog[512];

            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
                std::cout << "ERROR SHADER VERTEX COMPILATION FAILED\n:" << infoLog << "\n";
            }

            return shaderID;
        }

        return -1;
    }
};

