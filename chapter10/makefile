all: strategy adapter

.outputFolder:
	mkdir -p out

strategy : .outputFolder
	g++ -std=c++17 strategy.cpp -Wall -Wextra -Werror -o out/strategy
	./out/strategy

adapter: .outputFolder
	g++ -std=c++17 adapter.cpp -Wall -Wextra -Werror -o out/adapter
	./out/adapter
