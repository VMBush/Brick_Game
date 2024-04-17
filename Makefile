UNAME_S := $(shell uname -s)

CC = g++
FLAGS = -Werror -Wextra -Wall
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
PROJECT_NAME = game
RECORD_PATH_TETRIS = $(realpath ./brick_game/tetris/record.txt)
RECORD_PATH_SNAKE = $(realpath ./brick_game/snake/record.txt)

ifeq ($(UNAME_S),Darwin)
	TST_LIBS := -I/opt/homebrew/opt/check/include -L/opt/homebrew/opt/check/lib -lcheck 
	TST_FLAG := -I/opt/homebrew/opt/check/include 
else
	TST_LIBS = $(shell pkg-config --libs check) 
	TST_FLAG = 
endif

DIR_FUNC_C = $(wildcard ./gui/cli ./brick_game )
DIR_TEST_C = ./tests

FILES_FUNC_C := $(wildcard $(shell find $(DIR_FUNC_C) -name '*.c') $(shell find $(DIR_FUNC_C) -name '*.cpp'))


all: #makedirs $(PROJECT_NAME) #gcov_report
	g++ $(FLAGS) -g $(FILES_FUNC_C)  -lncursesw -o ./$(PROJECT_NAME)
	./$(PROJECT_NAME) #$(RECORD_PATH_TETRIS) $(RECORD_PATH_SNAKE)
	@echo $(wildcard $(addsuffix /**/*.c, ./gui/cli))
	@echo $(RECORD_PATH_TETRIS)

cli:
	g++ $(FLAGS) -g $(FILES_FUNC_C)  -lncursesw -o ./$(PROJECT_NAME)
	./$(PROJECT_NAME)

makedirs:
	mkdir -p obj_func_gcov obj_func obj_test report bin

clang:
	clang-format -n *.h $(FILES_FUNC_C) $(FILES_FUNC_H) $(FILES_TEST_C) $(FILES_TEST_H)

clangi:
	clang-format -i *.h $(FILES_FUNC_C) $(FILES_FUNC_H) $(FILES_TEST_C) $(FILES_TEST_H)

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem ../src

clean_gcov:
	-rm -r obj_func_gcov/*

clean:
	-rm test s21_gcov_test *.a
	-rm *.exe
	-rm -r obj_func obj_func_gcov obj_test report bin
	-rm test-* $(DIR_FUNC_GCOV_OBJ)/*.o
	# echo $(FILES_FUNC_OBJ)