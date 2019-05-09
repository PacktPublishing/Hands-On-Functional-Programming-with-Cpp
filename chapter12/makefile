all: strategy dependencyinjection

.outputFolder:
	mkdir -p out

strategy : .outputFolder
	g++ -std=c++17 strategy.cpp -Wall -Wextra -Werror -o out/strategy
	./out/strategy

adapter: .outputFolder
	g++ -std=c++17 adapter.cpp -Wall -Wextra -Werror -o out/adapter
	./out/adapter

dependencyinjection : .outputFolder
	g++ -std=c++17 dependencyinjection.cpp -Wall -Wextra -Werror -o out/dependencyinjection
	./out/dependencyinjection
