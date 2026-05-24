#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;


struct Task {
    string topic;
    string subject;
    string deadline;
    int priority;
    string status; // DONE / PENDING / SKIPPED
};


class GeminiAPI {
private:
    string apiKey;
public:
    GeminiAPI(string key);
    string generateResponse(const string& prompt);
};


static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

GeminiAPI::GeminiAPI(string key) {
    apiKey = key;
}

string GeminiAPI::generateResponse(const string& prompt) {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        string url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent?key=" + apiKey;

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

        
        body["generationConfig"]["responseMimeType"] = "application/json";

        string jsonData = body.dump();
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            cerr << "CURL Error: " << curl_easy_strerror(res) << endl;
        }
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    try {
        json responseJson = json::parse(readBuffer);
        string text = responseJson["candidates"][0]["content"]["parts"][0]["text"];
        return text;
    }
    catch(...) {
       
        return readBuffer.empty() ? "MOCK_ERROR" : readBuffer;
    }
}


Task parseGeminiResponseToTask(const string& modelOutputText) {
    Task task{"Failed Topic", "Failed Subject", "TBD", 5, "PENDING"};
    try {
        json taskJson = json::parse(modelOutputText);
        if (taskJson.contains("topic"))    task.topic = taskJson["topic"].get<string>();
        if (taskJson.contains("subject"))  task.subject = taskJson["subject"].get<string>();
        if (taskJson.contains("deadline")) task.deadline = taskJson["deadline"].get<string>();
        if (taskJson.contains("priority")) task.priority = taskJson["priority"].get<int>();
        if (taskJson.contains("status"))   task.status = taskJson["status"].get<string>();
    } catch (...) {
        cerr << "[Parser Error]: Could not map internal string tokens onto layout keys." << endl;
    }
    return task;
}


int main() {
    cout << "==================================================" << endl;
    cout << "       RUNNING FILE I/O AI PLANNING MODULE        " << endl;
    cout << "==================================================" << endl;

    
    const char* envKey = getenv("GEMINI_API_KEY");
    string apiKey = envKey ? string(envKey) : "MOCK_MODE_KEY";

    GeminiAPI plannerAPI(apiKey);

    string mockServerResponse = 
        "{\n"
        "  \"topic\": \"Asymptotic Time Complexity Analysis\",\n"
        "  \"subject\": \"Computer Science\",\n"
        "  \"deadline\": \"2026-05-30\",\n"
        "  \"priority\": 1,\n"
        "  \"status\": \"PENDING\"\n"
        "}";

    string aiResponseString;

    if (apiKey == "MOCK_MODE_KEY") {
        cout << "[System Notification]: No API Key detected. Simulating server handshake tracking..." << endl;
        aiResponseString = mockServerResponse;
    } else {
        cout << "[Network Action]: Contacting Gemini 2.5 Flash Endpoint..." << endl;
        string userPrompt = "Generate a structured homework task for reviewing Big O notation for algorithms next Friday. Format as a strict json object matching fields topic, subject, deadline, priority as int, and status.";
        aiResponseString = plannerAPI.generateResponse(userPrompt);
    }

  
    cout << "[File IO Action]: Committing raw data payload stream directly to backup logs..." << endl;
    ofstream logFile("raw_gemini_output.json");
    logFile << aiResponseString;
    logFile.close();

    // --- STEP 3: PARSE OBJECT VALUE ARRAYS ---
    cout << "[Parser Action]: Marshaling text variables inside data arrays..." << endl;
    Task integratedTask = parseGeminiResponseToTask(aiResponseString);

  
    cout << "\n================ CORE RUNTIME TASK GENERATED ================" << endl;
    cout << "  Topic:       " << integratedTask.topic << endl;
    cout << "  Subject:     " << integratedTask.subject << endl;
    cout << "  Deadline:    " << integratedTask.deadline << endl;
    cout << "  Priority:    " << integratedTask.priority << " (Max Urgency Tier)" << endl;
    cout << "  Status:      " << integratedTask.status << endl;
    cout << "=============================================================" << endl;

    return 0;
}
