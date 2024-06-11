#include <bits/stdc++.h>
#include "scheduler.h"


using namespace std;

void parse(vector<pair<string, vector<Process> > >& algorithms) {
    // Function to parse input tasks and algorithm parameters
    // Implementation to be added
    vector<Process> processes;
    Process p(1, 2, 6,  3);
    processes.push_back(p);
    Process q(2, 5, 2, 1);
    processes.push_back(q);
    Process r(3, 1, 8, 4);
    processes.push_back(r);
    Process a(4, 0, 3, 4);
    processes.push_back(a);
    Process b(5, 4, 4, 4);
    processes.push_back(b);
    
    algorithms.push_back(make_pair("SRT", processes));
}

int main() {
    vector<pair<string, vector<Process> > > algorithms;
    Operation operation = TRACE; // or SHOW_STATISTICS

    parse(algorithms);

    for (int idx = 0; idx < (int)algorithms.size(); idx++) {
        clear_timeline();
        execute_algorithm(algorithms[idx].first, algorithms[idx].second, operation);
        // if (operation == TRACE)
        //     printTimeline(idx);
        // else if (operation == SHOW_STATISTICS)
        //     printStats(idx);
        cout << "\n";
    }

    return 0;
}