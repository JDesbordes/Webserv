#ifndef TYPEDEFS_HPP
#define TYPEDEFS_HPP

#include "global.hpp"

typedef enum e_method_type {
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE,
    PATCH,
    ERROR
} t_method_type;

typedef struct s_method {
    t_method_type type;
    std::string path;
    std::string args;
} t_method;

#endif
