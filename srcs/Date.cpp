#include "Date.hpp"

Date::Date() {}
Date::~Date() {}

std::string Date::operator()()
{
    char buff[64];
    std::string res = "Date: ";
    
    struct timeval tv;
    struct timezone tz;
    tz.tz_minuteswest = 0;
    tz.tz_dsttime = DST_NONE;
    gettimeofday(&tv, &tz);
    time_t ttime = tv.tv_sec;
    struct tm *time = localtime(&ttime);
    strftime(buff, sizeof(buff), "%a, %d %b %Y %X", time);
    res += std::string(buff) + " GMT";
    Debug::info("RES=" + res);
    return (res);
}