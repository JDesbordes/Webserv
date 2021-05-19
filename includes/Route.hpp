#ifndef ROUTE_HPP
#define ROUTE_HPP

#include "global.hpp"

class Route
{
    public:
        Route();
        Route(const Route &);
        Route &operator=(const Route &);

        void setRoot(std::string root);
        void addMethod(t_method_type type);
        void setAutoIndex(bool autoindex);
        void addIndex(std::string filename);
        void setCGIExtension(std::string ext);
        void setCGIPath(std::string path);
        void setClientMaxBodySize(size_t size);
        void setAuthBasic(std::string name);
        void setAuthBasicUserFile(std::string path);
        void setAuthBasicUserFileList(std::map<std::string, std::string> path);

        std::string &getRoot();
        std::vector<t_method_type> &getMethod();
        bool &getAutoIndex();
        std::vector<std::string> &getIndex();
        std::string &getCGIExtension();
        std::string &getCGIPath();
        size_t &getClientMaxBodySize();
        std::string &getAuthBasic();
        std::string &getAuthBasicUserFile();
        std::map<std::string, std::string> &getAuthBasicUserFileList();

        void debug();

        ~Route();
    private:

        std::string                         _root;
        std::vector<t_method_type>          _method;
        bool                                _autoindex;
        std::vector<std::string>            _index;
        std::string                         _cgi_extension;
        std::string                         _cgi_path;
        size_t                              _client_max_body_size;
        std::string                         _auth_basic;
        std::string                         _auth_basic_user_file;
        std::map<std::string, std::string>  _auth_basic_user_file_list;
};

#endif // !ROUTE_HPP