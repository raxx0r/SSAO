#include <string>
#include <assimp/scene.h>    

struct Model{
	float* vertices;
	// int verticesSize;
	float* normals;
	// int normalsSize;

};

class ModelImporter {

private:
	Model processObject(const aiScene*);
    
public:
	ModelImporter();
	Model importModel(const std::string& filePath);
};
