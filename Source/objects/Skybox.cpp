#include "Skybox.h"
#include "../stb_image.h"



SkyBox::SkyBox(const char *path, const char *vertexPath, const char *fragmentPath)
{
     this->path = std::string(path);
     std::vector<std::string> faces{"right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"};
     loadCubemap(faces);
     glGenVertexArrays(1, &VAO);
     glGenBuffers(1, &VBO);

     glBindVertexArray(VAO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

     glEnableVertexAttribArray(0);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
     shader = new Shader(vertexPath, fragmentPath);
     shader->use();
     shader->setInt("skybox", 0);
}

SkyBox::~SkyBox()
{
     delete shader;
     shader = nullptr;
}

void SkyBox::Draw(glm::mat4 view, glm::mat4 projection)
{
     glDepthFunc(GL_LEQUAL);
     shader->use();
     shader->setMatrix("projection", projection);
     shader->setMatrix("view", glm::mat4(glm::mat3(view)));

     glBindVertexArray(VAO);
     glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
     glDrawArrays(GL_TRIANGLES, 0, 36);
     glDepthFunc(GL_LESS);
}

void SkyBox::loadCubemap(std::vector<std::string> &faces)
{
     stbi_set_flip_vertically_on_load(false);
     glGenTextures(1, &textureID);
     glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

     int width, height, numChannels;

     for (unsigned int i = 0; i < faces.size(); i++)
     {
          unsigned char *data = stbi_load((path + '/' + faces[i]).c_str(), &width, &height, &numChannels, 0);
          if (data)
          {
               glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
          }
          else
          {
              CG_CORE_ERROR("Failed to load cubempap: ", faces[i]);
          }
          stbi_image_free(data);
     }
     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
     stbi_set_flip_vertically_on_load(true);
}
