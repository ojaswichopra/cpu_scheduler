#include "scheduler.h"
#include <bits/stdc++.h>

using namespace std;

void srt(const vector<Process>& processes) {
    cout << "Executing Shortest Remaining Time (SRT) algorithm\n";

    int process_count = processes.size();
    vector<int> finishTime(process_count);
    vector<int> turnAroundTime(process_count);
    vector<double> normTurn(process_count);
    timeline.resize(process_count, vector<char>(100, '.')); // Assuming max timeline of 100 units

    int current_time = 0;
    int completed_processes = 0;
    vector<Process> proc_queue = processes;

    while (completed_processes < process_count) {
        int shortest_remaining_time = INT_MAX;
        int shortest_process_index = -1;

        // Find the process with the shortest remaining burst time
        for (int i = 0; i < process_count; ++i) {
            if (proc_queue[i].remaining_time > 0 && proc_queue[i].arrival_time <= current_time) {
                if (proc_queue[i].remaining_time < shortest_remaining_time) {
                    shortest_remaining_time = proc_queue[i].remaining_time;
                    shortest_process_index = i;
                }
            }
        }

        if (shortest_process_index != -1) {
            Process& p = proc_queue[shortest_process_index];
            int start_time = current_time;

            p.remaining_time--;
            current_time++;

            timeline[shortest_process_index][current_time - 1] = '*';

            if (p.remaining_time == 0) {
                finishTime[shortest_process_index] = current_time;
                turnAroundTime[shortest_process_index] = finishTime[shortest_process_index] - p.arrival_time;
                normTurn[shortest_process_index] = static_cast<double>(turnAroundTime[shortest_process_index]) / p.burst_time;
                completed_processes++;
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
