all : hw

hw : main.o
	g++ -o hw main.o

main.o : main.cpp
	g++ -c -std=c++11 main.cpp

clean :
	rm *.o hw