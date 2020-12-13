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
	int cpu_position;
	int io_position;
	int cpu_burst;
	int io_burst;
	bool running = false;
	list<int> cpuList;
	list<int> ioList;
};

// utility_functions.cpp
bool operator<(process const & lhs, process const & rhs);
bool comp_by_io_remain(process const & lhs, process const & rhs);
bool comp_by_cpu_burst(process const & lhs, process const & rhs);

void check_arguments(bool&, bool&, int, char**, bool&, bool&, bool&, bool&);
void load_file(int& totalJobs,list<process>& processes, bool verbose);

// fcfs.cpp
void fcfs(list<process>& processes, int& totalJobs, bool verbose);
// sjf.cpp
void sjf(list<process>& processes, int& totalJobs, bool verbose);
// rr.cpp
void rr(list<process>& processes, int& totalJobs, bool verbose);

