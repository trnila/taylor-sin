FLAGS=-lgmp

taylor: main.o fn.o
	g++ $(FLAGS) $^ -o taylor

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

fn.o: fn.cpp
	g++ $(FLAGS) -c fn.cpp

clean:
	rm -f taylor
	rm -f *.o