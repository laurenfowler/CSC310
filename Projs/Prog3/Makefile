CC = c++
HEADERS = btree.h album.h
OBJS = btree.o album.o

run: createBT.o $(OBJS) $(HEADERS)
	$(CC) createBT.o $(OBJS)	

createBT.o: createBT.cpp $(HEADERS)
	$(CC) -c createBT.cpp

btree.o: btree.cpp $(HEADERS)
	$(CC) -c btree.cpp

album.o: album.cpp
	$(CC) -c album.cpp

clean:
	rm *.o
	rm a.out
