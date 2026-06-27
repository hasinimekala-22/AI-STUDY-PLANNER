#include <iostream>

#include "gemini.h"

using namespace std;

int main() {

    string apiKey =
        "YOUR_GEMINI_API_KEY_HERE"; // Paste your Gemini API key here (do NOT commit real keys!)

    GeminiAPI ai(apiKey);

    string prompt =
        "Give a 1-day study plan for dsa";

    string response =
        ai.generateResponse(prompt);

    cout << response << endl;

    return 0;
}