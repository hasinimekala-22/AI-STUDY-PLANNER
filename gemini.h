#ifndef GEMINI_H
#define GEMINI_H

#include <string>

class GeminiAPI {

private:
    std::string apiKey;

public:
    GeminiAPI(std::string key);

    std::string generateResponse(
        const std::string& prompt
    );
};

#endif