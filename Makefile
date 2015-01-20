taylor: main.o fn.o
	g++ $^ -o taylor

main.o: main.cpp
	g++ -c main.cpp

fn.o: fn.cpp
	g++ -c fn.cpp

clean:
	rm -f taylor
	rm -f *.o