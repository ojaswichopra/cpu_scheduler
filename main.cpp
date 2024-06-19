#include <bits/stdc++.h>
#include "scheduler.h"
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void parse(pair<string, vector<Process> > & algorithms) {
    ifstream inFile("processes.txt");
    if (!inFile) {
        cerr << "Failed to open processes.txt" << endl;
        return;
    }
    
    vector<Process> processes;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() == 4) {
            int process_id = stoi(tokens[0]);
            int arrival_time = stoi(tokens[1]);
            int burst_time = stoi(tokens[2]);
            int priority = stoi(tokens[3]);
            processes.emplace_back(process_id, arrival_time, burst_time, priority);
        } else {
            cerr << "Invalid line in processes.txt: " << line << endl;
        }
    }
    
    algorithms=(make_pair("SRT", processes));
}

int main() {
    pair<string, vector<Process> >  algorithms;
    Operation operation = TRACE; // or SHOW_STATISTICS

    parse(algorithms);
    clear_timeline();
    execute_algorithm(algorithms.first, algorithms.second, operation);
    return 0;
}