#include "scheduler.h"
#include <bits/stdc++.h>

using namespace std;

void priority(const vector<Process>& processes) {
    cout << "Executing Priority Scheduling algorithm\n";

    int process_count = processes.size();
    vector<int> finishTime(process_count);
    vector<int> turnAroundTime(process_count);
    vector<double> normTurn(process_count);
    timeline.resize(process_count, vector<char>(100, '.')); // Assuming max timeline of 100 units

    // Copy the processes to a local vector to sort them
    vector<Process> proc_queue = processes;

    // Sort processes by priority (higher priority number means higher priority)
    sort(proc_queue.begin(), proc_queue.end(), [](const Process& a, const Process& b) {
        if (a.priority == b.priority) {
            return a.arrival_time < b.arrival_time;
        }
        return a.priority > b.priority;
    });

    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < process_count) {
        int highest_priority = -1;
        int process_index = -1;

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < process_count; ++i) {
            if (proc_queue[i].remaining_time > 0 && proc_queue[i].arrival_time <= current_time) {
                if (highest_priority == -1 || proc_queue[i].priority > highest_priority) {
                    highest_priority = proc_queue[i].priority;
                    process_index = i;
                }
            }
        }

        if (process_index != -1) {
            Process& p = proc_queue[process_index];
            int start_time = current_time;

            int execution_time = p.remaining_time;
            current_time += execution_time;
            p.remaining_time -= execution_time;

            for (int j = start_time; j < current_time; ++j) {
                timeline[p.process_id-1][j] = '*';
            }

            finishTime[process_index] = current_time;
            turnAroundTime[process_index] = finishTime[process_index] - p.arrival_time;
            normTurn[process_index] = static_cast<double>(turnAroundTime[process_index]) / p.burst_time;
            completed_processes++;

            cout << "Process " << p.process_id << " started at time " << start_time
                      << " and finished at time " << finishTime[process_index] << "\n";
        } else {
            current_time++;
        }
    }

    // Printing the timeline for debugging purposes
    cout << "Timeline:\n";
        for (int p = 0; p < process_count; p++) {
    for (int t = 0; t < current_time; t++) {
            cout << timeline[p][t];
        }
        cout << "\n";
    }
}
