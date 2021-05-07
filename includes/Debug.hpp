#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "global.hpp"

class Debug
{
    public:
        static void error(std::string err);
        static void warning(std::string warn);
        static void checkpoint(std::string cp);
        static void info(std::string info);

        static void error(std::string err, int code);
        static void warning(std::string warn, int code);
        static void checkpoint(std::string cp, int code);
        static void info(std::string info, int code);
        
        static std::string escapestr(std::string str);

        ~Debug();

    private:
        Debug();
        Debug(const Debug &);
        Debug &operator=(const Debug &);
};

#endif // !DEBUG_HPP
