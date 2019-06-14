all: computeSalaries computeSalariesTest 

.outputFolder:
	mkdir -p out

computeSalaries: .outputFolder
	g++ -std=c++17 computeSalaries.cpp computeSalaries.h -Wall -Wextra -Werror -o out/computeSalaries
	./out/computeSalaries

computeSalariesTest: .outputFolder
	g++ -std=c++17 computeSalariesTest.cpp computeSalaries.h -Wall -Wextra -Werror -o out/computeSalariesTest
	./out/computeSalariesTest
