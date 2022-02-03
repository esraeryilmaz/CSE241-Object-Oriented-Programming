hw : main.o GTUContainer.o GTUSet.o GTUVector.o GTUIterator.o GTUIteratorConst.o
	g++ -o hw GTUContainer.o GTUSet.o GTUVector.o GTUIterator.o GTUIteratorConst.o main.o

GTUContainer.o : GTUContainer.cpp
	g++ -c -std=c++11 GTUContainer.cpp

GTUSet.o : GTUSet.cpp
	g++ -c -std=c++11 GTUSet.cpp

GTUVector.o : GTUVector.cpp
	g++ -c -std=c++11 GTUVector.cpp

GTUIterator.o : GTUIterator.cpp
	g++ -c -std=c++11 GTUIterator.cpp

GTUIteratorConst.o : GTUIteratorConst.cpp
	g++ -c -std=c++11 GTUIteratorConst.cpp

main.o : main.cpp
	g++ -c -std=c++11 main.cpp

run :
	./hw

clean :
	rm *.o hw
