#ifndef DATE_HPP
#define DATE_HPP

#include "global.hpp"

class Date {
    public:
        Date();
        std::string operator()();
        ~Date();

    private:
        Date(const Date &);
        Date &operator=(const Date &);
};

#endif // !DATE_HPP