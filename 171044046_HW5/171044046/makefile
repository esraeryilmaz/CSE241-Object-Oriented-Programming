hw : main.o AbstractBoard.o BoardVector.o BoardArray1D.o BoardArray2D.o
	g++ -o hw AbstractBoard.o BoardVector.o BoardArray1D.o BoardArray2D.o main.o

AbstractBoard.o : AbstractBoard.cpp
	g++ -c -std=c++11 AbstractBoard.cpp

BoardVector.o : BoardVector.cpp
	g++ -c -std=c++11 BoardVector.cpp

BoardArray1D.o : BoardArray1D.cpp
	g++ -c -std=c++11 BoardArray1D.cpp

BoardArray2D.o : BoardArray2D.cpp
	g++ -c -std=c++11 BoardArray2D.cpp

main.o : main.cpp
	g++ -c -std=c++11 main.cpp

run :
	./hw

clean :
	rm *.o hw