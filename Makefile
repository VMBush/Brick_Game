UNAME_S := $(shell uname -s)

CC = g++
FLAGS = -Werror -Wextra -Wall
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
PROJECT_NAME_CLI = terminal
PROJECT_NAME_GUI = desktop.exe
RECORD_PATH_TETRIS = $(realpath ./brick_game/tetris/record.txt)
RECORD_PATH_SNAKE = $(realpath ./brick_game/snake/record.txt)

ifeq ($(UNAME_S),Darwin)
	TST_LIBS := -I/opt/homebrew/opt/check/include -L/opt/homebrew/opt/check/lib -lcheck 
	TST_FLAG := -I/opt/homebrew/opt/check/include 
	PROJECT_NAME_GUI = desktop
	FLAGS = -Werror -Wextra -Wall -I/usr/local/include/ncurses

else
	TST_LIBS = $(shell pkg-config --libs check) 
	TST_FLAG = 
	PROJECT_NAME_GUI = desktop.exe
endif

DIR_FUNC_C = $(wildcard ./gui/cli ./brick_game )
DIR_TEST_C = ./tests
FILES_C := $(wildcard $(shell find $(DIR_FUNC_C) -name '*.c'))
FILES_CPP := $(wildcard $(shell find $(DIR_FUNC_C) -name '*.cpp'))


FILES_FUNC_C := $(wildcard $(shell find $(DIR_FUNC_C) -name '*.c') $(shell find $(DIR_FUNC_C) -name '*.cpp'))

.PHONY: gui tests

all: install dist
	# g++ $(FLAGS) -g $(FILES_FUNC_C)  -lncursesw -o ./$(PROJECT_NAME)
	# ./$(PROJECT_NAME) #$(RECORD_PATH_TETRIS) $(RECORD_PATH_SNAKE)
	# @echo $(wildcard $(addsuffix /**/*.c, ./gui/cli))
	# @echo $(RECORD_PATH_TETRIS)
	# @echo $(FILES_FUNC_C)
	

install:
	make cli
	make gui

uninstall:
	make clean

dvi:
	-start Readme.md
	-open Readme.md
	-xdg-open Readme.md

dist:
	mv gui/desktop/release/desktop.exe $(PROJECT_NAME_GUI)

cli:
	@echo $(FILES_C)
	#gcc $(FLAGS) -g $(FILES_C) -lncurses -o ./$(PROJECT_NAME_CLI)
	g++ $(FLAGS) -g $(FILES_CPP) $(FILES_C) -lncursesw -o ./$(PROJECT_NAME_CLI)
	# g++ $(FLAGS) -g $(FILES_FUNC_C)  -lncursesw -o ./$(PROJECT_NAME_CLI)

gui:
	cd ./gui/desktop && qmake && make

tests: makedirs
	# make -f Makefile.Test_c
	make -f Makefile.Test_cpp

makedirs:
	mkdir -p obj_func_gcov obj_func obj_test report report_cpp bin

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
	-rm *.exe desktop
	-rm -r obj_func obj_func_gcov obj_test report report_cpp bin
	-rm test-* $(DIR_FUNC_GCOV_OBJ)/*.o
	-rm -r gui/desktop/debug gui/desktop/release gui/desktop/Makefile* gui/desktop/.qmake.*
	@echo $(FILES_FUNC_C)
