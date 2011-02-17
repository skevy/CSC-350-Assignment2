#include "Utils\Parser.hpp"

#include <vector>

const int LINES_IN_CAMERA = 7;

namespace Victor {
    
    Parser::Parser(string filename) {
        this->filename = filename;
        this->file.open(this->filename.c_str());
    }
    
    Parser::~Parser() {
        
    }

    GraphicsFile Parser::parse() {
        string line;
        vector<string> tokens;

        //get camera
        getline(this->file, line);
        tokens = StringUtils::tokenize(line);
        
        Camera *c = new Camera();
        c->name = tokens.at(1);
        
        for(int i = 0; i < LINES_IN_CAMERA; i++) {
            getline(this->file, line);
            tokens = StringUtils::tokenize(line);
            vector<float> attrs;
            for(int j = 1; j < tokens.size(); j++)
                attrs.push_back(StringUtils::toFloat(tokens.at(j)));
            c->attrs[tokens.at(0)] = attrs;
        }

        //get mesh
        getline(this->file, line);
        tokens = StringUtils::tokenize(line);
        
        Mesh *m = new Mesh();
        m->name = tokens.at(1);
        
        getline(this->file, line);
        m->num_triangles = StringUtils::toInt(line);
        
        getline(this->file, line);
        m->num_verticies = StringUtils::toInt(line);
        
        getline(this->file, line);
        m->num_indicies = StringUtils::toInt(line);
        
        //get the location
        getline(this->file, line);
        tokens = StringUtils::tokenize(line);
        for(int i = 1; i < tokens.size(); i++)
            m->position.push_back(StringUtils::toFloat(tokens.at(i)));
        
        //get the verticies
        for(int i = 0; i < m->num_verticies; i++) {
            getline(this->file, line);
            tokens = StringUtils::tokenize(line);
            map<string, vector<float>> vertex;
            
            vector<float> v;
            for(int i = 1; i <= 3; i++)
                v.push_back(StringUtils::toFloat(tokens.at(i)));
            vertex["v"] = v;
            
            vector<float> n;
            for(int i = 5; i <= 7; i++)
                n.push_back(StringUtils::toFloat(tokens.at(i)));
            vertex["n"] = n;

            m->verticies.push_back(vertex);
        }

        //get the indicies
        for(int i = 0; i < m->num_indicies; i++) {
            getline(this->file, line);
            tokens = StringUtils::tokenize(line);
            m->indicies.push_back(StringUtils::toInt(tokens.at(1)));
        }
                
        this->gf.camera = *c;
        this->gf.mesh = *m;
        
        return this->gf;
    }
}