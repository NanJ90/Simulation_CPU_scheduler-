#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <list>

using namespace std;

const string stauts[] = { "new", "read","wait","run","execute" }; // 0 1 2 3 4

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
    int io_burst
    int *cpuList;
    int *ioList;
};


void load_file() {
    int id, arrival, numbers=0;

    ifstream infile;
    infile.open("exampleinput.txt");

    infile >> totalJobs >> overheads;
    cout << "Number of processes and overheads " << totalJobs << " " << overheads << endl;

//    CPU newcpu; I_O newio;
//    newcpu.burstT = cpu;
//    newio.burstT = io;
//    cpuList.push_back(newcpu);
//    ioList.push_back(newio);
}
void display() {
    cout << "The is process has  " << p_id << " " << numOfCPU << " " << arrivalT << endl;
    cout << "process " << p_id << "has cpu and io " << endl;
    for (int i = 0; i < numOfCPU; i++) {
        cout << cpuList[i].burstT << " " << ioList[i].burstT << endl;
    }
}
~process() {};

struct compareArrival
{
    inline bool operator() (const process& p1, const process& p2)
    {
        return (p1.arrivalT < p2.arrivalT);
    }
};

bool compareJobsT(process a, process b) {
    if(a.arrivalT == b.arrivalT)
    { return a.cpuList[a.currentC].burstT < b.cpuList[b.currentC].burstT;}
    return a.arrivalT < b.arrivalT;
};
bool compareJobsTio(process a, process b) {
    if (a.status == 2 && b.status == 2){
        if(a.iotime == b.iotime)
        { return a.cpuList[a.currentC].burstT < b.cpuList[b.currentC].burstT;}
        else return a.iotime < b.iotime;
    }
    return 0;
};
void summary(string alg,int cur,int idle);
void fcfs(vector<process>, int);
void sjf(vector<process>, int);

int main(int argc, char** argv) {
    int totalJobs=0, overheads=0;
    int id, arrival, numbers=0;
    load_file();
//    ifstream infile;
//    infile.open("inData.txt");
//
//    infile >> totalJobs >> overheads;
//    cout << "Number of processes and overheads " << totalJobs << " " << overheads << endl;

//    int cnum, cpu, io, counter = 0;
//
//    string line;
//    vector<process> processes;
//
//    process p1;
//    while (getline(infile, line)) {
//        cpu = io = 0;
//        if (line.empty()) continue;
//        istringstream ss(line);
//        if(numbers == 0) { //first process input
//            process temp;
//            ss >> id >> arrival >> numbers;
//            temp.p_id=id;
//            temp.arrivalT = arrival;
//            temp.numOfCPU = numbers;
//            p1 = temp;
//            continue;
//        }
//        if (numbers == counter) {
//            processes.push_back(p1);
//            process temp;
//            ss >> id >> arrival >> numbers;
//            temp.p_id=id;
//            temp.arrivalT = arrival;
//            temp.numOfCPU = numbers;
//            p1 = temp;
//            counter=0;
//        }
//        else {
//            ss >> cnum >> cpu >> io;
//            p1.insertCPU_IO(cpu, io);
//            counter++;
//            //cout<< cnum<<" "<<cpu << " "<<io<<endl;
//        }
//    }
//    processes.push_back(p1);
//    for(int i = 0;i<totalJobs;i++){
//        for(int j = 0;j<processes[i].numOfCPU;j++){
//            processes[i].serviceT += processes[i].cpuList[j].burstT;
//            processes[i].iotimeB += processes[i].ioList[j].burstT;
//        }
//    }
//    fcfs(processes,totalJobs);
//    sjf(processes,totalJobs);
//    /*------SRTN------*/
//    vector<process> ready;
//    ready = processes;
//    int current=0, idleT=0, mins = INT_MAX, complete = 0, shortest = 0;
//    while(complete != totalJobs){
//        for(int i = 0;i< totalJobs;i++){
//            if(processes[i].arrivalT <= current){
//                //mins = processes[i].cpuList[processes[i].currentC].burstT;
//                shortest = i;
//                //ready.push_back(processes[i]);
//            }
//            ready[shortest].cputime = processes[i].cpuList[processes[i].currentC].burstT-current;
//            if(ready[shortest].cpuList[ready[shortest].currentC].finish == true && ready[shortest].ioList[ready[shortest].currentC].isio == true){
//                ready[shortest].iotime = ready[shortest].ioList[ready[shortest].currentC].burstT-current;
//
//            }
//            mins = ready[shortest].cpuList[ready[shortest].currentC].remainT;
//            if(mins == 0) mins = INT_MAX;
//            current++;
//
//        }
//
//    }
    infile.close();
    return 0;
}
void summary(string alg,int current, int idletime){
    double cpuUtilization=0.0;
    cpuUtilization =static_cast<double>(current-idletime)/static_cast<double>(current)*100.0;
    cout<<alg<<endl;
    cout<<"Total time required is " << current << " time units"<<endl;
    cout<< "the cpu utilization is "<< (int)cpuUtilization<<"%"<<endl<<endl;
}
/*------FCFS*--------*/
void fcfs(vector<process>processes, int totalJobs){ //nesting loops
    string algName = "First come first serve";
    //sorting process in processes by arrvial time in ready Q
    vector<process> readyQ, executeArr;
    readyQ = processes;
    sort(readyQ.begin(), readyQ.end(), compareArrival());

    for (int i = 0; i < totalJobs; i++) {
        readyQ[i].status = 1;
    }
    int cTime = readyQ[0].arrivalT;
    int iTime = readyQ[0].arrivalT;
    int current = 0;
    int idletime = 0;
    //int overheadsCount = 0;
    while (readyQ[0].status == 1 && !readyQ.empty()) {//io burst and empty conflicts
        //if(readyQ[0].currentC == readyQ[0].numOfCPU) continue;
        if(readyQ[0].arrivalT > current) {
            idletime += readyQ[0].arrivalT- cTime;
            cTime = readyQ[0].arrivalT;
        }
        
        int i = readyQ[0].currentC;
        readyQ[0].status = 3;
        cTime += readyQ[0].cpuList[i].burstT;
        current = cTime;
        iTime = current + readyQ[0].ioList[i].burstT;
        readyQ[0].cputime = cTime;
        readyQ[0].iotime = iTime;
        readyQ[0].status = 2;
        
        i++; //update cpu counter in a process
        readyQ[0].currentC = i;
        if (readyQ[0].currentC == readyQ[0].numOfCPU) {//process completed
            readyQ[0].status = 4; //prcess completed
            readyQ[0].finishT = current;
            readyQ[0].tatT = readyQ[0].finishT - readyQ[0].arrivalT;
            readyQ[0].wait = readyQ[0].tatT - readyQ[0].serviceT-readyQ[0].iotimeB;
            executeArr.push_back(readyQ[0]);
           
            readyQ.erase(readyQ.begin());
            sort(readyQ.begin(), readyQ.end(),compareJobsTio);
            readyQ[0].status = 1;
            if(cTime < readyQ[0].iotime) {
                cTime = readyQ[0].iotime;
                idletime+=readyQ[0].iotime - current;
            }
            continue;
        }
        if (cTime < readyQ[1].iotime) {
            sort(readyQ.begin(), readyQ.end(), compareJobsTio);
            //overheadsCount++;
            idletime += readyQ[0].iotime - current;
            cTime = readyQ[0].iotime;
            readyQ[0].status = 1;
            //readyQ[0].idle = true;
            
        }
        else {
            readyQ[1].status = 1;
            rotate(readyQ.begin(), readyQ.begin() + 1, readyQ.end());
            //overheadsCount++;
        }
    }
    summary(algName,current,idletime);
}
/*------SJF*--------*/
void sjf(vector<process>processes, int totalJobs){
    string algName = "Shortest Job First";
    vector<process> readyQ, executeArr;
    readyQ = processes;
    //sorting by cpu time if they arrive at the same time
    sort(readyQ.begin(), readyQ.end(), compareJobsT);
    for (int i = 0; i < totalJobs; i++) {
        readyQ[i].status = 1;
    }
    int cTime = readyQ[0].arrivalT;
    int iTime = readyQ[0].arrivalT;
    int current = 0;
    int idletime = 0;

    while (readyQ[0].status == 1 && !readyQ.empty()) {
        //checking unarrival process
        if(readyQ[0].arrivalT > current) {
            idletime += readyQ[0].arrivalT- cTime;
            cTime = readyQ[0].arrivalT;
            readyQ[0].status=1;
        }
        //sort(readyQ.begin(), readyQ.end(),compareJobsT);
        int i = readyQ[0].currentC;
        readyQ[0].status = 3; //running
        //update cpu time, io time and current time;
        cTime += readyQ[0].cpuList[i].burstT;
        current = cTime;
        iTime = current + readyQ[0].ioList[i].burstT;
        readyQ[0].cputime = cTime;
        readyQ[0].iotime = iTime;
        readyQ[0].status = 2;
        i++; //update cpu counter in a process
        readyQ[0].currentC = i;

        if (readyQ[0].currentC == readyQ[0].numOfCPU) {//process completed
            readyQ[0].status = 4; //prcess completed
            readyQ[0].finishT = current;
            readyQ[0].tatT = readyQ[0].finishT - readyQ[0].arrivalT;
            readyQ[0].wait = readyQ[0].tatT - readyQ[0].serviceT-readyQ[0].iotimeB;
            executeArr.push_back(readyQ[0]);

            readyQ.erase(readyQ.begin());
            sort(readyQ.begin(), readyQ.end(), compareJobsTio);
            readyQ[0].status = 1;
            if(cTime < readyQ[0].iotime) {
                cTime = readyQ[0].iotime;
                idletime+=readyQ[0].iotime - current;
            }
            continue;
        }
        if (cTime < readyQ[1].iotime) {
            sort(readyQ.begin(), readyQ.end(), compareJobsTio);//if io same shortest job first.
            //overheadsCount++;
            idletime += readyQ[0].iotime - current;
            cTime = readyQ[0].iotime;
            readyQ[0].status = 1;
            //readyQ[0].idle = true;

        }
        else {
            readyQ[1].status = 1;
            rotate(readyQ.begin(), readyQ.begin() + 1, readyQ.end());
            //overheadsCount++;
        }

    }
    summary(algName,current, idletime);
}
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
