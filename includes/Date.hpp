#ifndef DATE_HPP
#define DATE_HPP

#include "global.hpp"

class Date {
    public:
        std::string operator()(int fd);

    private:
        Date();
        Date(const Date &);
        Date &operator=(const Date &);
        ~Date();
};

#endif // !DATE_HPP