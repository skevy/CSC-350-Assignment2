#ifndef VICTOR_OBJECTS_OBJECT_HPP
#define VICTOR_OBJECTS_OBJECT_HPP

#include <string>
#include <iostream>
#include <map>
#include <vector>

#include "HabuMath.hpp"

using namespace std;
using namespace HabuTech;

namespace Victor {
    
    class Object {
                
        protected:
            string name;
            float angle[3];
            Vector<float, 4> position;
            Vector<float, 4> rightVector;
            Vector<float, 4> forwardVector;
            Vector<float, 4> upVector;
            Matrix<float, 4> transformMatrix;
        
        public:
            Object(string objectName);
            Object();
            ~Object();
            
            void absolutePitch(float pitch);
            void absoluteRoll(float roll);
            void absoluteYaw(float yaw);
            void advance(float dist);
            void elevate(float dist);
            void forward(float x, float y, float z);
            void move(float x, float y, float z);
            string getName();
            void setName(string name);
            void setPosition(float x, float y, float z);
            void relativePitch(float pitch);
            void relativeRoll(float roll);
            void relativeYaw(float yaw);
            void right(float x, float y, float z);
            void up(float x, float y, float z);
            void strafe(float dist);
            void tranformToModelSpace();
            void tranformToViewSpace();
            
    };
}

#endif VICTOR_OBJECTS_OBJECT_HPP