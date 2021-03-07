CXXFLAGS=-std=c++11 -Wall
CC=c++
OBJS=main.o Solver.o Tube.o


watersort: $(OBJS)
	$(CC) $(CXXFLAGS) $^ -o $@

clean:
	rm watersort *.o
