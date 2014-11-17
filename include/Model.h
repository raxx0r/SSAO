#include <string>
#include <assimp/scene.h>    

class Model {
	public:
	  Model(const std::string& filePath);
	  float* vertices;
	  float* normals;
	  int numVertices;
	private:
	  void processObject(const aiScene* object);
};
