time: time.o driver.o
	g++ -o time time.o driver.o

driver.o: driver.cpp
	g++ -c driver.cpp

time.o: time.cpp time.h
	g++ -c time.cpp
	
clean:
	rm -rf time *.o
