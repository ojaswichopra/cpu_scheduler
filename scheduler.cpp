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

void printTimeline(int idx) {
    // Function to print the timeline of processes
    // Implementation to be added
}

void printStats(int idx) {
    // Function to print the statistics of scheduling
    // Implementation to be added
}