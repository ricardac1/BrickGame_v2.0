GCC_FLAGS =  -std=c11
G++_FLAGS =  -std=c++17 #-Wall -Wextra -Werror
# Папки поиска
SRC_DIRS = .
OBJ_DIR = ./objs
TEST_DIR = ./tests
TEST_OBJ_DIR = ./tests/objs
BUILD_PATH = gcov_report/
REPORT_PATH = $(BUILD_PATH)report/
TEST_CPP_FILES := $(wildcard $(TEST_DIR)/*.cpp)
EXE = test.out
PROJECT_NAME=BrickGame_v2.0
BACKEND_TETRIS=brick_game/tetris
BACKEND_SNAKE=brick_game/snake
MODEL_SNAKE=$(BACKEND_SNAKE)/model
CONTROLLER_SNAKE=$(BACKEND_SNAKE)/controller
FRONTEND_CLI=gui/cli


OS := $(shell uname)

ifeq ($(OS),Linux)
	OPEN = xdg-open
	TEST_FLAGS = -lgtest -lgtest_main -lrt -lm -pthread
endif
ifeq ($(OS),Darwin)
	OPEN = open
	TEST_FLAGS = -L$(GTEST_PATH)/lib -lgtest -lgtest_main -lpthread
endif

all: clean install

install: clean cli desktop

cli: libtetris.a libsnake.a
	mkdir build
	gcc  $(GCC_FLAGS) -c $(FRONTEND_CLI)/*.c -lncurses 
	g++  $(G++_FLAGS) -c $(FRONTEND_CLI)/*.cpp -lncurses 
	cd build && g++ -g $(G++_FLAGS) -o $(PROJECT_NAME)_cli ../*.o  -lncurses -L./.. -ltetris  -lsnake 
	rm -rf *.o *.a

libsnake.a:
	g++  -g $(G++_FLAGS) -c $(MODEL_SNAKE)/*.cpp $(CONTROLLER_SNAKE)/*.cpp 
	ar rc libsnake.a *.o
	rm -rf *.o

libtetris.a:
	gcc -g $(GCC_FLAGS) -c $(BACKEND_TETRIS)/*.c 
	ar rc libtetris.a *.o
	rm -rf *.o

desktop:
	rm -rf desk
	mkdir desk
#	cd desk && qmake ../gui/desktop
#	cd desk && make
#	mv desk/desktop.app build
	rm -rf desk

start:
	cd build && ./$(PROJECT_NAME)_cli

	

# test: $(OBJS_TEST_FILES)
# 	g++ $(OBJS_TEST_FILES) $(TEST_FLAGS) -o $(EXE)
# 	./$(EXE)

# # Компиляция исходных файлов в объектные
# $(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
# 	mkdir -p $(dir $@)
# 	g++ $(GCC_FLAGS) -c $< -o $@

# # Компиляция тестовых файлов в объектные
# $(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(TEST_OBJ_DIR)
# 	mkdir -p $(dir $@)
# 	g++ $(GCC_FLAGS) -c $< -o $@

# # Создание директории для объектных файлов, если она не существует
# $(OBJ_DIR) $(TEST_OBJ_DIR):
# 	mkdir -p $@

gcov_report: build_dir
	mkdir -p $(REPORT_PATH)
	g++ $(GCC_FLAGS) --coverage $(SRC_CPP_FILES) $(TEST_CPP_FILES) -o $(BUILD_PATH)$(EXE) $(TEST_FLAGS) -fprofile-instr-generate -fcoverage-mapping
	chmod +x $(BUILD_PATH)$(EXE)
	$(BUILD_PATH)$(EXE)
	lcov -t "Report" --directory . --capture --output-file $(BUILD_PATH)coverage.info --ignore-errors empty,inconsistent --no-external
	genhtml --ignore-errors inconsistent --ignore-errors corrupt $(BUILD_PATH)coverage.info --output-directory $(REPORT_PATH)
	$(OPEN) $(REPORT_PATH)index.html

build_dir:
	mkdir -p $(BUILD_PATH)

clean:
	rm -rf $(OBJ_DIR) $(TEST_OBJ_DIR) $(EXE) *.a *.out *.gc* *.info *.profraw *.o $(BUILD_PATH) 
	rm -rf $(REPORT_PATH)
	rm -rf *.o
	rm -rf build

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
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=leaks_log.txt ./$(EXE)
	echo --- Valgrind summary --- && cat leaks_log.txt | grep 'total heap usage' && cat leaks_log.txt | grep 'ERROR SUMMARY'

style_test:
	cp ../materials/linters/.clang-format .
	clang-format -n *.cpp *.h */*.cpp
	rm .clang-format

format_style:
	cp ../materials/linters/.clang-format .
	clang-format -i */*.cpp
	rm .clang-format
