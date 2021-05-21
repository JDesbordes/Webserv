#ifndef UTILS_HPP
#define UTILS_HPP

#include "global.hpp"

std::string ltrim(const std::string& s);
std::string rtrim(const std::string& s);
std::string trim(const std::string& s);
std::vector<std::string> split_parser(std::string str, std::string delimiter);
void parse_error(std::string err, std::string supply);
int noblock(int fd);
std::vector<std::string> split(std::string s, std::string delimiter);
void lower(std::string &s);
t_method_type getType(std::string type);
std::string getStringType(t_method_type type);
int isRegularFile(const char *path);
int isDirectory(const char *path);
int countChar(std::string s, char c);
bool is_number(const std::string& s);

template<typename charT>
struct ci_equal {
    ci_equal(const std::locale& loc) : _loc(loc) {}
    bool operator()(charT ch1, charT ch2)
    {
        return std::toupper(ch1, _loc) == std::toupper(ch2, _loc);
    }
    private:
        const std::locale &_loc;
};

template<typename T>
int ci_find_substr( const T &str1, const T &str2, const std::locale &loc = std::locale())
{
    typename T::const_iterator it = std::search(str1.begin(), str1.end(), str2.begin(), str2.end(), ci_equal<typename T::value_type>(loc));
    if (it != str1.end())
        return (it - str1.begin());
    else
        return (-1);
}

#endif // !UTILS_HPP
