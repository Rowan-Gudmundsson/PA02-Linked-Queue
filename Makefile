all: test sim

test: test7 QueueLinked
	g++ -o test7 test7.o QueueLinked.o

sim: storesim QueueLinked
	g++ -o storesim storesim.o QueueLinked.o

test7: test7.cpp
	g++ -c test7.cpp

QueueLinked: QueueLinked.cpp QueueLinked.h Queue.h
	g++ -c QueueLinked.cpp

storesim: storesim.cpp
	g++ -c storesim.cpp
