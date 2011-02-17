#include "Utils\Vertex.hpp"

namespace Victor {
    
    Vertex::Vertex() {
        
    }
    
    Vertex::Vertex(Vector<float, 3> &normal, Point<float, 3> &position) {
        this->normal = &normal;
        this->position = &position;
    }

    Vertex::~Vertex() {

    }

}