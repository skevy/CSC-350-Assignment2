#ifndef VICTOR_SCENES_SCENE_HPP
#define VICTOR_SCENES_SCENE_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

#include "HabuMath.hpp"
#include "Utils\StringUtils.hpp"

#include "Objects\Mesh\Mesh.hpp"
#include "Objects\Camera\Camera.hpp"

using namespace std;

namespace Victor {
    
    class Scene {
                
        private:
            string name;
            string filename;
            float aspectRatio;
            Camera *activeCamera;
            vector<Camera*> cameras;
            vector<Mesh*> meshes;
        
        public:
            Scene(string name, string filename);
            ~Scene();
            
            Camera* getActiveCamera();
            void setAspectRatio(float aspectRatio);
            void load();
            void render();
            
    };
}

#endif VICTOR_SCENES_SCENE_HPP