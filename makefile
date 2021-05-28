main: StudentasFunkcijos.o
	g++ main.cpp StudentasFunkcijos.o -o main 
StudentasFunkcijos:
	g++ -c StudentasFunkcijos.cpp
clean:
	rm *.o main test *.txt
