#include "scheduler.h"
#include <bits/stdc++.h>

// Global variables for storing results (for simplicity)
vector<int> finishTime;
vector<int> turnAroundTime;
vector<double> normTurn;

using namespace std;

void fcfs(const vector<Process>& processes) {
    cout << "Executing First Come First Serve algorithm\n";

    int process_count = processes.size();
    finishTime.resize(process_count);
    turnAroundTime.resize(process_count);
    normTurn.resize(process_count);
    timeline.resize(process_count, vector<char>(100, '.')); // Assuming max timeline of 100 units

    // Copy the processes to a local vector to sort them
    vector<Process> sorted_processes = processes;

    // Sort processes by arrival time
    sort(sorted_processes.begin(), sorted_processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    int time = sorted_processes[0].arrival_time;

    for (int i = 0; i < process_count; i++) {
        int arrivalTime = sorted_processes[i].arrival_time;
        int serviceTime = sorted_processes[i].burst_time;

        finishTime[i] = time + serviceTime;
        turnAroundTime[i] = finishTime[i] - arrivalTime;
        normTurn[i] = static_cast<double>(turnAroundTime[i]) / serviceTime;

        for (int j = time; j < finishTime[i]; j++)
            timeline[i][j] = '*';
        for (int j = arrivalTime; j < time; j++)
            timeline[i][j] = '.';
        
        time += serviceTime;

        cout << "Process " << sorted_processes[i].process_id << " started at time " << time - serviceTime
                  << " and finished at time " << finishTime[i] << "\n";
    }
    writeTimelineToFile(timeline,time, "timeline.txt");
    // Printing the timeline for debugging purposes
    cout << "Timeline:\n";
    for (int p = 0; p < process_count; p++) {
    for (int t = 0; t < time; t++) {
            cout << timeline[p][t];
        }
        cout << "\n";
    }
}
