#ifndef VICTOR_OBJECTS_MESH_HPP
#define VICTOR_OBJECTS_MESH_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include "HabuMath.hpp"

#include "Objects\Object.hpp"
#include "Utils\Vertex.hpp"
#include "Utils\StringUtils.hpp"

using namespace std;

namespace Victor {

    struct Vertex3D {
        float location[3];
        float normal[3];
    };

    class Mesh: public Object {              
        
        private:
            bool isWireframe;
            
            Vertex3D *vertexArray;
            unsigned long *indexArray;
            
            unsigned int indexBufferID;
            unsigned int vertexBufferID;
            unsigned long numberOfFaces;
            unsigned long numberOfIndicies;
            unsigned long numberOfVerticies;
              
        public:
            Mesh(string name);
            Mesh();
            ~Mesh();
            void init();
            void load(stringstream *ss);
            void render(float (&matrixView)[16]);
            void setLOD(unsigned long lod);
            void setWireframe(bool b);
    };
}

#endif VICTOR_OBJECTS_MESH_HPP