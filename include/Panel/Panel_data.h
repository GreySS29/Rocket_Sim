#include <iostream>
#include <sstream>
#include <string>

struct Panel_data {
    int angle{};
    bool launch{};
    bool abort{};

    bool parse(const std::string& data) {
    std::istringstream parser(data);

    std::string angleText;
    std::string launchText;
    std::string abortText;

    if (!std::getline(parser, angleText, ';') ||
        !std::getline(parser, launchText, ';') ||
        !std::getline(parser, abortText)) {
        std::cerr << "Wrong format: [" << data << "]\n";
        return false;
    }


    try {
        angle = std::stoi(angleText);
        launch = std::stoi(launchText) != 0;
        abort = std::stoi(abortText) != 0;
    } catch (const std::exception& error) {
        std::cerr << "Conversion error: " << error.what() << '\n';
        return false;
    }

    return true;
}
};