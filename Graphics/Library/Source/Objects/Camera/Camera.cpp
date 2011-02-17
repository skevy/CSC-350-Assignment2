// 3rd Party Includes
#include <GL\glew.h> // Must be called before GL.h

// Platform Includes
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include "Objects\Camera\Camera.hpp"

namespace Victor {

    Camera::Camera(string name) : Object(name) {
        this->position[0] = this->position[1] = this->position[2] = 0;
        this->angle[0] = this->angle[1] = this->angle[2] = 0;
    }
    
    Camera::Camera() : Object() {
        this->position[0] = this->position[1] = this->position[2] = 0;
        this->angle[0] = this->angle[1] = this->angle[2] = 0;
    }

    Camera::~Camera() {
        
    }
    
    void Camera::setAspectRatio(float aspectRatio) {
        this->aspectRatio = aspectRatio;
    }
    
    void Camera::setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ, float upX, float upY, float upZ) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, upX, upY, upZ); // eye(x,y,z), focal(x,y,z), up(x,y,z)
    }
    
    void Camera::setPerspective(float fov, float aspectRatio, float nearClip, float farClip) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fov, aspectRatio, nearClip, farClip);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    
    void Camera::init() {
        this->setPerspective(this->verticalFOV, this->aspectRatio, this->nearClipPlane, this->farClipPlane);
        this->setCamera(this->position[0], this->position[1], this->position[2], this->forwardVector[0], this->forwardVector[1], this->forwardVector[2], this->upVector[0], this->upVector[1], this->upVector[2]);
    }
    
    void Camera::load(stringstream *ss) {
        string line;
        while(getline(*ss, line), !ss->eof()) {
            if(line != "") {
                vector<string> tokens;
                tokens = StringUtils::tokenize(line);
                if(tokens.at(0) == "Right") {
                    this->rightVector[0] = StringUtils::toFloat(tokens.at(1));
                    this->rightVector[1] = StringUtils::toFloat(tokens.at(2));
                    this->rightVector[2] = StringUtils::toFloat(tokens.at(3));
                } else if(tokens.at(0) == "Up") {
                    this->upVector[0] = StringUtils::toFloat(tokens.at(1));
                    this->upVector[1] = StringUtils::toFloat(tokens.at(2));
                    this->upVector[2] = StringUtils::toFloat(tokens.at(3));
                } else if(tokens.at(0) == "Forward") {
                    this->forwardVector[0] = StringUtils::toFloat(tokens.at(1));
                    this->forwardVector[1] = StringUtils::toFloat(tokens.at(2));
                    this->forwardVector[2] = StringUtils::toFloat(tokens.at(3));
                } else if(tokens.at(0) == "Loc") {
                    this->position[0] = StringUtils::toFloat(tokens.at(1));
                    this->position[1] = StringUtils::toFloat(tokens.at(2));
                    this->position[2] = StringUtils::toFloat(tokens.at(3));
                } else if(tokens.at(0) == "Far") {
                    this->farClipPlane = StringUtils::toFloat(tokens.at(1));
                } else if(tokens.at(0) == "Near") {
                    this->nearClipPlane = StringUtils::toFloat(tokens.at(1));
                } else if(tokens.at(0) == "FOV") {
                    this->verticalFOV = StringUtils::toFloat(tokens.at(1)) * 57.2957795f; //convert radians to degrees
                }
            }
        }
        this->init();
        return;
    }

    void Camera::render() {
        glLoadIdentity();
        
        glRotatef(-this->angle[0], 1, 0, 0); // pitch
        glRotatef(-this->angle[1], 0, 1, 0); // heading
        glRotatef(-this->angle[2], 0, 0, 1); // roll
        glTranslatef(-this->position[0], -this->position[1], -this->position[2]);
            
        return;
    }
}