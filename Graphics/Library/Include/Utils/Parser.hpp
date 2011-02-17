#ifndef VICTOR_UTILS_PARSER_HPP
#define VICTOR_UTILS_PARSER_HPP

#include <string>
#include <iostream>
#include <fstream>

#include "Utils\StringUtils.hpp"
#include "Objects\Mesh.hpp"
#include "Objects\Camera.hpp"

using namespace std;

namespace Victor {

    struct GraphicsFile {
        Camera camera;
        Mesh mesh;
    };
    
    class Parser {
        private:
            string filename;
            GraphicsFile gf;
            ifstream file;
        
        public:            
            Parser(string filename);
            ~Parser();
            
            GraphicsFile parse();
    };
}

#endif VICTOR_UTILS_PARSER_HPP