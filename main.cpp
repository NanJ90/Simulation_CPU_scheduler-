#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
// #include <list> // moved to process.h
#include <iterator>
//#include <bits/stdc++.h>
#include "process.h"

using namespace std;

const string stauts[] = { "new", "read","wait","run","execute" }; // 0 1 2 3 4



//void display() {
//    cout << "The is process has  " << p_id << " " << numOfCPU << " " << arrivalT << endl;
//    cout << "process " << p_id << "has cpu and io " << endl;
//    for (int i = 0; i < numOfCPU; i++) {
//        cout << cpuList[i].burstT << " " << ioList[i].burstT << endl;
//    }
//}

//struct compareArrival
//{
//    inline bool operator() (const process& p1, const process& p2)
//    {
//        return (p1.arrivalT < p2.arrivalT);
//    }
//};
//
//bool compareJobsT(process a, process b) {
//    if(a.arrivalT == b.arrivalT)
//    { return a.cpuList[a.currentC].burstT < b.cpuList[b.currentC].burstT;}
//    return a.arrivalT < b.arrivalT;
//};
//bool compareJobsTio(process a, process b) {
//    if (a.status == 2 && b.status == 2){
//        if(a.iotime == b.iotime)
//        { return a.cpuList[a.currentC].burstT < b.cpuList[b.currentC].burstT;}
//        else return a.iotime < b.iotime;
//    }
//    return 0;
//};
//void summary(string alg,int cur,int idle);
//void fcfs(vector<process>, int);
//void sjf(vector<process>, int);

int main(int argc, char** argv) {

    bool verbose = false;
    bool detail_output = false;

    bool FCFS = false;
    bool SJF = false;
    bool SRTN = false;
    bool RR = false;
    int totalJobs = 0;

    check_arguments(verbose, detail_output, argc, argv, FCFS, SJF, SRTN, RR);

    list<process> processes;

	if (FCFS) {
		load_file(totalJobs,processes,verbose);
		fcfs(processes, totalJobs, verbose);
		// if (detail_output) details(processes, totalJobs, "FCFS");
		// 	else summary(processes, totalJobs, "FCFS"); 
	}

	if (SJF) {
		load_file(totalJobs,processes,verbose);
		sjf(processes, totalJobs, verbose);
		// if (detail_output) details(processes, totalJobs, "SJF");
		// 	else summary(processes, totalJobs, "SJF");
	}

	if (SRTN) {
		load_file(totalJobs,processes,verbose);
		// srtn(processes, totalJobs, verbose);
		// if (detail_output) details(processes, totalJobs, "SRTN");
		// 	else summary(processes, totalJobs, "SRTN");
	}

	if (RR) {
		load_file(totalJobs,processes,verbose);
		rr(processes, totalJobs, verbose);
		// if (detail_output) details(processes, totalJobs, "RR");
		// 	else summary(processes, totalJobs, "RR");
	}
    return 0;
} // end of int main()

//void summary(string alg,int current, int idletime){
//    double cpuUtilization=0.0;
//    cpuUtilization =static_cast<double>(current-idletime)/static_cast<double>(current)*100.0;
//    cout<<alg<<endl;
//    cout<<"Total time required is " << current << " time units"<<endl;
//    cout<< "the cpu utilization is "<< (int)cpuUtilization<<"%"<<endl<<endl;
//}

///*------SJF*--------*/
//void sjf(vector<process>processes, int totalJobs){
//    string algName = "Shortest Job First";
//    vector<process> readyQ, executeArr;
//    readyQ = processes;
//    //sorting by cpu time if they arrive at the same time
//    sort(readyQ.begin(), readyQ.end(), compareJobsT);
//    for (int i = 0; i < totalJobs; i++) {
//        readyQ[i].status = 1;
//    }
//    int cTime = readyQ[0].arrivalT;
//    int iTime = readyQ[0].arrivalT;
//    int current = 0;
//    int idletime = 0;
//
//    while (readyQ[0].status == 1 && !readyQ.empty()) {
//        //checking unarrival process
//        if(readyQ[0].arrivalT > current) {
//            idletime += readyQ[0].arrivalT- cTime;
//            cTime = readyQ[0].arrivalT;
//            readyQ[0].status=1;
//        }
//        //sort(readyQ.begin(), readyQ.end(),compareJobsT);
//        int i = readyQ[0].currentC;
//        readyQ[0].status = 3; //running
//        //update cpu time, io time and current time;
//        cTime += readyQ[0].cpuList[i].burstT;
//        current = cTime;
//        iTime = current + readyQ[0].ioList[i].burstT;
//        readyQ[0].cputime = cTime;
//        readyQ[0].iotime = iTime;
//        readyQ[0].status = 2;
//        i++; //update cpu counter in a process
//        readyQ[0].currentC = i;
//
//        if (readyQ[0].currentC == readyQ[0].numOfCPU) {//process completed
//            readyQ[0].status = 4; //prcess completed
//            readyQ[0].finishT = current;
//            readyQ[0].tatT = readyQ[0].finishT - readyQ[0].arrivalT;
//            readyQ[0].wait = readyQ[0].tatT - readyQ[0].serviceT-readyQ[0].iotimeB;
//            executeArr.push_back(readyQ[0]);
//
//            readyQ.erase(readyQ.begin());
//            sort(readyQ.begin(), readyQ.end(), compareJobsTio);
//            readyQ[0].status = 1;
//            if(cTime < readyQ[0].iotime) {
//                cTime = readyQ[0].iotime;
//                idletime+=readyQ[0].iotime - current;
//            }
//            continue;
//        }
//        if (cTime < readyQ[1].iotime) {
//            sort(readyQ.begin(), readyQ.end(), compareJobsTio);//if io same shortest job first.
//            //overheadsCount++;
//            idletime += readyQ[0].iotime - current;
//            cTime = readyQ[0].iotime;
//            readyQ[0].status = 1;
//            //readyQ[0].idle = true;
//
//        }
//        else {
//            readyQ[1].status = 1;
//            rotate(readyQ.begin(), readyQ.begin() + 1, readyQ.end());
//            //overheadsCount++;
//        }
//
//    }
//    summary(algName,current, idletime);
//}


//void detail(){
//    //calculate TAT and cpu utilization and idle time
//    int totalTat = 0, totalWait=0;
//
////    for(int i = 0;i<totalJobs;i++){
////        totalTat += executeArr[i].tatT;
////        totalWait += executeArr[i].wait;
////    }
////
////    cout << "the average tat is " <<totalTat/totalJobs<<endl;
////    cout << "the average wait is " <<totalWait/totalJobs<<endl;
//
//}
