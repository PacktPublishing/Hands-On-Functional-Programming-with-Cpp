all: ticTacToeResult monads

.outputFolder:
	mkdir -p out
	
ticTacToeResult: .outputFolder
	g++ -std=c++17 ticTacToeResult.cpp -Wall -Wextra -Werror -o out/ticTacToeResult
	./out/ticTacToeResult

monads: .outputFolder
	g++ -std=c++17 monads.cpp -Wall -Wextra -Werror -o out/monads
	./out/monads
