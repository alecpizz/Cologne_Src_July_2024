#include "Mesh.h"
#include "Shader.h"

using namespace std;

Mesh::Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indicies, std::vector<Texture> textures)
{
     this->verticies = verticies;
     this->indicies = indicies;
     this->textures = textures;

     setupMesh();
}

void Mesh::Draw(Shader *shader)
{
     unsigned int diffuseNum = 1;
     unsigned int specularNum = 1;
     unsigned int normalNum = 1;
     for (unsigned int i = 0; i < textures.size(); i++)
     {
          glActiveTexture(GL_TEXTURE0 + i);
          string number;
          string name = textures[i].type;
          if (name == "texture_diffuse")
               number = to_string(diffuseNum++);
          else if (name == "texture_specular")
               number = to_string(specularNum++);
          else if (name == "texture_normal")
               number = to_string(normalNum++);
          shader->setInt(("material." + name + number).c_str(), i);
          glBindTexture(GL_TEXTURE_2D, textures[i].id);
     }

     glBindVertexArray(VAO);
     glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
     glBindVertexArray(0);
     glActiveTexture(0);
}

void Mesh::setupMesh()
{
     glGenVertexArrays(1, &VAO);
     glGenBuffers(1, &VBO);
     glGenBuffers(1, &EBO);

     glBindVertexArray(VAO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);

     glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), &verticies[0], GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), &indicies[0], GL_STATIC_DRAW);

     // vertex positions
     glEnableVertexAttribArray(0);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

     // normals
     glEnableVertexAttribArray(1);
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
     // text coords
     glEnableVertexAttribArray(2);
     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));

     // Tangent
     glEnableVertexAttribArray(3);
     glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Tangent));

     glEnableVertexAttribArray(4);
     glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Bitangent));

     glBindVertexArray(0);
}
