How To Use CPU Scheduling Program

Compile (in terminal):
make

Execute (in terminal):
./sim

Execute Using Flags:
./sim -d	(Detailed Information Mode)
./sim -v	(Verbose Mode)
./sim -x	(Enable 5s Overhead Switch)
./sim fcfs	(First Come First Serve)
./sim sjf	(Shortest Job First)
./sim srtn	(Shortest Remaining Time Next)
./sim rr10	(Round Robin W/ Quantum = 10)
./sim rr50	(Round Robin W/ Quantum = 50)
./sim rr100	(Round Robin W/ Quantum = 100)

-d, -v, and/or -x can be used in combination
algorithm keywords may be used in combination (multiple round robin quantums may not be used)