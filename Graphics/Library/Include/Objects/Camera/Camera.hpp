#ifndef VICTOR_OBJECTS_CAMERA_HPP
#define VICTOR_OBJECTS_CAMERA_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

#include "HabuMath.hpp"

#include "Objects\Object.hpp"
#include "Utils\Vertex.hpp"
#include "Utils\StringUtils.hpp"

using namespace std;

namespace Victor {
    
    class Camera: public Object {
        
        private:
            float farClipPlane;
            float nearClipPlane;
            float verticalFOV;
            float aspectRatio;
            HabuTech::Matrix<float, 4> projectionMatrix;
            
        public:
            Camera(string name);
            Camera();
            ~Camera();
            void changeFOV(float fov);
            Matrix<float, 4>& getProjectionMatrix();
            Matrix<float, 4>& getViewMatrix();
            void init();
            void load(stringstream *ss);
            void render();
            void setFOV(float fov);
            void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ, float upX, float upY, float upZ);
            void setPerspective(float fov, float aspectRatio, float nearClip, float farClip);
            void setAspectRatio(float aspectRatio);
            void updateProjection();
            float getX();
            float getY();
            float getZ();
            
    };
}

#endif VICTOR_OBJECTS_CAMERA_HPP