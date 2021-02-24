FLAGS += -Wall -Werror --std=c++17
USER_DIR_S = build
EXECUTABLE = bin/program

.PHONY: all clean

$(EXECUTABLE): $(USER_DIR_S)/main.o $(USER_DIR_S)/libmySimpleComputer.a $(USER_DIR_S)/libmyTerm.a $(USER_DIR_S)/libmyBigChars.a $(USER_DIR_S)/libprintConsole.a
	g++ $(FLAGS) -o $@ $^ -Lbuild -lmySimpleComputer -Lbuild -lmyTerm -Lbuild -lmyBigChars -Lbuild -lprintConsole

$(USER_DIR_S)/main.o: src/main.c
	g++ $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/mySimpleComputer.o: src/mySimpleComputer.c
	g++ $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/libmySimpleComputer.a: $(USER_DIR_S)/mySimpleComputer.o
	ar rc $(USER_DIR_S)/libmySimpleComputer.a $(USER_DIR_S)/mySimpleComputer.o

$(USER_DIR_S)/myTerm.o: src/myTerm.c
	g++ $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/myBigChars.o: src/myBigChars.c
	g++ $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/printConsole.o: src/printConsole.c
	g++ $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/libmyTerm.a: $(USER_DIR_S)/myTerm.o
	ar rc $(USER_DIR_S)/libmyTerm.a $(USER_DIR_S)/myTerm.o

$(USER_DIR_S)/libmyBigChars.a: $(USER_DIR_S)/myBigChars.o
	ar rc $(USER_DIR_S)/libmyBigChars.a $(USER_DIR_S)/myBigChars.o

$(USER_DIR_S)/libprintConsole.a: $(USER_DIR_S)/printConsole.o
	ar rc $(USER_DIR_S)/libprintConsole.a $(USER_DIR_S)/printConsole.o

start:
	./bin/program

clean:
	rm -rf $(USER_DIR_S)/*.o
	rm -rf $(USER_DIR_S)/*.a
	rm -rf bin/program

