#include "scheduler.h"
#include <bits/stdc++.h>

using namespace std;

void ag(const vector<Process>& processes) {

    int time_quantum=4;
    cout << "Executing Aging algorithm with Time Quantum\n";

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
    vector<int> waiting_time(process_count, 0);

    while (completed_processes < process_count) {
        // Increase waiting time for all processes
        for (int i = 0; i < process_count; ++i) {
            if (proc_queue[i].remaining_time > 0 && proc_queue[i].arrival_time <= current_time) {
                waiting_time[i]++;
            }
        }

        // Find the process with the highest priority (including aging)
        int highest_priority = -1;
        int process_index = -1;
        for (int i = 0; i < process_count; ++i) {
            if (proc_queue[i].remaining_time > 0 && proc_queue[i].arrival_time <= current_time) {
                int adjusted_priority = proc_queue[i].priority + waiting_time[i];
                if (highest_priority == -1 || adjusted_priority > highest_priority) {
                    highest_priority = adjusted_priority;
                    process_index = i;
                }
            }
        }

        if (process_index != -1) {
            Process& p = proc_queue[process_index];
            int start_time = current_time;

            // Execute the process for the duration of the time quantum or until completion
            int execution_time = min(time_quantum, p.remaining_time);
            current_time += execution_time;
            p.remaining_time -= execution_time;

            for (int j = start_time; j < current_time; ++j) {
                timeline[process_index][j] = '*';
            }

            if (p.remaining_time == 0) {
                finishTime[process_index] = current_time;
                turnAroundTime[process_index] = finishTime[process_index] - p.arrival_time;
                normTurn[process_index] = static_cast<double>(turnAroundTime[process_index]) / p.burst_time;
                completed_processes++;

                cout << "Process " << p.process_id << " started at time " << start_time
                     << " and finished at time " << finishTime[process_index] << "\n";
            } else {
                cout << "Process " << p.process_id << " started at time " << start_time
                     << " and paused at time " << current_time << " with " << p.remaining_time << " units remaining\n";
            }
        } else {
            current_time++;
        }
    }
    
    writeTimelineToFile(timeline,current_time, "timeline.txt");
    // Printing the timeline for debugging purposes
    cout << "Timeline:\n";
    for (int p = 0; p < process_count; p++) {
    for (int t = 0; t < current_time; t++) 
        {
            cout << timeline[p][t];
        }
        cout << "\n";
    }
}
