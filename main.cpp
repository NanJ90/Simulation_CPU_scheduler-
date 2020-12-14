#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iterator>
//#include <bits/stdc++.h>
#include "process.h"

using namespace std;


int main(int argc, char** argv) {

    bool verbose = false;
    bool detail_output = false;

    bool FCFS = false;
    bool SJF = false;
    bool SRTN = false;
    bool RR = false;

    bool sc_version = false;

    int tq;
    int totalJobs = 0;

    check_arguments(verbose, detail_output, argc, argv, FCFS, SJF, SRTN, RR, tq, sc_version);

    list<process> processes;

	if (FCFS) {
        cout<<"First come first serve"<<endl;
		load_file(totalJobs,processes,verbose);
		fcfs(processes, totalJobs, verbose, sc_version,detail_output);
	}

	if (SJF) {
        cout<<"Shortest job first"<<endl;
		load_file(totalJobs,processes,verbose);
		sjf(processes, totalJobs, verbose, sc_version,detail_output);
	}

	if (SRTN) {
        cout<<"Shortest remaining time next"<<endl;
		load_file(totalJobs,processes,verbose);
		srtn(processes, totalJobs, verbose,sc_version, detail_output);
	}

	if (RR) {
        cout<<"Round Robin with time quantum "<< tq<<endl;
		load_file(totalJobs,processes,verbose);
		rr(processes, totalJobs, verbose,sc_version, detail_output,tq);
	}
    return 0;
} // end of int main()
