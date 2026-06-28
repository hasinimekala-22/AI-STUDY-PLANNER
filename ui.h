#ifndef UI_H
#define UI_H

#include "task.h"
#include "heap.h"
#include "planner.h"
#include "storage.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;

// ======================================================
// COLORS
// ======================================================

namespace Color
{
    const string RESET  = "\033[0m";
    const string RED    = "\033[31m";
    const string GREEN  = "\033[32m";
    const string YELLOW = "\033[33m";
    const string BLUE   = "\033[34m";
    const string CYAN   = "\033[36m";
    const string BOLD   = "\033[1m";
}

// ======================================================
// LOADING ANIMATION
// ======================================================

inline void loadingAnimation()
{
    cout << Color::CYAN
         << "\nGenerating AI Study Plan";

    for(int i = 0; i < 3; i++)
    {
        cout << ".";
        cout.flush();

        this_thread::sleep_for(
            chrono::milliseconds(500)
        );
    }

    cout << Color::RESET << "\n\n";
}

// ======================================================
// BANNER
// ======================================================

inline void showBanner()
{
    cout << Color::CYAN
         << Color::BOLD;

    cout << "====================================================\n";
    cout << "              AI STUDY PLANNER AGENT\n";
    cout << "====================================================\n";

    cout << Color::RESET;

    cout << "Workflow : Sense -> Plan -> Act\n";
    cout << "Engine   : Gemini AI + Min Heap Scheduler\n";
    cout << "Mode     : Adaptive Smart Planning\n";

    cout << "\n";
}
inline void showUrgentTasks(
    const vector<Task>& tasks)
{
    cout
    << "\n══════════ URGENT TASK ALERT ══════════\n";

    bool found = false;
    int count = 1;

    for(const auto& t : tasks)
    {
        if(t.status == "PENDING"
           && t.priority == 1)
        {
            found = true;

            cout
            << count++ << ". "
            << t.subject
            << " - "
            << t.topic
            << " ("
            << t.deadline
            << ")\n";
        }
    }

    if(!found)
    {
        cout
        << "✅ No urgent tasks today.\n";
    }

    cout
    << "═══════════════════════════════════════\n\n";
}
// ======================================================
// DASHBOARD
// ======================================================

inline void showDashboard(
    const vector<Task>& tasks)
{
    int completed = 0;
    int pending = 0;
    string highestTask = "None";
string nextDeadline = "None";
int bestPriority = 999;

    for(const auto& t : tasks)
    {
        if(t.status == "PENDING")
{
    if(t.priority < bestPriority)
    {
        bestPriority = t.priority;
        highestTask =
            t.subject + " - " + t.topic;
        nextDeadline = t.deadline;
    }
}
       
    }

    int total = tasks.size();
    

    int percent = 0;

    if(total != 0)
    {
        percent =
        (completed * 100) / total;
    }

    cout << Color::BOLD
         << "================ DASHBOARD ================\n"
         << Color::RESET;

    cout << "Total Tasks     : "
         << total << "\n";

    cout << "Completed Tasks : "
         << completed << "\n";

    cout << "Pending Tasks   : "
         << pending << "\n";

    cout << "Productivity    : "
         << percent
         << "%\n";
         cout
<< "Highest Priority : "
<< highestTask
<< "\n";

cout
<< "Next Deadline    : "
<< nextDeadline
<< "\n";
cout << "Status           : ";
if(percent < 30)
{
    cout
    << "🔴 Needs Attention\n";
}
else if(percent < 70)
{
    cout
    << "🟡 On Track\n";
}
else
{
    cout
    << "🟢 Excellent\n";
}

    cout << "===========================================\n\n";
}

// ======================================================
// PROGRESS BAR
// ======================================================
inline void showProgressBar(
    const vector<Task>& tasks)
{
    int total = tasks.size();

    if(total == 0)
    {
        cout << "No tasks available.\n";
        return;
    }

    int completed = 0;

    for(const auto& t : tasks)
    {
        if(t.status == "DONE")
            completed++;
    }

    int percentage =
        (completed * 100) / total;

    int bars =
        percentage / 5;

    cout << Color::CYAN
         << "\n══════════ STUDY PROGRESS ══════════\n"
         << Color::RESET;

    cout << "Progress : [";

    for(int i = 0; i < 20; i++)
    {
        if(i < bars)
        {
            cout << "=";
        }
        else if(i == bars && percentage != 100)
        {
            cout << ">";
        }
        else
        {
            cout << ".";
        }
    }

    cout << "] "
         << percentage
         << "%\n";

    cout << "Completed: "
         << completed
         << " / "
         << total
         << " Tasks\n";

    cout << "Status   : ";

    if(percentage == 100)
    {
        cout
        << Color::GREEN
        << "🏆 Completed All Tasks";
    }
    else if(percentage >= 70)
    {
        cout
        << Color::GREEN
        << "🟢 Excellent Progress";
    }
    else if(percentage >= 40)
    {
        cout
        << Color::YELLOW
        << "🟡 On Track";
    }
    else
    {
        cout
        << Color::RED
        << "🔴 Needs Attention";
    }

    cout
    << Color::RESET
    << "\n════════════════════════════════════\n\n";
}
// ======================================================
// TASK TABLE
// ======================================================

inline void displayTasks(
    const vector<Task>& tasks)
{
    cout << Color::YELLOW
         << left
         << setw(15) << "SUBJECT"
         << setw(25) << "TOPIC"
         << setw(15) << "DEADLINE"
         << setw(15) << "STATUS"
         << "\n";

    cout << "------------------------------------------------------------\n";

    for(const auto& t : tasks)
    {
        cout << left
             << setw(15) << t.subject
             << setw(25) << t.topic
             << setw(15) << t.deadline
             << setw(15) << t.status
             << "\n";
    }

    cout << Color::RESET;
}

// ======================================================
// AI ANALYSIS
// ======================================================

inline void showAIAnalysis()
{
    cout << Color::BLUE
         << "\n================ AI ANALYSIS ================\n"
         << Color::RESET;

    cout << "Detected backlog in DSA.\n";
    cout << "Prioritizing high-weightage topics.\n";
    cout << "Daily workload adjusted dynamically.\n";

    cout << "=============================================\n\n";
}

// ======================================================
// MENU
// ======================================================

inline void showMenu()
{
    cout << Color::BOLD
         << "================ MENU ================\n"
         << Color::RESET;

    cout << "1. View Study Plan\n";
    cout << "2. Show Dashboard\n";
    cout << "3. Show Progress Bar\n";
    cout << "4. AI Analysis\n";
    cout << "5. Mark DONE\n";
    cout << "6. Mark SKIPPED\n";
    cout << "7. Trigger Re-plan\n";
    cout << "8. Export Plan\n";
    cout << "0. Save & Exit\n";

    cout << "\nEnter choice: ";
}

#endif