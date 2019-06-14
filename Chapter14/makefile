all: ranges

.outputFolder:
	mkdir -p out

ranges: .outputFolder
	g++ -std=c++17 -Iinclude/ ranges.cpp -Wall -Wextra -Werror -o out/ranges
	./out/ranges
