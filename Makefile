

# TODO: This is useful
akinator: tree.o deff_dump.o diff.o recursive_down.o frontend.o
	clang++ tree.o deff_dump.o diff.o recursive_down.o frontend.o -o deff && ./deff
# TODO: make separate compile task

deff_dump.o: diff_project/deff_dump.cpp diff_project/deff_dump.h diff_project/tree.h
	clang++ -c diff_project/deff_dump.cpp

tree.o: diff_project/tree.cpp diff_project/tree.h
	clang++ -c diff_project/tree.cpp

diff.o: diff_project/diff.cpp diff_project/diff.h diff_project/tree.h
	clang++ -c diff_project/diff.cpp
recursive_down.o: recursive_down.cpp recursive_down.h
	clang++ -c recursive_down.cpp
frontend.o: frontend.cpp recursive_down.h diff_project/diff.cpp diff_project/diff.h diff_project/tree.h frontend.h
	clang++ -c frontend.cpp

# TODO: Put some effort in your makefile
