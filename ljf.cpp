#include "scheduler.h"
#include <bits/stdc++.h>

using namespace std;

void ljf(const vector<Process>& processes) {
    cout << "Executing Longest Job First (LJF) algorithm\n";

    int process_count = processes.size();
    vector<int> finishTime(process_count);
    vector<int> turnAroundTime(process_count);
    vector<double> normTurn(process_count);
    timeline.resize(process_count, vector<char>(100, '.')); // Assuming max timeline of 100 units

    int current_time = 0;
    int completed_processes = 0;
    vector<Process> proc_queue = processes;

    while (completed_processes < process_count) {
        int longest_burst_time = -1;
        int longest_process_index = -1;

        // Find the process with the longest remaining burst time
        for (int i = 0; i < process_count; ++i) {
            if (proc_queue[i].remaining_time > 0 && proc_queue[i].arrival_time <= current_time) {
                if (proc_queue[i].burst_time > longest_burst_time) {
                    longest_burst_time = proc_queue[i].burst_time;
                    longest_process_index = i;
                }
            }
        }

        if (longest_process_index != -1) {
            Process& p = proc_queue[longest_process_index];
            int start_time = current_time;
            int execution_time = p.burst_time;
            p.remaining_time=0;
            current_time+=execution_time;

            for (int j=start_time;j<=current_time;j++){
            timeline[longest_process_index][j] = '*';
            }

            finishTime[longest_process_index] = current_time;
            turnAroundTime[longest_process_index] = finishTime[longest_process_index] - p.arrival_time;
            normTurn[longest_process_index] = static_cast<double>(turnAroundTime[longest_process_index]) / p.burst_time;
            completed_processes++;
            
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
