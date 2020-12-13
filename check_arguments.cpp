#include <string>
#include "functions.h"
using namespace std;

void check_arguments(bool& v, bool& d, int argc, char** argv,
   bool& FCFS, bool& SJF, bool& SRTN, bool& RR) {

   string argument;

   for (int i = 1; i < argc; ++i) {
       if (argv[i][0] == '-') {
           if (argv[i][1] == 'v') {
               v = true;
           }
       if (argv[i][1] == 'd') {
               d = true;
           }
       }
       argument = argv[i];
       if (argument == "FCFS" || argument == "fcfs") {FCFS = true;}
       if (argument == "SJF"  || argument == "sjf")  {SJF = true;}
       if (argument == "SRTN" || argument == "srtn") {SRTN = true;}
       if (argument == "RR"   || argument == "rr")   {RR = true;}
   }
   if (
       FCFS == false &&
       SJF == false &&
       SRTN == false &&
       RR == false
       ) {
       FCFS = false;
       SJF = false;
       SRTN = false;
       RR = true;
       // if all false, assume user is unfamiliar
       // and want to see all output
   }
}