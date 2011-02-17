#ifndef VICTOR_UTILS_VERTEX_HPP
#define VICTOR_UTILS_VERTEX_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "HabuMath.hpp"

using namespace std;
using namespace HabuTech;

namespace Victor {
    class Vertex {
              
        public:
            Vector<float, 3> *normal;
            Point<float, 3> *position;
            float textureUV[2];

            Vertex();
            Vertex(Vector<float, 3> &normal, Point<float, 3> &position);
            ~Vertex();
    };
}

#endif VICTOR_UTILS_VERTEX_HPP