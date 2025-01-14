GCC_FLAGS =  -std=c11  -Wall -Wextra -Werror
G++_FLAGS =  -std=c++17 #-Wall -Wextra -Werror
# Папки поиска
SRC_DIRS = .
OBJ_DIR = ./objs
TEST_DIR = ./tests
TEST_OBJ_DIR = ./tests/objs
BUILD_PATH = gcov_report/
REPORT_PATH = $(BUILD_PATH)report/
TEST_CPP_FILES := $(wildcard $(TEST_DIR)/*.cpp)
PROJECT_NAME=BrickGame_v2.0
BACKEND_TETRIS=brick_game/tetris
BACKEND_SNAKE=brick_game/snake
MODEL_SNAKE=$(BACKEND_SNAKE)/model
CONTROLLER_SNAKE=$(BACKEND_SNAKE)/controller
FRONTEND_CLI=gui/cli
BUILD_DIR_TEST = ./build_test
COVERAGE_FLAGS=-fprofile-arcs -ftest-coverage


ifeq ($(shell uname -s), Linux)
	TEST_FLAGS = -lcheck -lpthread -pthread -lm  -lrt -lsubunit
	OPEN = xdg-open
	LDFLAGS := -lncursesw
else
	TEST_FLAGS = -lcheck -lpthread -pthread -lm 
	LDFLAGS := -lncurses
	OPEN = open
endif


all: clean install

install: clean cli desktop

cli: libtetris.a libsnake.a
	mkdir build
	gcc  -g $(GCC_FLAGS) -c $(FRONTEND_CLI)/*.c -lncurses 
	g++  -g $(G++_FLAGS) -c $(FRONTEND_CLI)/*.cpp -lncurses 
	cd build && g++ -g $(G++_FLAGS) -o $(PROJECT_NAME)_cli ../*.o  -lncurses -L./..	-ltetris  -lsnake 
	rm -rf *.o *.a

libsnake.a:
	g++ $(G++_FLAGS) -c $(MODEL_SNAKE)/*.cpp $(CONTROLLER_SNAKE)/*.cpp 
	ar rc libsnake.a *.o
	rm -rf *.o

libtetris.a:
	gcc $(GCC_FLAGS) -c $(BACKEND_TETRIS)/*.c 
	ar rc libtetris.a *.o
	rm -rf *.o

desktop:
	rm -rf desk
	mkdir desk
	cd desk && qmake ../gui/desktop
	cd desk && make
	mv desk/desktop.app/Contents/MacOS/desktop build
	rm -rf desk

unistall:
	rm -rf build

dvi: clean
	open ./dvi/Documentation.html

dist: install
	tar -cvzf $(PROJECT_NAME).tgz build
	rm -rf build

startCli:
	cd build && ./$(PROJECT_NAME)_cli
startUi:
	cd build && ./desktop

test: clean test_snake test_tetris
	

test_tetris: 
	@mkdir -p $(BUILD_DIR_TEST)
	gcc -DTEST_MODE $(GCC_FLAGS) $(COVERAGE_FLAGS) $(TEST_DIR)/*.c $(BACKEND_TETRIS)/*.c  -o $(BUILD_DIR_TEST)/tetris -lncurses $(TEST_FLAGS)
	./$(BUILD_DIR_TEST)/tetris

test_snake: 
	@mkdir -p $(BUILD_DIR_TEST)
	g++ $(G++_FLAGS) $(COVERAGE_FLAGS)  $(TEST_DIR)/*.cpp $(BACKEND_SNAKE)/*/*.cpp -o $(BUILD_DIR_TEST)/snake -lgtest
	./$(BUILD_DIR_TEST)/snake


gcov_report: test
	lcov -t "test" -o $(BUILD_DIR_TEST)test.info -c -d . --no-external --ignore-errors mismatch,mismatch,inconsistent
	genhtml -o report $(BUILD_DIR_TEST)test.info
	open ./report/index.html


clean:
	rm -rf $(OBJ_DIR) $(TEST_OBJ_DIR) $(EXE) *.a *.out *.gc* *.info *.profraw *.o $(BUILD_PATH) 
	rm -rf $(REPORT_PATH)
	rm -rf *.o
	rm -rf build
	rm -rf $(BUILD_DIR_TEST)
	rm -rf report
	rm -rf *.txt
	rm -rf *.tgz

rebuild: clean cli

docker_build:
	cp ../materials/linters/.clang-format ./
	docker build -t vault:v1 .
	docker create -it --name decimal_vault vault:v1

docker_start:
	docker start -i decimal_vault

docker_delete:
	docker rm decimal_vault
	docker image rm vault:v1

valgrind: rebuild
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=leaks_log.txt ./build/$(PROJECT_NAME)_cli
	echo --- Valgrind summary --- && cat leaks_log.txt | grep 'total heap usage' && cat leaks_log.txt | grep 'ERROR SUMMARY'

style_test:
	cp ../materials/linters/.clang-format .
	clang-format -n ./*/*/*.c ./*/*/*.h ./*/*/*.cpp
	clang-format -n ./*/*/*/*.h ./*/*/*/*.cpp
	rm .clang-format

format_style:
	cp ../materials/linters/.clang-format .
	clang-format -i ./*/*/*.c ./*/*/*.h ./*/*/*.cpp
	clang-format -i ./*/*/*/*.h ./*/*/*/*.cpp
	rm .clang-format
