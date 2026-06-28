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
    // Banner
    // ------------------------------------------------

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);


    showBanner();

    // ------------------------------------------------
    // Create Heap
    // ------------------------------------------------

    MinHeap heap;

    // ------------------------------------------------
    // Load Tasks From File
    // ------------------------------------------------

    vector<Task> tasks =
loadTasks("tasks.txt");

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
    "YOUR_API_KEY_HERE";

    GeminiAPI gemini(apiKey);

    // ------------------------------------------------
    // Generate AI Study Plan
    // ------------------------------------------------

    cout << "\nGenerating AI Study Plan...\n\n";
    int studyHours;

do
{
    cout
    << "How many hours can you study today? ";

    cin >> studyHours;

    if(studyHours <= 0)
    {
        cout
        << "Please enter a valid number of study hours.\n";
    }

} while(studyHours <= 0);
    string prompt =
"Act as an AI Study Planner.\n"
"Create a personalized study schedule.\n"
"Prioritize nearest deadlines and pending tasks.\n"
"Ignore completed tasks.\n"
"Available study hours today: "
+ to_string(studyHours)
+ "\n\n"
"Tasks:\n";
for(const auto& t : heap.getTasks())
{
    prompt +=
        t.subject + " | " +
        t.topic + " | " +
        t.deadline + " | " +
        to_string(t.priority) + " | " +
        t.status + "\n";
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
cout << "\n🤖 AI is analyzing your schedule...\n";
loadingAnimation();
string response =
gemini.generateResponse(prompt);
    cout
    << "=========== AI GENERATED PLAN ===========\n";

    cout
    << response
    << "\n";

    cout
    << "=========================================\n";

    // ------------------------------------------------
    // Menu Loop
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
            // View Study Plan
            // ----------------------------------------

            case 1:

                heap.displayHeap();

                break;

            // ----------------------------------------
            // Dashboard
            // ----------------------------------------

            case 2:

                showDashboard(
                    heap.getTasks()
                );

                break;

            // ----------------------------------------
            // Progress Bar
            // ----------------------------------------

            case 3:

                showProgressBar(
                    heap.getTasks()
                );

                break;

            // ----------------------------------------
            // AI Analysis
            // ----------------------------------------

          case 4:
    showAIAnalysis();
    break;

case 5:
{
    cout << "Enter topic name: ";

    string topic;
    cin >> ws;
    getline(cin, topic);

    bool found = false;

    for(auto& t : heap.getTasks())
    {
        cout << "Task in file : [" << t.topic << "]\n";
        cout << "You entered  : [" << topic << "]\n";

        if(t.topic == topic)
        {
            t.status = "DONE";
            found = true;
            cout << "MATCH FOUND!\n";
        }
    }

    if(!found)
    {
        cout << "Topic not found.\n";
    }

    saveTasks(
        heap.getTasks(),
        "tasks.txt"
    );

    break;
}

            // ----------------------------------------
            // Mark DONE
            // ----------------------------------------

case 6:
{
    cout << "Enter topic name: ";

    string topic;
    cin >> ws;
    getline(cin, topic);

    bool found = false;

    for(auto& t : heap.getTasks())
    {
        if(t.topic == topic)
        {
            t.status = "SKIPPED";
            found = true;
        }
    }

    if(!found)
    {
        cout << "Topic not found.\n";
    }

    saveTasks(
        heap.getTasks(),
        "tasks.txt"
    );

    break;
}

            // ----------------------------------------
            // Replanning
            // ----------------------------------------

           

                case 7:

    cout
    << "AI is analyzing your progress...\n\n";

    for(auto& task : heap.getTasks())
    {
        // Increase priority
        // for unfinished tasks

        if(task.status == "PENDING")
        {
            task.priority--;

            if(task.priority < 1)
            {
                task.priority = 1;
            }
        }
    }

    cout
    << "Replanning completed successfully.\n";

    cout
    << "Pending tasks reprioritized.\n";

    saveTasks(
        heap.getTasks(),
        "tasks.txt"
    );

    break;

            // ----------------------------------------
            // Export
            // ----------------------------------------

            case 8:

    exportPlan(
        heap.getTasks()
    );

    cout
    << "\nStudy plan exported successfully.\n";

    cout
    << "File: study_plan_export.txt\n";

    cout
    << "Location: Project Folder\n";

    break;

            // ----------------------------------------
            // Exit
            // ----------------------------------------

            case 0:

                cout
                << "Saving Progress...\n";

                saveTasks(
                    heap.getTasks(),
                    "tasks.txt"
                );

                running = false;

                break;

            // ----------------------------------------
            // Invalid
            // ----------------------------------------

            default:

                cout
                << "Invalid Option\n";
        }

        cout << "\n";
    }

    return 0;
}