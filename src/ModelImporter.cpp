#include "ModelImporter.h"

#include <assimp/Importer.hpp>             
#include <assimp/postprocess.h> 

ModelImporter::ModelImporter() {

}

Model ModelImporter::importModel(const std::string& filePath) {

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

        // TODO: Should be changed, return nullptr or similar.
        // Proper cleanup can be missed if program terminates here.
        exit(EXIT_FAILURE);
    }

    printf("Model import of %s succeded. \n", filePath.c_str());    

    // We're done. Everything will be cleaned up by the importer destructor
    return processObject(scene);
}

// Processes a scene that only consists of one object (one mesh).
Model ModelImporter::processObject(const aiScene* object) {

    float *vertexArray;
    float *normalArray;

    int numVerts = 0;
    aiMesh* mesh = object->mMeshes[0];

    vertexArray = new float[mesh->mNumFaces*3*3];
    normalArray = new float[mesh->mNumFaces*3*3];

    for (int i = 0; i < mesh->mNumFaces; i++) {

        const aiFace& face = mesh->mFaces[i];
     
        for (int j = 0; j < 3; j++) {

            aiVector3D normal = mesh->mNormals[face.mIndices[j]];
            memcpy(normalArray,&normal,sizeof(float)*3);
            normalArray+=3;
       
            aiVector3D pos = mesh->mVertices[face.mIndices[j]];
            memcpy(vertexArray,&pos,sizeof(float)*3);
            vertexArray += 3;

            numVerts += 3;
        }
    }

    normalArray-=mesh->mNumFaces*3*3;
    vertexArray-=mesh->mNumFaces*3*3;

    Model model = { vertexArray, normalArray, numVerts};
    return model;
}