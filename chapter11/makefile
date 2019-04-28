all: performance

.outputFolder:
	mkdir -p out

performance: .outputFolder
	g++ -std=c++17 parallelExecution.cpp -Wall -Wextra -Werror -o out/parallelExecution
	./out/parallelExecution
