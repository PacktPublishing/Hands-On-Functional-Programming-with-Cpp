all: performance

.outputFolder:
	mkdir -p out

performance: .outputFolder
	g++ -std=c++17 performance.cpp -Wall -Wextra -Werror -o out/performance
	./out/performance
