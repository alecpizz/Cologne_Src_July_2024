#include "Shader.h"

using namespace std;

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
     string vertexCode;
     string fragmentCode;
     ifstream vShaderFile;
     ifstream fShaderFile;

     vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
     fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

     try
     {   //standard cpp file loading and reading
          vShaderFile.open(vertexPath);
          fShaderFile.open(fragmentPath);
          stringstream vShaderStream, fShaderStream;

          vShaderStream << vShaderFile.rdbuf();
          fShaderStream << fShaderFile.rdbuf();

          vShaderFile.close();
          fShaderFile.close();

          vertexCode = vShaderStream.str();
          fragmentCode = fShaderStream.str();
     }
     catch(ifstream::failure e)
     {
         CG_CORE_ERROR("Error shader file read fail: ", e.what());
     }
     
     const char* vShaderCode = vertexCode.c_str(); //i hate c strings
     const char* fShaderCode = fragmentCode.c_str();

     //compile them shaders. works the same way as before
     unsigned int vertex, fragment;
     int success;
     char infoLog[512];

     vertex = glCreateShader(GL_VERTEX_SHADER);
     glShaderSource(vertex, 1, &vShaderCode, nullptr);
     glCompileShader(vertex);
     
     //check for death
     glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
     if(!success)
     {
          glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
          cerr << "SHADER COMPILATION FAILED FOR VERTEX: \n" << infoLog << endl;
     }

     fragment = glCreateShader(GL_FRAGMENT_SHADER);
     glShaderSource(fragment, 1, &fShaderCode, nullptr);
     glCompileShader(fragment);

     //again check for death
     glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
     if(!success)
     {
          glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
         CG_CORE_ERROR("Shader compilation failed for fragment shader: {0}\n", infoLog);
     }

     //create program for shader
     ID = glCreateProgram();
     glAttachShader(ID, vertex);
     glAttachShader(ID, fragment);
     glLinkProgram(ID);

     //check for death finally
     glGetProgramiv(ID, GL_LINK_STATUS, &success);
     if(!success)
     {
          glGetProgramInfoLog(ID, 512, nullptr, infoLog);
         CG_CORE_ERROR("Shader program compilation failed for fragment shader: {0}\n", infoLog);
     }

     glDeleteShader(vertex);
     glDeleteShader(fragment);
    CG_CORE_INFO("Compiled shader successfully");
}

Shader::~Shader()
{
     glDeleteProgram(ID);
    CG_CORE_INFO("Cleaned up shader");
}

void Shader::use()
{
     glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
     glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
     glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
     glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMatrix(const std::string &name, glm::mat4 value) const
{
     glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, glm::vec3 value) const
{
     glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
     glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(glm::vec3(x, y, z)));
}

void Shader::setuVec3(const string &name, glm::uvec3 value) const
{
    glUniform3uiv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setuVec2(const string &name, glm::uvec2 value) const
{
    glUniform2uiv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}


Shader::Shader(const char *computePath)
{
    string computeCode;
    ifstream shaderFile;

    shaderFile.exceptions(ifstream::failbit | ifstream::badbit);

    try
    {   //standard cpp file loading and reading
        shaderFile.open(computePath);
        stringstream shaderStream;

        shaderStream << shaderStream.rdbuf();

        shaderFile.close();

        computeCode = shaderStream.str();
    }
    catch(ifstream::failure e)
    {
        CG_CORE_ERROR("Error shader file read fail: {0}", e.what());
    }

    const char* cShaderCode = computeCode.c_str(); //i hate c strings

    //compile them shaders. works the same way as before
    unsigned int compute;
    int success;
    char infoLog[512];

    compute = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute, 1, &cShaderCode, nullptr);
    glCompileShader(compute);

    //check for death
    glGetShaderiv(compute, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(compute, 512, nullptr, infoLog);
        CG_CORE_ERROR("Shader compilation failed for compute shader: \n {0}", infoLog);
    }

    //create program for shade
    ID = glCreateProgram();
    glAttachShader(ID, compute);
    glLinkProgram(ID);

    //check for death finally
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        CG_CORE_ERROR("Shader program compilation failed for compute shader: \n {0}", infoLog);
    }

    glDeleteShader(compute);
    CG_CORE_INFO("Compiled compute shader successfully");
}

