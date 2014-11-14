#include <string>
#include <assimp/scene.h>    

struct Model {
	float* vertices;
	float* normals;
	int numVerts;
};

class ModelImporter {

public:
	ModelImporter();
	Model importModel(const std::string& filePath);
	
private:
	Model processObject(const aiScene*);
    
};
