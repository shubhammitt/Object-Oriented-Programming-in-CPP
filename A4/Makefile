target: book.o menu.o store.o
	g++ -o menu menu.o book.o store.o

store.o: store.cpp 
	g++ -c store.cpp

menu.o: menu.cpp
	g++ -c menu.cpp 

book.o: book.cpp
	g++ -c book.cpp

clean:
	rm -rf *.o menu