#include "ModelImporter.h"

#include <assimp/Importer.hpp>      
#include <assimp/scene.h>           
#include <assimp/postprocess.h> 

ModelImporter::ModelImporter() {

}

bool ModelImporter::importModel(const std::string& filePath) {
  // Please read Assimp documentation for details on how to use this implementation.


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
  if( !scene){
    printf("Import failed! \n");
    return false;
  }

  // Now we can access the file's contents. 
  // DoTheSceneProcessing( scene);
  // We're done. Everything will be cleaned up by the importer destructor
  return true;
}