#include "Debug.hpp"

void Debug::error(std::string err) { std::cerr << RED << "[ERROR]: " << DGR << err << RST << std::endl; }
void Debug::error(std::string err, int code) { std::cerr << RED << "[ERROR]: " << DGR << err << " (" << code << ")" << RST << std::endl; }

void Debug::warning(std::string warn) { std::cout << YEL << "[WARNING]: " << DGR << warn << RST << std::endl; }
void Debug::warning(std::string warn, int code) { std::cout << YEL << "[WARNING]: " << DGR << warn << " (" << code << ")" << RST << std::endl; }

void Debug::checkpoint(std::string cp) { std::cout << GRE << "[CHECKPOINT]: " << DGR << cp << RST << std::endl; }
void Debug::checkpoint(std::string cp, int code) { std::cout << GRE << "[CHECKPOINT]: " << DGR << cp << " (" << code << ")" << RST << std::endl; }

void Debug::info(std::string info) { std::cout << BLU << "[INFO]: " << DGR << info << RST << std::endl; }
void Debug::info(std::string info, int code) { std::cout << BLU << "[INFO]: " << DGR << info << " (" << code << ")" << RST << std::endl; }

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