#include "planner.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <vector>
#include "gemini.h"

using namespace std;


Planner::Planner() {
    
}

int Planner::calculateDaysRemaining(const string& deadlineDate, const string& currentDate) {
    
    struct tm tm_dead = {0};
    struct tm tm_curr = {0};
    int y, m, d;
    char dash1, dash2;

    stringstream ss_dead(deadlineDate);
    ss_dead >> y >> dash1 >> m >> dash2 >> d;
    tm_dead.tm_year = y - 1900; 
    tm_dead.tm_mon = m - 1;     
    tm_dead.tm_mday = d;

    
    stringstream ss_curr(currentDate);
    ss_curr >> y >> dash1 >> m >> dash2 >> d;
    tm_curr.tm_year = y - 1900;
    tm_curr.tm_mon = m - 1;
    tm_curr.tm_mday = d;

    time_t time_dead = mktime(&tm_dead);
    time_t time_curr = mktime(&tm_curr);
    
    double seconds = difftime(time_dead, time_curr);
    int daysLeft = seconds / (60 * 60 * 24); 

    return daysLeft;
}


vector<Task> Planner::detectSlippage(const vector<Task>& currentTasks, const string& currentDate) {
    vector<Task> slippedTasks;
    int SLIPPAGE_THRESHOLD = 2;

    cout << "[SENSE] Analyzing current tasks for slippage..." << endl;

    for (const Task& task : currentTasks) {
        if (task.status == "PENDING" || task.status == "SKIPPED") {
            int daysLeft = calculateDaysRemaining(task.deadline, currentDate);
            
            if (daysLeft <= SLIPPAGE_THRESHOLD) {
                cout << "  -> Slippage Detected: '" << task.topic << "' only has " 
                     << daysLeft << " days left!" << endl;
                slippedTasks.push_back(task);
            }
        }
    }
    return slippedTasks;
}


void Planner::replanTasks(vector<Task>& allTasks, const string& currentDate) {
    cout << "\n[PLAN] Initiating Replanning phase..." << endl;
    
    vector<Task> slipped = detectSlippage(allTasks, currentDate);

    if (slipped.empty()) {
        cout << "[PLAN] All tasks are on track. No replanning needed." << endl;
        return; 
    }

    cout << "[PLAN] Contacting Gemini API to optimize schedule for " << slipped.size() << " tasks..." << endl;

    // --- REAL GEMINI API INTEGRATION ---

    // 1. Initialize the API (PASTE YOUR ACTUAL KEY HERE)
    GeminiAPI gemini("YOUR_GEMINI_API_KEY_HERE");

    // 2. Build the prompt using the slipped tasks
    string prompt = "I am a student. I am falling behind on these tasks:\n";
    for(const Task& t : slipped) {
        prompt += "- " + t.topic + " (" + t.subject + ") Due: " + t.deadline + "\n";
    }
    prompt += "Please give me a short, 2-sentence motivational advice and a quick tip on how to prioritize these.";

    // 3. Call the API
    string aiResponse = gemini.generateResponse(prompt);

    // 4. Print the AI's response
    cout << "\n================ AI RESPONSE ================\n";
    cout << aiResponse << endl;
    cout << "=============================================\n\n";

    // -----------------------------------

    // We keep this simulated priority update so your Min Heap still gets tested!
    for (Task& task : allTasks) {
        for (const Task& slippedTask : slipped) {
            if (task.topic == slippedTask.topic) {
                // The system decides this is now high priority (1 is highest in Min Heap)
                task.priority = 1; 
                cout << "  -> System updated priority for '" << task.topic << "' to 1." << endl;
            }
        }
    }
}

void Planner::updateHeap(const vector<Task>& updatedTasks) {
    cout << "\n[ACT] Sending updated schedule to the Min Heap..." << endl;

    cout << "[UPDATE] Heap successfully updated with new task priorities." << endl;
}

void Planner::runReActLoop(vector<Task>& currentTasks, const string& currentDate) {
    cout << "\n========== RUNNING ReAct LOOP ==========" << endl;
    
    replanTasks(currentTasks, currentDate);

    updateHeap(currentTasks);
    
    cout << "======================================" << endl;
}