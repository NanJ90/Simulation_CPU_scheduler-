#pragma once
#include <list>

using namespace std;

struct process {
	int p_id;
	int numOfCPU;
	int arrivalT;
	int finishT;
	int serviceT;
	int tatT;
	int totalCPUBurst;
	int totalIOBurst;
	int cpu_burst; // used for sjf
	int io_burst;
	list<int> cpuList;
	list<int> ioList;
};

// utility_functions.cpp
bool operator<(process const & lhs, process const & rhs);
bool comp_by_io_remain(process const & lhs, process const & rhs);
bool comp_by_cpu_burst(process const & lhs, process const & rhs);
bool comp_by_cpu_remain(process const & lhs, process const & rhs);
bool comp_by_pid(process const & lhs, process const & rhs);

void check_arguments(bool& v, bool& d, int argc, char** argv,
   bool& FCFS, bool& SJF, bool& SRTN, bool& RR,int&tq, bool& sc_version);

void load_file(int& totalJobs,list<process>& processes, bool verbose);
void summary(int time,int idle);
void details(list<process> fin,int total);
// sjf.cpp
void sjf(list<process>& processes, int& totalJobs, bool verbose, bool sc_version,bool detail);
// rr.cpp
void srtn(list<process>& processes, int& totalJobs, bool verbose, bool sc_version,bool detail);
// rr.cpp
void rr(list<process>& processes, int& totalJobs, bool verbose, bool sc_version,bool detail,int tq);
// fcfs.cpp
void fcfs(list<process>& processes, int& totalJobs, bool verbose, bool sc_version,bool detail);

