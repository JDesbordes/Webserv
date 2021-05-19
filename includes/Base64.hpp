#ifndef __BASE64_H__
#define __BASE64_H__

#include "global.hpp"

class Base64
{
public:
    static std::string Encode(const std::string data);
    static std::string Decode(const std::string &input, std::string &out);
};

#endif // __BASE64_H__