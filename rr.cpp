#include "scheduler.h"
#include <bits/stdc++.h>

using namespace std;

void rr(const vector<Process>& processes, int time_quantum) {
    cout << "Executing RR algorithm with time quantum " << time_quantum << "\n";

    int process_count = processes.size();
    vector<int> finishTime(process_count);
    vector<int> turnAroundTime(process_count);
    vector<double> normTurn(process_count);
    timeline.resize(process_count, vector<char>(100, '.')); // Assuming max timeline of 100 units

    vector<Process> proc_queue = processes;
    queue<int> ready_queue;

    int current_time = 0;
    int completed_processes = 0;


    for (int i = 0; i < process_count; ++i) {
            if (proc_queue[i].arrival_time == current_time) {
                ready_queue.push(i);
            }
        }

    while (completed_processes < process_count) {

        if (!ready_queue.empty()) {
            int process_index = ready_queue.front();
            ready_queue.pop();


            Process& p = proc_queue[process_index];
            int start_time = current_time;

            int execution_time = min(time_quantum, p.remaining_time);
            current_time += execution_time;
            p.remaining_time -= execution_time;

            for (int j = start_time; j < current_time; ++j) {
                timeline[process_index][j] = '*';
            }

            // Enqueue processes that have arrived during the execution
            for (int i = 0; i < process_count; ++i) {
                if (proc_queue[i].arrival_time > start_time && proc_queue[i].arrival_time <= current_time) {
                    ready_queue.push(i);

                }
            }

            if (p.remaining_time > 0) {
                ready_queue.push(process_index);

            } else {
                finishTime[process_index] = current_time;
                turnAroundTime[process_index] = finishTime[process_index] - p.arrival_time;
                normTurn[process_index] = static_cast<double>(turnAroundTime[process_index]) / p.burst_time;
                completed_processes++;
            }
        } else {
            current_time++;
            // Enqueue processes that have arrived
            for (int i = 0; i < process_count; ++i) {
                if (proc_queue[i].arrival_time == current_time) {
                    ready_queue.push(i);

                }
            }
        }
    }

    // Output results
    for (int i = 0; i < process_count; ++i) {
        cout << "Process " << proc_queue[i].process_id << " finished at time " << finishTime[i]
                  << " with turnaround time " << turnAroundTime[i] << " and normalized turnaround time " << normTurn[i] << "\n";
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
    vector<vector<int>> stats(process_count,vector<int>(5));
    for (int p=0;p<process_count;p++)
    {
        stats[p][0]=processes[p].arrival_time;
        stats[p][1]=processes[p].burst_time;
        stats[p][2]=finishTime[p];
        stats[p][3]=turnAroundTime[p];
        stats[p][4]=normTurn[p];
    }
    writeStatsToFile(stats, "stats.txt");
}
