all:
	g++ -o a.exe Pro.cpp main.cpp -std=c++98 -Wextra -Wall -Wpedantic
	clang++ -o b.exe Pro.cpp main.cpp -std=c++98 -Wextra -Wall -Wpedantic
