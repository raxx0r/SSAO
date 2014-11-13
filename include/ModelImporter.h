#include <string>
#include <assimp/scene.h>    

struct Model{
	float* vertices;
	float* normals;
	int numVerts;
	// int normalsSize;

};

class ModelImporter {

private:
	Model processObject(const aiScene*);
    
public:
	ModelImporter();
	Model importModel(const std::string& filePath);
};
