// 3rd Party Includes
#include <GL\glew.h> // Must be called before GL.h

// Platform Includes
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include "Objects\Mesh\Mesh.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace Victor {

    int bufferSize = 0;
    
    Mesh::Mesh(string name) : Object(name) {
        this->indexBufferID = 0;
        this->vertexBufferID = 0;
        this->numberOfFaces = 0;
        this->numberOfIndicies = 0;
        this->numberOfVerticies = 0;
        this->setWireframe(true);
        
        this->position[0] = this->position[1] = this->position[2] = 0;
        this->angle[0] = this->angle[1] = this->angle[2] = 0;
    }

    Mesh::Mesh() : Object() {        
        this->indexBufferID = 0;
        this->vertexBufferID = 0;
        this->numberOfFaces = 0;
        this->numberOfIndicies = 0;
        this->numberOfVerticies = 0;
        this->setWireframe(true);
        
        this->position[0] = this->position[1] = this->position[2] = 0;
        this->angle[0] = this->angle[1] = this->angle[2] = 0;
    }

    Mesh::~Mesh() {
        
    }
    
    void Mesh::init() {
        // Create the VBO's
        glGenBuffersARB(1, &this->vertexBufferID);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->vertexBufferID);
        glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(Vertex3D) * this->numberOfVerticies, NULL, GL_STATIC_DRAW);
        glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(Vertex3D) * this->numberOfVerticies, this->vertexArray); // Actually upload the data
        glNormalPointer(GL_FLOAT, sizeof(Vertex3D), BUFFER_OFFSET(12));
        glVertexPointer(3, GL_FLOAT, sizeof(Vertex3D), BUFFER_OFFSET(0));
        
        glGenBuffersARB(1, &indexBufferID); // Generate buffer
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->indexBufferID); // Bind the element array buffer
        glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->numberOfIndicies * sizeof(unsigned long), this->indexArray, GL_STATIC_DRAW);
        glGetBufferParameterivARB(GL_ELEMENT_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &bufferSize);
    }
    
    void Mesh::load(stringstream *ss) {
        string line; 

        getline(*ss, line);
        this->numberOfFaces = StringUtils::toInt(line);
        
        getline(*ss, line);
        this->numberOfVerticies = StringUtils::toInt(line);
        
        getline(*ss, line);
        this->numberOfIndicies = StringUtils::toInt(line);
        
        //get the location
        getline(*ss, line);
        vector<string> tokens;
        tokens = StringUtils::tokenize(line);
        float x = StringUtils::toFloat(tokens.at(0));
        this->setPosition(x, StringUtils::toFloat(tokens.at(1)), StringUtils::toFloat(tokens.at(2)));

        this->vertexArray = new Vertex3D[this->numberOfVerticies];
        this->indexArray = new unsigned long[this->numberOfIndicies];

        //get the verticies
        for(unsigned int i = 0; i < this->numberOfVerticies; i++) {
            getline(*ss, line);
            tokens = StringUtils::tokenize(line);
            this->vertexArray[i].location[0] = StringUtils::toFloat(tokens.at(1));
            this->vertexArray[i].location[1] = StringUtils::toFloat(tokens.at(2));
            this->vertexArray[i].location[2] = StringUtils::toFloat(tokens.at(3));

            this->vertexArray[i].normal[0] = StringUtils::toFloat(tokens.at(5));
            this->vertexArray[i].normal[1] = StringUtils::toFloat(tokens.at(6));
            this->vertexArray[i].normal[2] = StringUtils::toFloat(tokens.at(7));
        }
        
        //get the indicies
        for(unsigned int i = 0; i < this->numberOfIndicies; i++) {
            getline(*ss, line);
            tokens = StringUtils::tokenize(line);
            this->indexArray[i] = (unsigned long)StringUtils::toInt(tokens.at(1));
        }

        this->init();
    }
    
    void Mesh::render(float (&matrixView)[16]) {
        // clear buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        glLoadIdentity();

        // tramsform camera
        glTranslatef(this->position[0], this->position[1], this->position[2]);   //Position
        glRotatef(this->angle[0], 1, 0, 0);   // pitch
        glRotatef(this->angle[1], 0, 1, 0);   // heading
        glRotatef(this->angle[2], 0, 0, 1);   // roll
        
        float matrixModel[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, matrixModel);
        glLoadMatrixf(matrixView);
        glMultMatrixf(matrixModel);
        
        float matrixModelView[16];
        
        glGetFloatv(GL_MODELVIEW_MATRIX, matrixModelView);

        glBindBufferARB(GL_ARRAY_BUFFER_ARB, this->vertexBufferID);
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, this->indexBufferID);

        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        glNormalPointer(GL_FLOAT, sizeof(Vertex3D), BUFFER_OFFSET(12));
        glVertexPointer(3, GL_FLOAT, sizeof(Vertex3D), BUFFER_OFFSET(0));

        glDrawElements(GL_TRIANGLES, this->numberOfIndicies, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
    
    void Mesh::setLOD(unsigned long lod) {
        
    }
    
    void Mesh::setWireframe(bool b) {
        this->isWireframe = b;
        if(this->isWireframe) {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
        }
    }

}