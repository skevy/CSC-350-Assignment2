// 3rd Party Includes
#include <GL\glew.h> // Must be called before GL.h

// Platform Includes
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include "Scenes\Scene.hpp"

namespace Victor {
    
    Scene::Scene(string name, string filename) {
        this->name = name;
        this->filename = filename;
        this->aspectRatio = 640.f / 480.f;
    }

    Scene::~Scene() {
        
    }
    
    void Scene::setAspectRatio(float aspectRatio) {
        this->aspectRatio = aspectRatio;
    }
    
    void Scene::load() {
        int numLinesInCamera = 8;
        int numLinesInMesh = 2;
        
        ifstream file;
        file.open(this->filename.c_str());

        while(!file.eof()) {
            string dataType;
            
            file >> dataType;
            if(dataType == "Camera") { //get camera
                string name;
                file >> name;
                stringstream ss;
                for(int i = 0; i < numLinesInCamera; i++) {
                    string str;
                    getline(file, str);
                    ss << str << endl;
                }
                Camera *c = new Camera(name);
                c->setAspectRatio(this->aspectRatio);
                c->load(&ss);
                this->cameras.push_back(c);
            } else if (dataType == "Mesh") { //get mesh
                string name;
                stringstream ss;
            
                file >> name;
            
                int numTriangles;
                file >> numTriangles;
                ss << numTriangles << endl;
            
                int numVerticies;
                file >> numVerticies;
                ss << numVerticies << endl;
            
                int numIndicies;
                file >> numIndicies;
                ss << numIndicies;
            
                numLinesInMesh += numIndicies + numVerticies;
                for(int i = 0; i < numLinesInMesh; i++) {
                    string str;
                    getline(file, str);
                    ss << str << endl; //Put location in stream
                }
                Mesh *m = new Mesh(name);
                m->load(&ss);
                this->meshes.push_back(m);
            }
        }                      
        
        this->activeCamera = this->cameras[0];
        
        return;
    }
    
    Camera* Scene::getActiveCamera() {
        return this->activeCamera;
    }
    
    void Scene::render() {
        glPushMatrix();
        
        this->activeCamera->render();
        
        float matrixView[16];
        
        glGetFloatv(GL_MODELVIEW_MATRIX, matrixView);
        
        for(int i = 0; i < 1; i++) {
            meshes[i]->render(matrixView);
        }
        
        glPopMatrix();
        return;
    }
}