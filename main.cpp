#include <iostream>
#include <windows.h>
#include "task.h"
#include "heap.h"
#include "storage.h"
#include "ui.h"
#include "planner.h"
#include "gemini.h"

using namespace std;

int main()
{
    // ------------------------------------------------
    // Console UTF-8 Setup
    // ------------------------------------------------

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // ------------------------------------------------
    // Splash + Startup Animation
    // ------------------------------------------------

    showBanner();

    // ------------------------------------------------
    // Create Heap
    // ------------------------------------------------

    MinHeap heap;

    // ------------------------------------------------
    // Load Tasks From File
    // ------------------------------------------------

    vector<Task> tasks = loadTasks("tasks.txt");

    // ------------------------------------------------
    // Show Home Card + Urgent Alerts
    // ------------------------------------------------

    showHomeCard("Dhanush");
    showUrgentTasks(tasks);

    // ------------------------------------------------
    // Insert Into Heap
    // ------------------------------------------------

    for(const auto& t : tasks)
    {
        heap.insertTask(t);
    }

    // ------------------------------------------------
    // Gemini API
    // ------------------------------------------------

    string apiKey =
        "AQ.Ab8RN6JeU8sclEO028CU091DRwmh-3jPPgR7q4wHa2Fw-rfm3Q";

    GeminiAPI gemini(apiKey);

    // ------------------------------------------------
    // Study Hours Input
    // ------------------------------------------------

    int studyHours = 0;

    do
    {
        cout << Color::BOLD
             << "\n  How many hours can you study today? › "
             << Color::RESET;

        cin >> studyHours;

        if(studyHours <= 0)
        {
            cout << Color::RED
                 << "  ✗ Please enter a valid number of study hours.\n"
                 << Color::RESET;
        }

    } while(studyHours <= 0);

    // ------------------------------------------------
    // Build Gemini Prompt
    // ------------------------------------------------

    string prompt =
        "Act as an AI Study Planner.\n"
        "Create a personalized study schedule.\n"
        "Prioritize nearest deadlines and pending tasks.\n"
        "Ignore completed tasks.\n"
        "Available study hours today: "
        + to_string(studyHours)
        + "\n\nTasks:\n";

    for(const auto& t : heap.getTasks())
    {
        prompt +=
            t.subject + " | " +
            t.topic   + " | " +
            t.deadline+ " | " +
            to_string(t.priority) + " | " +
            t.status  + "\n";
    }

    prompt +=
        "\nIMPORTANT RULES:\n"
        "1. Use ONLY the tasks listed above.\n"
        "2. Do NOT invent any new subjects or topics.\n"
        "3. Ignore completed tasks while scheduling.\n"
        "4. Create a schedule only for today.\n"
        "5. Allocate study slots within the available study hours.\n"
        "6. Mention completed tasks separately.\n"
        "7. Give a short motivational message.\n"
        "\nOutput format:\n"
        "09:00 - 10:00 : Subject - Topic\n"
        "10:15 - 11:15 : Subject - Topic\n"
        "Reason:\n"
        "- ...\n";

    // ------------------------------------------------
    // AI Agent Thinking + Plan Generation
    // ------------------------------------------------

    cout << "\n  " << Color::CYAN << Color::BOLD
         << "🤖 AI is analyzing your schedule...\n"
         << Color::RESET;

    loadingAnimation();  // showAgentThinking()

    string response = gemini.generateResponse(prompt);

    // ------------------------------------------------
    // Display AI Generated Plan
    // ------------------------------------------------

    cout << Color::CYAN << Color::BOLD
         << "\n  ╔═════════════════════════════════════════╗\n"
         << "  ║        AI GENERATED STUDY PLAN          ║\n"
         << "  ╠═════════════════════════════════════════╣\n"
         << Color::RESET;

    cout << response << "\n";

    cout << Color::CYAN
         << "  ╚═════════════════════════════════════════╝\n"
         << Color::RESET << "\n";

    // ------------------------------------------------
    // Main Menu Loop
    // ------------------------------------------------

    bool running = true;

    while(running)
    {
        showMenu();

        int choice;
        cin >> choice;
        cout << "\n";

        switch(choice)
        {
            // ----------------------------------------
            // 1. View Study Plan
            // ----------------------------------------

            case 1:
                heap.displayHeap();
                break;

            // ----------------------------------------
            // 2. Dashboard
            // ----------------------------------------

            case 2:
                showDashboard(heap.getTasks());
                break;

            // ----------------------------------------
            // 3. Progress Bar
            // ----------------------------------------

            case 3:
                showProgressBar(heap.getTasks());
                break;

            // ----------------------------------------
            // 4. AI Analysis
            // ----------------------------------------

            case 4:
                showAIAnalysis();
                break;

            // ----------------------------------------
            // 5. Mark Task DONE
            // ----------------------------------------

            case 5:
            {
                cout << Color::BOLD
                     << "  Enter topic name › "
                     << Color::RESET;

                string topic;
                cin >> ws;
                getline(cin, topic);

                bool found = false;

                for(auto& t : heap.getTasks())
                {
                    if(t.topic == topic)
                    {
                        t.status = "DONE";
                        found    = true;
                    }
                }

                if(found)
                {
                    cout << Color::GREEN
                         << "  ✓ Marked as DONE: " << topic
                         << Color::RESET << "\n";
                }
                else
                {
                    cout << Color::RED
                         << "  ✗ Topic not found. Check spelling.\n"
                         << Color::RESET;
                }

                saveTasks(heap.getTasks(), "tasks.txt");
                break;
            }

            // ----------------------------------------
            // 6. Skip Task
            // ----------------------------------------

            case 6:
            {
                cout << Color::BOLD
                     << "  Enter topic name › "
                     << Color::RESET;

                string topic;
                cin >> ws;
                getline(cin, topic);

                bool found = false;

                for(auto& t : heap.getTasks())
                {
                    if(t.topic == topic)
                    {
                        t.status = "SKIPPED";
                        found    = true;
                    }
                }

                if(found)
                {
                    cout << Color::YELLOW
                         << "  ⏭  Marked as SKIPPED: " << topic
                         << Color::RESET << "\n";
                }
                else
                {
                    cout << Color::RED
                         << "  ✗ Topic not found. Check spelling.\n"
                         << Color::RESET;
                }

                saveTasks(heap.getTasks(), "tasks.txt");
                break;
            }

            // ----------------------------------------
            // 7. AI Re-plan
            // ----------------------------------------

            case 7:
            {
                showAgentThinking();

                for(auto& task : heap.getTasks())
                {
                    if(task.status == "PENDING")
                    {
                        task.priority--;
                        if(task.priority < 1)
                            task.priority = 1;
                    }
                }

                cout << Color::BRIGHT_GREEN
                     << "  ✓ Replanning complete. Pending tasks reprioritized.\n"
                     << Color::RESET;

                saveTasks(heap.getTasks(), "tasks.txt");
                break;
            }

            // ----------------------------------------
            // 8. Export Study Plan
            // ----------------------------------------

            case 8:
            {
                exportPlan(heap.getTasks());

                cout << Color::BRIGHT_GREEN
                     << "  ✓ Study plan exported successfully.\n"
                     << Color::RESET;

                cout << Color::DIM
                     << "  File     : study_plan_export.txt\n"
                     << "  Location : Project Folder\n"
                     << Color::RESET;
                break;
            }

            // ----------------------------------------
            // 9. Urgent Tasks
            // ----------------------------------------

            case 9:
                showUrgentTasks(heap.getTasks());
                break;

            // ----------------------------------------
            // 0. Save & Exit
            // ----------------------------------------

            case 0:
                saveTasks(heap.getTasks(), "tasks.txt");
                showExitScreen();
                running = false;
                break;

            // ----------------------------------------
            // Invalid
            // ----------------------------------------

            default:
                cout << Color::RED
                     << "  ✗ Invalid option. Choose 0-9.\n"
                     << Color::RESET;
        }

        cout << "\n";
    }

    return 0;
}