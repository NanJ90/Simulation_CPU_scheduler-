output: *.o
	g++ *.o -o sim
*.o: *.cpp process.h
	g++ -c *.cpp
clean:
	rm *.o sim
