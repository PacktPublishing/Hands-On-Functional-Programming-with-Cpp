all: computeSalaries 

.outputFolder:
	mkdir -p out

computeSalaries: .outputFolder
	g++ -std=c++17 computeSalaries.cpp -Wall -Wextra -Werror -o out/computeSalaries
	./out/computeSalaries
