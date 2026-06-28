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
#include <sstream>
#include <ctime>
using namespace std;

// ╔══════════════════════════════════════════════════════════╗
// ║                   COLOR SYSTEM                          ║
// ╚══════════════════════════════════════════════════════════╝

namespace Color
{
    // Reset
    const string RESET       = "\033[0m";

    // Standard colors
    const string RED         = "\033[31m";
    const string GREEN       = "\033[32m";
    const string YELLOW      = "\033[33m";
    const string BLUE        = "\033[34m";
    const string MAGENTA     = "\033[35m";
    const string CYAN        = "\033[36m";
    const string WHITE       = "\033[37m";

    // Bright variants
    const string BRIGHT_RED  = "\033[91m";
    const string BRIGHT_GREEN= "\033[92m";
    const string BRIGHT_CYAN = "\033[96m";
    const string BRIGHT_WHITE= "\033[97m";

    // Styles
    const string BOLD        = "\033[1m";
    const string DIM         = "\033[2m";
    const string UNDERLINE   = "\033[4m";

    // Background
    const string BG_BLUE     = "\033[44m";
    const string BG_CYAN     = "\033[46m";
}

// ╔══════════════════════════════════════════════════════════╗
// ║                  UTILITY HELPERS                        ║
// ╚══════════════════════════════════════════════════════════╝

inline void sleep_ms(int ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}

inline void printLine(const string& ch = "─", int len = 62)
{
    cout << Color::DIM;
    for(int i = 0; i < len; i++) cout << ch;
    cout << Color::RESET << "\n";
}

inline void printDoubleLine(int len = 62)
{
    cout << Color::CYAN << Color::BOLD;
    for(int i = 0; i < len; i++) cout << "═";
    cout << Color::RESET << "\n";
}

inline string getCurrentDate()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    const char* months[] = {
        "January","February","March","April","May","June",
        "July","August","September","October","November","December"
    };
    const char* days[] = {
        "Sunday","Monday","Tuesday","Wednesday",
        "Thursday","Friday","Saturday"
    };
    ostringstream oss;
    oss << days[ltm->tm_wday] << ", "
        << ltm->tm_mday << " "
        << months[ltm->tm_mon] << " "
        << (1900 + ltm->tm_year);
    return oss.str();
}

inline void clearScreen()
{
    cout << "\033[2J\033[H";
}

// ╔══════════════════════════════════════════════════════════╗
// ║               SPLASH SCREEN & STARTUP                   ║
// ╚══════════════════════════════════════════════════════════╝

inline void showSplash()
{
    clearScreen();

    cout << Color::CYAN << Color::BOLD;
    cout << "\n";
    cout << "     █████╗ ██╗\n";
    cout << "    ██╔══██╗██║\n";
    cout << "    ███████║██║\n";
    cout << "    ██╔══██║██║\n";
    cout << "    ██║  ██║██║\n";
    cout << "    ╚═╝  ╚═╝╚═╝\n";
    cout << Color::RESET;

    sleep_ms(300);

    cout << Color::BRIGHT_WHITE << Color::BOLD;
    cout << "    ███████╗████████╗██╗   ██╗██████╗ ██╗   ██╗\n";
    cout << "    ██╔════╝╚══██╔══╝██║   ██║██╔══██╗╚██╗ ██╔╝\n";
    cout << "    ███████╗   ██║   ██║   ██║██║  ██║ ╚████╔╝ \n";
    cout << "    ╚════██║   ██║   ██║   ██║██║  ██║  ╚██╔╝  \n";
    cout << "    ███████║   ██║   ╚██████╔╝██████╔╝   ██║   \n";
    cout << "    ╚══════╝   ╚═╝    ╚═════╝ ╚═════╝    ╚═╝   \n";
    cout << Color::RESET;

    sleep_ms(300);

    cout << Color::GREEN << Color::BOLD;
    cout << "    ██████╗ ██╗      █████╗ ███╗   ██╗███╗   ██╗███████╗██████╗ \n";
    cout << "    ██╔══██╗██║     ██╔══██╗████╗  ██║████╗  ██║██╔════╝██╔══██╗\n";
    cout << "    ██████╔╝██║     ███████║██╔██╗ ██║██╔██╗ ██║█████╗  ██████╔╝\n";
    cout << "    ██╔═══╝ ██║     ██╔══██║██║╚██╗██║██║╚██╗██║██╔══╝  ██╔══██╗\n";
    cout << "    ██║     ███████╗██║  ██║██║ ╚████║██║ ╚████║███████╗██║  ██║\n";
    cout << "    ╚═╝     ╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝\n";
    cout << Color::RESET;

    cout << "\n";
    cout << Color::DIM;
    cout << "    ────────────────────────────────────────────────────────────\n";
    cout << "          Powered by Gemini AI  •  Adaptive Min-Heap Scheduler\n";
    cout << "              Sense  •  Plan  •  Execute  •  Improve\n";
    cout << "    ────────────────────────────────────────────────────────────\n";
    cout << Color::RESET;
    cout << "\n";

    sleep_ms(600);
}

// ╔══════════════════════════════════════════════════════════╗
// ║               STARTUP ANIMATION                         ║
// ╚══════════════════════════════════════════════════════════╝

inline void animateProgressBar(const string& label, int delayMs = 30)
{
    cout << "    " << Color::CYAN << left << setw(30) << label << Color::RESET;
    cout << " [";

    for(int i = 0; i < 20; i++)
    {
        cout << Color::GREEN << "█" << Color::RESET;
        cout.flush();
        sleep_ms(delayMs);
    }

    cout << "] " << Color::BRIGHT_GREEN << "100%" << Color::RESET << "\n";
}

inline void showStartupAnimation()
{
    cout << Color::YELLOW << Color::BOLD
         << "    Initializing AI Core...\n\n"
         << Color::RESET;

    sleep_ms(300);

    animateProgressBar("Loading Gemini Engine",   25);
    animateProgressBar("Loading Heap Scheduler",  20);
    animateProgressBar("Loading Planner",         18);
    animateProgressBar("Loading Database",        22);
    animateProgressBar("Loading Dashboard",       15);

    cout << "\n";
    cout << Color::BRIGHT_GREEN << Color::BOLD
         << "    ✓ AI READY\n"
         << Color::RESET;

    sleep_ms(700);
    clearScreen();
}

// ╔══════════════════════════════════════════════════════════╗
// ║                    HOME SCREEN                          ║
// ╚══════════════════════════════════════════════════════════╝

inline void showBanner()
{
    showSplash();
    showStartupAnimation();
}

inline void showHomeCard(const string& userName = "Dhanush")
{
    cout << "\n";
    cout << Color::CYAN << Color::BOLD;
    cout << "  ┌──────────────────────────────────────────────────────────────┐\n";
    cout << "  │              AI STUDY PLANNER  DASHBOARD                    │\n";
    cout << "  ├──────────────────────────────────────────────────────────────┤\n";
    cout << Color::RESET;

    cout << "  │ " << Color::BOLD << "User         : " << Color::RESET
         << Color::BRIGHT_WHITE << left << setw(47) << userName << Color::RESET << "│\n";

    cout << "  │ " << Color::BOLD << "Date         : " << Color::RESET
         << Color::DIM << left << setw(47) << getCurrentDate() << Color::RESET << "│\n";

    cout << "  │ " << Color::BOLD << "AI Status    : " << Color::RESET
         << Color::BRIGHT_GREEN << left << setw(47) << "ONLINE ●" << Color::RESET << "│\n";

    cout << "  │ " << Color::BOLD << "Scheduler    : " << Color::RESET
         << Color::YELLOW << left << setw(47) << "Min Heap" << Color::RESET << "│\n";

    cout << "  │ " << Color::BOLD << "Model        : " << Color::RESET
         << Color::MAGENTA << left << setw(47) << "Gemini" << Color::RESET << "│\n";

    cout << Color::CYAN;
    cout << "  └──────────────────────────────────────────────────────────────┘\n";
    cout << Color::RESET;
    cout << "\n";
}

// ╔══════════════════════════════════════════════════════════╗
// ║                  STATISTICS CARDS                       ║
// ╚══════════════════════════════════════════════════════════╝

inline void showStatsCards(const vector<Task>& tasks)
{
    int total     = tasks.size();
    int completed = 0;
    int pending   = 0;

    for(const auto& t : tasks)
    {
        if(t.status == "DONE")    completed++;
        else                      pending++;
    }

    int productivity = (total > 0) ? (completed * 100) / total : 0;

    // Row 1: Total & Completed
    cout << "  ┌──────────────────────────┐  ┌──────────────────────────┐\n";
    cout << "  │ " << Color::BOLD << "📚 Total Tasks" << Color::RESET
         << "        " << Color::BRIGHT_WHITE << Color::BOLD << setw(4) << total
         << Color::RESET << " │  │ "
         << Color::BOLD << "✅ Completed" << Color::RESET
         << "          " << Color::BRIGHT_GREEN << Color::BOLD << setw(4) << completed
         << Color::RESET << " │\n";
    cout << "  └──────────────────────────┘  └──────────────────────────┘\n";

    // Row 2: Pending & Productivity
    cout << "  ┌──────────────────────────┐  ┌──────────────────────────┐\n";
    cout << "  │ " << Color::BOLD << "⏳ Pending" << Color::RESET
         << "            " << Color::YELLOW << Color::BOLD << setw(4) << pending
         << Color::RESET << " │  │ "
         << Color::BOLD << "📈 Productivity" << Color::RESET
         << "      " << Color::CYAN << Color::BOLD << setw(3) << productivity << "%"
         << Color::RESET << " │\n";
    cout << "  └──────────────────────────┘  └──────────────────────────┘\n";
    cout << "\n";
}

// ╔══════════════════════════════════════════════════════════╗
// ║                   PROGRESS BAR                          ║
// ╚══════════════════════════════════════════════════════════╝

inline void showProgressBar(const vector<Task>& tasks)
{
    int total     = tasks.size();
    int completed = 0;

    for(const auto& t : tasks)
        if(t.status == "DONE") completed++;

    int pct  = (total > 0) ? (completed * 100) / total : 0;
    int bars = pct / 5; // out of 20

    cout << Color::BOLD << "  Study Progress\n" << Color::RESET;
    cout << "  ";

    for(int i = 0; i < 20; i++)
    {
        if(i < bars)
            cout << Color::GREEN << "█";
        else
            cout << Color::DIM << "░";
    }

    cout << Color::RESET << "  " << Color::BOLD << pct << "%\n" << Color::RESET;
    cout << "  Completed " << Color::BRIGHT_GREEN << completed << Color::RESET
         << " / " << total << " Tasks\n";
    cout << "  Status  ";

    if(pct == 100)
        cout << Color::BRIGHT_GREEN << Color::BOLD << "🏆 All Done!" << Color::RESET;
    else if(pct >= 70)
        cout << Color::GREEN  << "🟢 Great Progress" << Color::RESET;
    else if(pct >= 40)
        cout << Color::YELLOW << "🟡 On Track"       << Color::RESET;
    else
        cout << Color::RED    << "🔴 Needs Attention"<< Color::RESET;

    cout << "\n\n";
}

// ╔══════════════════════════════════════════════════════════╗
// ║                    AI INSIGHTS                          ║
// ╚══════════════════════════════════════════════════════════╝

inline void showAIInsights(const vector<Task>& tasks)
{
    // Compute highest priority pending task
    string topTask    = "None";
    int    bestPri    = 999;
    int    urgentCnt  = 0;
    int    skippedCnt = 0;

    for(const auto& t : tasks)
    {
        if(t.status == "PENDING")
        {
            if(t.priority < bestPri)
            {
                bestPri = t.priority;
                topTask = t.subject;
            }
            if(t.deadline == "Today" || t.deadline == "Tomorrow")
                urgentCnt++;
        }
        if(t.status == "SKIPPED") skippedCnt++;
    }

    int total     = tasks.size();
    int completed = 0;
    for(const auto& t : tasks)
        if(t.status == "DONE") completed++;

    int pending = total - completed;
    int estDays = (pending > 0) ? max(1, pending / 3) : 0;
    int conf    = (total > 0) ? min(99, 60 + (completed * 40 / total)) : 0;

    cout << Color::CYAN << Color::BOLD;
    cout << "  ┌─────────────────────────────────────────────────────────────┐\n";
    cout << "  │                       AI INSIGHTS                          │\n";
    cout << "  ├─────────────────────────────────────────────────────────────┤\n";
    cout << Color::RESET;

    auto insightLine = [](const string& text)
    {
        cout << "  │  " << Color::BRIGHT_GREEN << "✓ " << Color::RESET
             << left << setw(57) << text << "│\n";
    };

    insightLine(topTask != "None"
        ? topTask + " has the highest priority"
        : "All tasks are completed");

    insightLine(to_string(urgentCnt) + " task(s) due today or tomorrow");

    insightLine(skippedCnt > 0
        ? "You skipped " + to_string(skippedCnt) + " task(s) — consider catching up"
        : "No skipped tasks — great discipline!");

    insightLine("Estimated completion: " + to_string(estDays) + " Day(s)");
    insightLine("Confidence Score: " + to_string(conf) + "%");

    cout << Color::CYAN;
    cout << "  └─────────────────────────────────────────────────────────────┘\n";
    cout << Color::RESET << "\n";
}

// ╔══════════════════════════════════════════════════════════╗
// ║                    TASK TABLE                           ║
// ╚══════════════════════════════════════════════════════════╝

inline void displayTasks(const vector<Task>& tasks)
{
    cout << Color::BOLD << Color::CYAN;
    cout << "  ┌────┬────────────┬───────────────────────┬────────────┬──────────┐\n";
    cout << "  │ ID │ SUBJECT    │ TOPIC                 │ DEADLINE   │ STATUS   │\n";
    cout << "  ├────┼────────────┼───────────────────────┼────────────┼──────────┤\n";
    cout << Color::RESET;

    int id = 1;
    for(const auto& t : tasks)
    {
        string statusIcon;
        string statusColor;

        if(t.status == "DONE")
        {
            statusIcon  = "🟢 DONE";
            statusColor = Color::GREEN;
        }
        else if(t.status == "SKIPPED")
        {
            statusIcon  = "🔴 SKIP";
            statusColor = Color::RED;
        }
        else
        {
            statusIcon  = "🟡 PEND";
            statusColor = Color::YELLOW;
        }

        // Truncate long strings for clean columns
        string subject = t.subject.substr(0, 10);
        string topic   = t.topic.substr(0, 21);
        string deadln  = t.deadline.substr(0, 10);

        cout << "  │ "
             << Color::BOLD << left << setw(2) << id << Color::RESET
             << " │ "
             << left << setw(10) << subject
             << " │ "
             << left << setw(21) << topic
             << " │ "
             << Color::DIM << left << setw(10) << deadln << Color::RESET
             << " │ "
             << statusColor << left << setw(8) << statusIcon << Color::RESET
             << " │\n";

        id++;
    }

    cout << Color::CYAN;
    cout << "  └────┴────────────┴───────────────────────┴────────────┴──────────┘\n";
    cout << Color::RESET << "\n";
}

// ╔══════════════════════════════════════════════════════════╗
// ║                  AI AGENT THINKING                      ║
// ╚══════════════════════════════════════════════════════════╝

inline void showAgentThinking()
{
    cout << "\n";
    cout << Color::BOLD << Color::MAGENTA
         << "  ╔══════════════════════════════════╗\n"
         << "  ║          AI  AGENT               ║\n"
         << "  ╚══════════════════════════════════╝\n"
         << Color::RESET;

    struct Step { string label; int delay; };
    vector<Step> steps = {
        {"Sense",        20},
        {"Analyze",      18},
        {"Optimize",     22},
        {"Generate Plan",15}
    };

    for(const auto& s : steps)
    {
        cout << "  " << Color::CYAN << left << setw(16) << s.label
             << Color::RESET << "  ";

        for(int i = 0; i < 20; i++)
        {
            cout << Color::MAGENTA << "█" << Color::RESET;
            cout.flush();
            sleep_ms(s.delay);
        }
        cout << "  " << Color::BRIGHT_GREEN << "✓" << Color::RESET << "\n";
    }

    cout << "\n  " << Color::BRIGHT_GREEN << Color::BOLD
         << "► Plan Ready\n" << Color::RESET << "\n";
}

// ╔══════════════════════════════════════════════════════════╗
// ║                      DASHBOARD                          ║
// ╚══════════════════════════════════════════════════════════╝

inline void showDashboard(const vector<Task>& tasks)
{
    clearScreen();
    showHomeCard();
    showStatsCards(tasks);
    showProgressBar(tasks);
    showAIInsights(tasks);
    displayTasks(tasks);
}

// ╔══════════════════════════════════════════════════════════╗
// ║                   AI ANALYSIS                           ║
// ╚══════════════════════════════════════════════════════════╝

inline void showAIAnalysis()
{
    clearScreen();
    showAgentThinking();

    cout << Color::BOLD << Color::BLUE;
    cout << "  ╔═════════════════════════════════════════════════════════════╗\n";
    cout << "  ║                     AI ANALYSIS                            ║\n";
    cout << "  ╠═════════════════════════════════════════════════════════════╣\n";
    cout << Color::RESET;

    auto line = [](const string& icon, const string& txt)
    {
        cout << "  ║  " << icon << "  " << left << setw(55) << txt << "║\n";
    };

    line("🔍", "Detected backlog in DSA — prioritizing immediately");
    line("⚡", "High-weightage topics moved to top of heap");
    line("📊", "Daily workload dynamically re-balanced");
    line("🎯", "Confidence in plan completion: HIGH");
    line("💡", "Suggestion: 2-hour deep focus session on DSA today");

    cout << Color::BLUE;
    cout << "  ╚═════════════════════════════════════════════════════════════╝\n";
    cout << Color::RESET << "\n";
}

// ╔══════════════════════════════════════════════════════════╗
// ║                  URGENT TASKS                           ║
// ╚══════════════════════════════════════════════════════════╝

inline void showUrgentTasks(const vector<Task>& tasks)
{
    cout << "\n";
    cout << Color::BRIGHT_RED << Color::BOLD;
    cout << "  ═══════════════════════════════════════════════\n";
    cout << "  ⚠  URGENT TASK ALERT\n";
    cout << "  ═══════════════════════════════════════════════\n";
    cout << Color::RESET;

    bool found = false;
    int  idx   = 1;

    for(const auto& t : tasks)
    {
        if(t.status == "PENDING" && t.priority == 1)
        {
            found = true;
            cout << "  " << Color::YELLOW << idx++ << ". " << Color::RESET
                 << Color::BOLD << t.subject << Color::RESET
                 << " — " << t.topic
                 << Color::DIM << "  (" << t.deadline << ")" << Color::RESET
                 << "\n";
        }
    }

    if(!found)
        cout << "  " << Color::GREEN << "✅ No urgent tasks right now.\n" << Color::RESET;

    cout << Color::DIM;
    cout << "  ═══════════════════════════════════════════════\n";
    cout << Color::RESET << "\n";
}

// ╔══════════════════════════════════════════════════════════╗
// ║               DEADLINE NOTIFICATION                     ║
// ╚══════════════════════════════════════════════════════════╝

inline void showNotification(const string& taskName,
                             const string& deadline = "Tomorrow")
{
    cout << "\n";
    cout << Color::YELLOW << Color::BOLD;
    cout << "  ═══════════════════════════════════════════════\n";
    cout << "  ⚠  Deadline " << deadline << "\n";
    cout << "  " << taskName << "\n";
    cout << "  ═══════════════════════════════════════════════\n";
    cout << Color::RESET << "\n";
}

// ╔══════════════════════════════════════════════════════════╗
// ║                      MAIN MENU                          ║
// ╚══════════════════════════════════════════════════════════╝

inline void showMenu()
{
    cout << Color::CYAN << Color::BOLD;
    cout << "\n  ╔══════════════════════════════════════════════╗\n";
    cout << "  ║                 MAIN MENU                   ║\n";
    cout << "  ╠══════════════════════════════════════════════╣\n";
    cout << Color::RESET;

    auto item = [](const string& num, const string& icon, const string& label)
    {
        cout << "  ║  " << Color::BOLD << Color::YELLOW << num << Color::RESET
             << "  " << icon << "  "
             << left << setw(36) << label
             << Color::CYAN << "║\n" << Color::RESET;
    };

    item("1", "📚", "View Study Plan");
    item("2", "📊", "Dashboard");
    item("3", "📈", "Progress");
    item("4", "🤖", "AI Analysis");
    item("5", "✅", "Mark Task Completed");
    item("6", "⏭ ", "Skip Task");
    item("7", "🔄", "AI Re-plan");
    item("8", "💾", "Export Study Plan");
    item("9", "📅", "Urgent Tasks");
    item("0", "🚪", "Save & Exit");

    cout << Color::CYAN;
    cout << "  ╚══════════════════════════════════════════════╝\n";
    cout << Color::RESET;

    cout << "\n  " << Color::BOLD << "Enter choice › " << Color::RESET;
}

// ╔══════════════════════════════════════════════════════════╗
// ║                    EXIT SCREEN                          ║
// ╚══════════════════════════════════════════════════════════╝

inline void showExitScreen()
{
    cout << "\n";
    cout << Color::CYAN << "  Saving Tasks...\n" << Color::RESET;
    cout << "  ";
    for(int i = 0; i < 28; i++)
    {
        cout << Color::GREEN << "█" << Color::RESET;
        cout.flush();
        sleep_ms(18);
    }
    cout << "  " << Color::BOLD << "100%\n" << Color::RESET;

    sleep_ms(200);

    cout << Color::CYAN << "  Exporting Progress...\n" << Color::RESET;
    cout << "  ";
    for(int i = 0; i < 28; i++)
    {
        cout << Color::GREEN << "█" << Color::RESET;
        cout.flush();
        sleep_ms(15);
    }
    cout << "  " << Color::BOLD << "100%\n" << Color::RESET;

    sleep_ms(300);

    cout << "\n  " << Color::BRIGHT_GREEN << Color::BOLD
         << "✓ Session Saved Successfully\n" << Color::RESET;
    cout << "  " << Color::DIM << "See you tomorrow!\n" << Color::RESET;

    cout << "\n";
    cout << Color::DIM;
    cout << "  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    cout << Color::RESET;

    cout << Color::CYAN << Color::BOLD;
    cout << "               AI Study Planner\n";
    cout << Color::RESET;
    cout << Color::DIM;
    cout << "          Keep Learning. Keep Growing.\n";
    cout << "  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    cout << Color::RESET << "\n";
}

// ╔══════════════════════════════════════════════════════════╗
// ║              LOADING ANIMATION (RE-PLAN)                ║
// ╚══════════════════════════════════════════════════════════╝

inline void loadingAnimation()
{
    showAgentThinking();
}

#endif