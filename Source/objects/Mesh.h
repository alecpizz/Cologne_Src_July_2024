#ifndef MESH_H
#define MESH_H
#include "../cgpch.h"
#include "Shader.h"
struct Vertex
{
     glm::vec3 Position;
     glm::vec3 Normal;
     glm::vec2 TexCoords;
     glm::vec3 Tangent;
     glm::vec3 Bitangent;
};

struct Texture
{
     unsigned int id;
     std::string type;
     std::string path;
};

class Mesh
{
public:
     std::vector<Vertex> verticies;
     std::vector<unsigned int> indicies;
     std::vector<Texture> textures;
     Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indicies, std::vector<Texture> textures);
     void Draw(Shader *shader);
private:
     unsigned int VAO, VBO, EBO;
     void setupMesh();
};

#endif
