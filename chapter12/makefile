all: computeSalaries strategy dependencyinjection

.outputFolder:
	mkdir -p out

computeSalaries: .outputFolder
	g++ -std=c++17 computeSalaries.cpp -Wall -Wextra -Werror -o out/computeSalaries
	./out/computeSalaries

strategy : .outputFolder
	g++ -std=c++17 strategy.cpp -Wall -Wextra -Werror -o out/strategy
	./out/strategy

dependencyinjection : .outputFolder
	g++ -std=c++17 dependencyinjection.cpp -Wall -Wextra -Werror -o out/dependencyinjection
	./out/dependencyinjection
