#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <bits/stdc++.h>

using namespace std;

enum Operation { TRACE, SHOW_STATISTICS };

class Process{
    public:
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;

    Process(int pid, int at, int bt, int pr )
    : process_id(pid), arrival_time(at), burst_time(bt), priority(pr), 
        remaining_time(bt) {}
};

extern vector<vector<char> > timeline;

void clear_timeline();
void execute_algorithm(const string& algorithm_name, const vector<Process>& processes, Operation operation);
void writeTimelineToFile(const vector<vector<char>>& timeline, int time, const string& filename);

// Algorithm implementations
void ag(const vector<Process>& processes);
void fbv(const vector<Process>& processes);
void fcfs(const vector<Process>& processes);
void hrrn(const vector<Process>& processes);
void ljf(const vector<Process>& processes);
void lrt(const vector<Process>& processes);
void priority(const vector<Process>& processes);
void rr(const vector<Process>& processes, int time_quantum);
void sjf(const vector<Process>& processes);
void srt(const vector<Process>& processes);

#endif // SCHEDULER_H
