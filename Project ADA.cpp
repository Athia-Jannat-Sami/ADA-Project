#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

#ifdef _WIN32
  #define CLEAR "cls"
#else
  #define CLEAR "clear"
#endif

// Function to clear the console screen
void clearScreen() {
    system(CLEAR);
}

// Function to print the selected activities
void printSelectedActivities(const vector<int>& selected) {
    cout << "Selected activities: ";
    for (int activity : selected) {
        cout << activity << " ";
    }
    cout << "\n";
}

// Function to print the activity table (with activity number, start time, and end time)
void printActivityTable(const vector<pair<int, pair<int, int>>>& activities, const vector<int>& selected) {
    cout << "Activity | Start | End  | Selected\n";
    cout << "------------------------------------\n";
    for (int i = 0; i < activities.size(); i++) {
        bool isSelected = (find(selected.begin(), selected.end(), activities[i].first) != selected.end());
        cout << "   " << activities[i].first << "    |  " << activities[i].second.first
             << "  | " << activities[i].second.second
             << " | " << (isSelected ? "Yes" : "No") << "\n";
    }
    cout << "\n";
}

// Function to perform activity selection and visualize the process
void activitySelection(vector<pair<int, pair<int, int>>>& activities) {
    // Sort activities by their finish time
    sort(activities.begin(), activities.end(), [](const auto& a, const auto& b) {
        return a.second.second < b.second.second;
    });

    vector<int> selected;
    int lastSelected = -1;

    // Select the first activity
    selected.push_back(activities[0].first);
    lastSelected = 0;

    // Display the first selection
    clearScreen();
    cout << "Selecting activity: " << activities[0].first << " (Start: " << activities[0].second.first
         << ", End: " << activities[0].second.second << ")\n";
    printActivityTable(activities, selected);
    this_thread::sleep_for(chrono::milliseconds(1000));

    // Loop through remaining activities
    for (int i = 1; i < activities.size(); i++) {
        clearScreen();
        // If the current activity doesn't overlap, select it
        if (activities[i].second.first >= activities[lastSelected].second.second) {
            selected.push_back(activities[i].first);
            lastSelected = i;
            cout << "Selecting activity: " << activities[i].first << " (Start: " << activities[i].second.first
                 << ", End: " << activities[i].second.second << ")\n";
        } else {
            cout << "Skipping activity: " << activities[i].first << " (Start: " << activities[i].second.first
                 << ", End: " << activities[i].second.second << ")\n";
        }
        printActivityTable(activities, selected);
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    cout << "Final selected activities: ";
    for (int activity : selected) {
        cout << activity << " ";
    }
    cout << "\n";
}

int main() {
    int n;

    // Ask user for the number of activities
    cout << "Enter the number of activities: ";
    cin >> n;

    vector<pair<int, pair<int, int>>> activities;

    // Input activities from the user
    for (int i = 0; i < n; i++) {
        int start, end;
        cout << "Enter start time and end time for activity " << i + 1 << ": ";
        cin >> start >> end;
        activities.push_back({i + 1, {start, end}});
    }

    // Call the function to perform activity selection
    activitySelection(activities);

    return 0;
}

