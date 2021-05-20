#include "HttpError.hpp"

std::string HttpError::getPage(Server *serv, HttpParser *parser) {
    std::string err = "";
    bool f = false;

    std::map<int, std::string> pages = serv->getErrorPage();
    if (pages.find(parser->getErrno()) != pages.end()) {
        std::string line;
        std::ifstream file(pages.find(parser->getErrno())->second);
        if (file.is_open()) {
            while (getline(file, line))
                err += line;
            file.close();
        }
    }
    if (!f)
        err = getDefaultPage(parser->getErrno());
    return (err);
}

std::string HttpError::getDefaultPage(int err) {
    switch (err) {
        case 400:
            return (DEFAULT_400_PAGE);
            break;
        case 401:
            return (DEFAULT_401_PAGE);
            break;
        case 403:
            return (DEFAULT_403_PAGE);
            break;
        case 404:
            return (DEFAULT_404_PAGE);
            break;
        case 405:
            return (DEFAULT_405_PAGE);
            break;
        case 413:
            return (DEFAULT_413_PAGE);
            break;
        case 501:
            return (DEFAULT_501_PAGE);
            break;
        default:
            return (DEFAULT_500_PAGE);
            break;
        // TODO Check all handled
    }
}

std::string HttpError::getStatusMsg(int err) {
    switch (err) {
        case 200:
            return (DEFAULT_200_MSG);
            break;
        case 201:
            return (DEFAULT_201_MSG);
            break;
        case 204:
            return (DEFAULT_204_MSG);
            break;
        case 400:
            return (DEFAULT_400_MSG);
            break;
        case 401:
            return (DEFAULT_401_MSG);
            break;
        case 403:
            return (DEFAULT_403_MSG);
            break;
        case 404:
            return (DEFAULT_404_MSG);
            break;
        case 405:
            return (DEFAULT_405_MSG);
            break;
        case 413:
            return (DEFAULT_413_MSG);
            break;
        case 501:
            return (DEFAULT_501_MSG);
            break;
        default:
            return (DEFAULT_500_MSG);
            break;
        // TODO Check all handled
    }
}
