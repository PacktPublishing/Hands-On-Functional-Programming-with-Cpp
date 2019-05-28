all: functional algorithm

.outputFolder:
	mkdir -p out

functional: .outputFolder
	g++ -std=c++17 -Iinclude/ functional.cpp -Wall -Wextra -Werror -o out/functional
	./out/functional

algorithm: .outputFolder
	g++ -std=c++17 -Iinclude/ algorithm.cpp -Wall -Wextra -Werror -o out/algorithm
	./out/algorithm
