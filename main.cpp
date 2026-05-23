#include <iostream>

#include "gemini.h"

using namespace std;

int main() {

    string apiKey =
        ""; // Insert your Gemini API key here

    GeminiAPI ai(apiKey);

    string prompt =
        "Give a 1-day study plan for dsa";

    string response =
        ai.generateResponse(prompt);

    cout << response << endl;

    return 0;
}