all: ticTacToeResult ticTacToeResultWithClasses

.outputFolder:
	mkdir -p out
	
ticTacToeResult: .outputFolder
	g++ -std=c++17 ticTacToeResult.cpp -Wall -Wextra -Werror -o out/ticTacToeResult
	./out/ticTacToeResult

ticTacToeResultWithClasses: .outputFolder
	g++ -std=c++17 ticTacToeResultWithClasses.cpp -Wall -Wextra -Werror -o out/ticTacToeResultWithClasses
	./out/ticTacToeResultWithClasses
