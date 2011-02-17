#include "Utils\StringUtils.hpp"

namespace Victor {
    
    StringUtils::StringUtils() {
        
    }
    
    vector<string> StringUtils::tokenize(string str) {
        string buf;
        stringstream ss(str);
        
        vector<string> tokens;
        
        while(ss >> buf)
            tokens.push_back(buf);

        return tokens;
    }

    int StringUtils::toInt(string str) {
        int i;
        sscanf(str.c_str(), "%d", &i);
        return i;
    }

    float StringUtils::toFloat(string str) {
        float f = 0;
        sscanf(str.c_str(), "%f", &f);
        return f;
    }

}