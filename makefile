FLAGS += -Wall -Werror --std=c++17
USER_DIR_S = build
EXECUTABLE = bin/program

.PHONY: all clean

$(EXECUTABLE): $(USER_DIR_S)/main.o $(USER_DIR_S)/libmySimpleComputer.a $(USER_DIR_S)/libmyTerm.a
	g++ $(FLAGS) -o $@ $^ -Lbuild -lmySimpleComputer -Lbuild -lmyTerm

$(USER_DIR_S)/main.o: src/main.cpp
	g++ $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/mySimpleComputer.o: src/mySimpleComputer.cpp
	g++ $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/libmySimpleComputer.a: $(USER_DIR_S)/mySimpleComputer.o
	ar rc $(USER_DIR_S)/libmySimpleComputer.a $(USER_DIR_S)/mySimpleComputer.o

$(USER_DIR_S)/myTerm.o: src/myTerm.cpp
	g++ $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/libmyTerm.a: $(USER_DIR_S)/myTerm.o
	ar rc $(USER_DIR_S)/libmyTerm.a $(USER_DIR_S)/myTerm.o

start:
	./bin/program

clean:
	rm -rf $(USER_DIR_S)/*.o
	rm -rf bin/program

