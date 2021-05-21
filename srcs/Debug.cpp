#include "Debug.hpp"

void Debug::error(std::string err) {
    #ifdef ERR
    if (d == true) { std::cerr << RED << "[ERROR]: " << DGR << err << RST << std::endl; }
    #endif    
    (void)err;
}
void Debug::error(std::string err, int code) {
    #ifdef ERR
    if (d == true) { std::cerr << RED << "[ERROR]: " << DGR << err << " (" << code << ")" << RST << std::endl; }
    #endif
    (void)err;
    (void)code;   
}

void Debug::warning(std::string warn) {
    #ifdef WARN
    if (d == true) { std::cout << YEL << "[WARNING]: " << DGR << warn << RST << std::endl; }
    #endif
    (void)warn;
}
void Debug::warning(std::string warn, int code) {
    #ifdef WARN
    if (d == true) { std::cout << YEL << "[WARNING]: " << DGR << warn << " (" << code << ")" << RST << std::endl; }
    #endif
    (void)warn;
    (void)code; 
}

void Debug::checkpoint(std::string cp) {
    #ifdef CP
    if (d == true) { std::cout << GRE << "[CHECKPOINT]: " << DGR << cp << RST << std::endl; }
    #endif
    (void)cp;
}
void Debug::checkpoint(std::string cp, int code) {
    #ifdef CP
    if (d == true) { std::cout << GRE << "[CHECKPOINT]: " << DGR << cp << " (" << code << ")" << RST << std::endl; }
    #endif
    (void)cp;
    (void)code; 
}

void Debug::info(std::string info) {
    #ifdef INFO
    if (d == true) { std::cout << BLU << "[INFO]: " << DGR << info << RST << std::endl; }
    #endif
    (void)info;
}
void Debug::info(std::string info, int code) {
    #ifdef INFO
    if (d == true) { std::cout << BLU << "[INFO]: " << DGR << info << " (" << code << ")" << RST << std::endl; }
    #endif
    (void)info;
    (void)code; 
}

std::string Debug::escapestr(std::string str) {
    std::string res = "";
    
    for (size_t i = 0; i < str.length();i++)
        if (str.at(i) == '\n')
            res += "\\n";
        else if (str.at(i) == '\r')
            res += "\\r";
        else if (str.at(i) == '\t')
            res += "\\t";
        else if (str.at(i) == '\v')
            res += "\\v";
        else if (str.at(i) == '\0')
            res += "\\0";
        else
            res += str.at(i);
    return (res);
}

Debug::~Debug() {}