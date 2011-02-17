// 3rd Party Includes
#include <GL\glew.h> // Must be called before GL.h

// Platform Includes
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include "Objects\Object.hpp"

namespace Victor {
    Object::Object(string objectName) {
        this->name = objectName;
    }

    Object::Object() {
        
    }

    Object::~Object() {
        
    }
    
    void Object::setPosition(float x, float y, float z) {
        this->position[0] = x;
        this->position[1] = y;
        this->position[2] = z;
    }

    void Object::strafe(float dist) {
        this->position[0] += dist;
    }
    
    void Object::elevate(float dist) {
        this->position[1] += dist;
    }
    
    void Object::advance(float dist) {
        this->position[2] += dist;
    }
    
    void Object::relativePitch(float pitch) {
        this->angle[0] += pitch;
    }
    
    void Object::relativeYaw(float yaw) {
        this->angle[1] += yaw;
    }
    
    void Object::relativeRoll(float roll) {
        this->angle[2] += roll;
    }

}