#include "Model.h"
#include <stdio.h>
#include <stdlib.h>
#include <assimp/Importer.hpp>             
#include <assimp/postprocess.h> 

Model::Model(const std::string& filePath) {
    // Create an instance of the Importer class
    Assimp::Importer importer;

    // Set pointers to nullptr as default.
    vertices = nullptr;
    normals = nullptr;
    
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
    processObject(scene);
}

Model::~Model() {
    if(vertices != nullptr) delete[] vertices;
    if(normals != nullptr) delete[] normals;
}

void Model::setOffset(long offs) {
    offset = offs;
}

long Model::getOffset() {
    return offset;
}

void Model::setModelmatrix(glm::mat4 m) {
    modelmatrix = m;
}

glm::mat4 Model::getModelmatrix(){
    return modelmatrix;
}
// Processes a scene that only consists of one object (one mesh).
void Model::processObject(const aiScene* object) {

    float *vertexArray;
    float *normalArray;

    int numVerts = 0;
    aiMesh* mesh = object->mMeshes[0];

    vertexArray = new float[mesh->mNumFaces*3*3];
    normalArray = new float[mesh->mNumFaces*3*3];

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {

        const aiFace& face = mesh->mFaces[i];
     
        for (int j = 0; j < 3; j++) {

            aiVector3D normal = mesh->mNormals[face.mIndices[j]];
            memcpy(normalArray, &normal, sizeof(float)*3);
            normalArray += 3;
       
            aiVector3D pos = mesh->mVertices[face.mIndices[j]];
            memcpy(vertexArray, &pos, sizeof(float)*3);
            vertexArray += 3;

            numVerts++;
        }
    }
    
    normalArray-=mesh->mNumFaces*3*3;
    vertexArray-=mesh->mNumFaces*3*3;
    
    vertices = vertexArray;
    normals = normalArray;
    numVertices = numVerts;
}