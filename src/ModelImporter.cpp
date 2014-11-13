#include "ModelImporter.h"

#include <assimp/Importer.hpp>             
#include <assimp/postprocess.h> 

ModelImporter::ModelImporter() {

}

bool ModelImporter::importModel(const std::string& filePath) {

	// Create an instance of the Importer class
 	Assimp::Importer importer;

  	// And have it read the given file with some example postprocessing
  	// Usually - if speed is not the most important aspect for you - you'll 
  	// propably to request more postprocessing than we do in this example.
  	const aiScene* scene = importer.ReadFile( filePath, 
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);
  
  // If the import failed, report it
  if (!scene) {
    printf("Model import failed! - %s \n", importer.GetErrorString());
    return false;
  }

  printf("Model import of %s succeded. \n", filePath.c_str());

  processObject(scene);

  // Now we can access the file's contents. 
  // DoTheSceneProcessing( scene);
  // We're done. Everything will be cleaned up by the importer destructor
  return true;
}

// Processes a scene that only consists of one object (one mesh).
void ModelImporter::processObject(const aiScene* object) {

  aiMesh* mesh = object->mMeshes[0];
  int numVerts = mesh->mNumFaces * 3;

  float* vertices = new float[numVerts * 3];
  // float* normals = new float[numVerts * 3];
  // float* uv = new float[numVerts * 2];

  for (uint i = 0; i < mesh->mNumFaces; i++) {
    const aiFace& face = mesh->mFaces[i];

    for (uint j = 0; j < 3; j++) {
      aiVector3D pos = mesh->mVertices[face.mIndices[j]];
      memcpy(vertices, &pos, sizeof(float) * 3);
      vertices += 3;
    }
  }
  vertices -= numVerts * 3;
}