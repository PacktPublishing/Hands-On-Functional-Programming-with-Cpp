all: ticTacToeResult hiddenLoop

.outputFolder:
	mkdir -p out
	
ticTacToeResult: .outputFolder
	g++ -std=c++17 ticTacToeResult.cpp -Wall -Wextra -Werror -o out/ticTacToeResult
	./out/ticTacToeResult

hiddenLoop: .outputFolder
	g++ -std=c++17 hiddenLoop.cpp -Wall -Wextra -Werror -o out/hiddenLoop
	./out/hiddenLoop
