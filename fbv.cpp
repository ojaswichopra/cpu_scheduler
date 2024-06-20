#include "scheduler.h"
#include <bits/stdc++.h>

using namespace std;

void fbv(const vector<Process>& processes) {
    cout << "Executing Feedback algorithm\n";

    int process_count = processes.size();
    vector<int> finishTime(process_count);
    vector<int> turnAroundTime(process_count);
    vector<double> normTurn(process_count);
    timeline.resize(process_count, vector<char>(100, '.')); // Assuming max timeline of 100 units

    // Define the queues with different time quantums
    vector<queue<Process>> queues(3);
    vector<int> time_quantums = {4, 8, 12};

    // Sort processes by arrival time
    auto sorted_processes = processes;
    sort(sorted_processes.begin(), sorted_processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    // Enqueue the processes based on their arrival time
    int current_time = 0;
    size_t next_process_index = 0;
    int completed_processes = 0;

    while (completed_processes < process_count) {
        // Enqueue all processes that have arrived by current_time
        while (next_process_index < sorted_processes.size() && sorted_processes[next_process_index].arrival_time <= current_time) {
            queues[0].push(sorted_processes[next_process_index]);
            next_process_index++;
        }

        bool found_process = false;

        for (int q = 0; q < queues.size(); ++q) {
            if (!queues[q].empty()) {
                Process p = queues[q].front();
                queues[q].pop();

                found_process = true;

                int execution_time = min(time_quantums[q], p.remaining_time);
                int start_time = current_time;
                current_time += execution_time;
                p.remaining_time -= execution_time;

                for (int j = start_time; j < current_time; ++j) {
                    timeline[p.process_id - 1][j] = '*';
                }

                if (p.remaining_time > 0) {
                    if (q + 1 < queues.size()) {
                        queues[q + 1].push(p);
                    } else {
                        queues[q].push(p);
                    }
                } else {
                    finishTime[p.process_id - 1] = current_time;
                    turnAroundTime[p.process_id - 1] = finishTime[p.process_id - 1] - p.arrival_time;
                    normTurn[p.process_id - 1] = static_cast<double>(turnAroundTime[p.process_id - 1]) / p.burst_time;
                    completed_processes++;
                }

                if (p.remaining_time > 0) {
                    cout << "Process " << p.process_id << " started at time " << start_time
                          << " and paused at time " << current_time << "\n";
                } else {
                    cout << "Process " << p.process_id << " started at time " << start_time
                          << " and finished at time " << current_time << "\n";
                }
                break;
            }
        }

        if (!found_process) {
            current_time++;
        }
    }
    writeTimelineToFile(timeline,current_time, "timeline.txt");
    // Printing the timeline for debugging purposes
    cout << "Timeline:\n";
    for (int p = 0; p < process_count; p++) {
        for (int t = 0; t < current_time; t++) {
            cout << timeline[p][t];
        }
        cout << "\n";
    }

    // Printing statistics
    cout << "\nStatistics:\n";
    for (int i = 0; i < process_count; ++i) {
        cout << "Process " << i + 1 << ": Finish Time = " << finishTime[i] 
             << ", Turnaround Time = " << turnAroundTime[i] 
             << ", Normalized Turnaround Time = " << normTurn[i] << "\n";
    }
}