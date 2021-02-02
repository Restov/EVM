binary: main.o libmySimpleComputer.a
	g++ -Wall -Werror -o binary main.o -L. -lmySimpleComputer
main.o: main.cpp
	g++ -Wall -Werror -c main.cpp -o main.o
mySimpleComputer.o: mySimpleComputer.cpp
	g++ -Wall -Werror -c mySimpleComputer.cpp -o mySimpleComputer.o
libmySimpleComputer.a: mySimpleComputer.o
	ar rc libmySimpleComputer.a mySimpleComputer.o
clean:
	rm -f *.o *.a binary

