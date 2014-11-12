#include <string>
#include <assimp/scene.h>    

class ModelImporter {

private:
	void processObject(const aiScene*);
    
public:
	ModelImporter();
	bool importModel(const std::string& filePath);
};
