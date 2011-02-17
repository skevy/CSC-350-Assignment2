#ifndef VICTOR_UTILS_STRINGUTILS_HPP
#define VICTOR_UTILS_STRINGUTILS_HPP

#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

namespace Victor {
    class StringUtils {        
        public:            
            StringUtils();
            ~StringUtils();
            
            static vector<string> tokenize(string str);

            static int toInt(string str);
            static float toFloat(string str);
    };
}

#endif VICTOR_UTILS_STRINGUTILS_HPP