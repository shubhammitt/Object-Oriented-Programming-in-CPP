date: date.o driver.o
	g++ -o date date.o driver.o

driver.o: driver.cpp
	g++ -c driver.cpp

date.o: date.cpp date.h
	g++ -c date.cpp
	
clean:
	rm -rf date driver.o date.o
