#include "gemini.h"
#include "json.hpp"

#include <iostream>
#include <sstream>

#include <curl/curl.h>

using json = nlohmann::json;

static size_t WriteCallback(
    void* contents,
    size_t size,
    size_t nmemb,
    void* userp
) {

    ((std::string*)userp)->append(
        (char*)contents,
        size * nmemb
    );

    return size * nmemb;
}

GeminiAPI::GeminiAPI(std::string key) {
    apiKey = key;
}

std::string GeminiAPI::generateResponse(
    const std::string& prompt
) {

    CURL* curl;

    CURLcode res;

    std::string readBuffer;

    curl = curl_easy_init();

    if(curl) {

        // AQ. keys → x-goog-api-key header; legacy AIzaSy keys → ?key= URL param
        std::string url;
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        if (apiKey.rfind("AQ.", 0) == 0) {
            // New auth key format — send via x-goog-api-key header
            url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent";
            std::string apiKeyHeader = "x-goog-api-key: " + apiKey;
            headers = curl_slist_append(headers, apiKeyHeader.c_str());
        } else {
            // Legacy AIzaSy key — pass as URL query parameter
            url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent?key=" + apiKey;
        }

        json body;

        body["contents"] = {
            {
                {
                    "parts",
                    {{
                        {"text", prompt}
                    }}
                }
            }
        };

        std::string jsonData = body.dump();

        curl_easy_setopt(curl, CURLOPT_URL,           url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER,    headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS,    jsonData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA,     &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {

            std::cerr
            << "CURL Error: "
            << curl_easy_strerror(res)
            << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    try {
        // We MUST print the raw buffer to see what Google is complaining about
        std::cout << "\n=== RAW GOOGLE API RESPONSE ===\n" << readBuffer << "\n===============================\n" << std::endl;

        json responseJson = json::parse(readBuffer);
        
        std::string text = responseJson["candidates"][0]["content"]["parts"][0]["text"];
        
        return text;
    }
    catch(const std::exception& e) { 
        // This will print the exact C++ error if it fails
        std::cerr << "JSON Exception: " << e.what() << std::endl;
        return "JSON Parsing Failed";
    }
}