diamond: diamond.o driver.o
	g++ -o diamond diamond.o driver.o

driver.o: driver.cpp
	g++ -c driver.cpp

diamond.o: diamond.cpp diamond.h
	g++ -c diamond.cpp
	
clean:
	rm -rf diamond driver.o diamond.o
