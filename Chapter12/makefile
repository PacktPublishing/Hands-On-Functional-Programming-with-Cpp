all: computeSalaries strategy dependencyinjection autoincrement state maybe 

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

autoincrement: .outputFolder
	g++ -std=c++17 autoincrement.cpp -Wall -Wextra -Werror -o out/autoincrement
	./out/autoincrement

state: .outputFolder
	g++ -std=c++17 state.cpp -Wall -Wextra -Werror -o out/state
	./out/state

maybe: .outputFolder
	g++ -std=c++17 maybe.cpp -Wall -Wextra -Werror -o out/maybe
	./out/maybe

write: .outputFolder
	g++ -std=c++17 write.cpp -Wall -Wextra -Werror -o out/write
	./out/write
