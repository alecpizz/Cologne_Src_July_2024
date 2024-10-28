#ifndef MODEL_H
#define MODEL_H
#include "Shader.h"
#include "Mesh.h"
#include "../cgpch.h"
class Model
{
public:
     Model(const std::string &path);
     void Draw(Shader *shader);
private:
     std::vector<Mesh> meshes;
     std::string directory;
     std::vector<Texture> textures_loaded;
     void loadModel(const std::string &path);
     void processNode(aiNode *node, const aiScene *scene);
     Mesh processMesh(aiMesh *mesh, const aiScene *scene);
     std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
     unsigned int TextureFromFile(const char *path, const std::string &directory);
};

#endif
