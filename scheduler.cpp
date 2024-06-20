#include "scheduler.h"
#include <iostream>

using namespace std;

vector<std::vector<char>> timeline;

void clear_timeline() {
    timeline.clear();
}

void execute_algorithm(const string& algorithm_name, const vector<Process>& processes, Operation operation) {
    if (algorithm_name == "AGING") {
        ag(processes);
    } else if (algorithm_name == "FEEDBACK") {
        fbv(processes); 
    } else if (algorithm_name == "FCFS") {
        fcfs(processes);
    } else if (algorithm_name == "HRRN") {
        hrrn(processes);
    } else if (algorithm_name == "LJF"){
        ljf(processes);
    } else if (algorithm_name == "LRT"){
        lrt(processes);
    } else if (algorithm_name == "PRIORITY") {
        priority(processes);
    } else if (algorithm_name == "RR") {
        rr(processes, 2); // Example time quantum
    } else if (algorithm_name == "SJF") {
        sjf(processes);
    } else if (algorithm_name == "SRT") {
        srt(processes);
    }
}

void writeTimelineToFile(const vector<vector<char>>& timeline,int time, const string& filename) {
    ofstream outFile(filename);
    
    if (!outFile) {
        cerr << "Failed to open " << filename << endl;
        return;
    }
    
    for (const auto& process_timeline : timeline) {
        for (size_t i = 0; i < time; ++i) {
            outFile << process_timeline[i];
            if (i != time - 1) {
                outFile << " ";
            }
        }
        outFile << "\n";
    }
    
    outFile.close();
}

void writeStatsToFile(const vector<vector<int>>& stats, const string& filename) {
    ofstream outFile(filename);
    
    if (!outFile) {
        cerr << "Failed to open " << filename << endl;
        return;
    }
    
    for (const auto& entry : stats) {
        for (size_t i = 0; i < 5; ++i) {
            outFile << entry[i];
            if (i != 4) {
                outFile << " ";
            }
        }
        outFile << "\n";
    }
    
    outFile.close();
}
