#include "scheduler.h"
#include <bits/stdc++.h>

using namespace std;

void sjf(const vector<Process>& processes) {
    cout << "Executing Shortest Job First (SJF) algorithm\n";

    int process_count = processes.size();
    vector<int> finishTime(process_count);
    vector<int> turnAroundTime(process_count);
    vector<double> normTurn(process_count);
    timeline.resize(process_count, vector<char>(100, '.')); // Assuming max timeline of 100 units

    // Copy the processes to a local vector to sort them
    vector<Process> proc_queue = processes;

    // Sort processes by arrival time
    sort(proc_queue.begin(), proc_queue.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < process_count) {
        int shortest_job = -1;
        int shortest_burst_time = INT_MAX;

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < process_count; ++i) {
            if (proc_queue[i].remaining_time > 0 && proc_queue[i].arrival_time <= current_time) {
                if (proc_queue[i].burst_time < shortest_burst_time) {
                    shortest_burst_time = proc_queue[i].burst_time;
                    shortest_job = i;
                }
            }
        }

        if (shortest_job != -1) {
            Process& p = proc_queue[shortest_job];
            int start_time = current_time;

            int execution_time = p.remaining_time;
            current_time += execution_time;
            p.remaining_time -= execution_time;

            for (int j = start_time; j < current_time; ++j) {
                timeline[p.process_id-1][j] = '*';
            }

            finishTime[shortest_job] = current_time;
            turnAroundTime[shortest_job] = finishTime[shortest_job] - p.arrival_time;
            normTurn[shortest_job] = static_cast<double>(turnAroundTime[shortest_job]) / p.burst_time;
            completed_processes++;

            cout << "Process " << p.process_id << " started at time " << start_time
                      << " and finished at time " << finishTime[shortest_job] << "\n";
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
