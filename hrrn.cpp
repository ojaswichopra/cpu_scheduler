#include "scheduler.h"
#include <bits/stdc++.h>

using namespace std; 

void hrrn(const vector<Process>& processes) {
    cout << "Executing Highest Response Ratio Next algorithm\n";

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
        // Calculate response ratio for all processes that have arrived
        double highest_response_ratio = -1.0;
        int process_index = -1;
        for (int i = 0; i < process_count; ++i) {
            if (proc_queue[i].remaining_time > 0 && proc_queue[i].arrival_time <= current_time) {
                int waiting_time = current_time - proc_queue[i].arrival_time;
                double response_ratio = (waiting_time + proc_queue[i].burst_time) / proc_queue[i].burst_time;
                if (response_ratio > highest_response_ratio) {
                    highest_response_ratio = response_ratio;
                    process_index = i;
                }
            }
        }

        if (process_index != -1) {
            Process& p = proc_queue[process_index];
            int start_time = current_time;

            int execution_time = min(p.remaining_time, 1); // Execute for 1 unit
            current_time += execution_time;
            p.remaining_time -= execution_time;

            for (int j = start_time; j < current_time; ++j) {
                timeline[p.process_id - 1][j] = '*';
            }

            if (p.remaining_time == 0) {
                finishTime[p.process_id - 1] = current_time;
                turnAroundTime[p.process_id - 1] = finishTime[p.process_id - 1] - p.arrival_time;
                normTurn[p.process_id - 1] = static_cast<double>(turnAroundTime[p.process_id - 1]) / p.burst_time;
                completed_processes++;
            } 
        } else {
            current_time++;
        }
    }

    // Printing the timeline for debugging purposes
    cout << "Timeline:\n";
    for (int p = 0; p < process_count; p++) {
        for (int t = 0; t < finishTime[p]; t++) {
            cout << timeline[p][t];
        }
        cout << "\n";
    }
}

