all: ticTacToeResult ticTacToeResultWithClasses fromClassToFunctions

.outputFolder:
	mkdir -p out
	
ticTacToeResult: .outputFolder
	g++ -std=c++17 ticTacToeResult.cpp -Wall -Wextra -Werror -o out/ticTacToeResult
	./out/ticTacToeResult

ticTacToeResultWithClasses: .outputFolder
	g++ -std=c++17 ticTacToeResultWithClasses.cpp -Wall -Wextra -Werror -o out/ticTacToeResultWithClasses
	./out/ticTacToeResultWithClasses

fromClassToFunctions: .outputFolder
	g++ -std=c++17 fromClassToFunctions.cpp -Wall -Wextra -Werror -o out/fromClassToFunctions
	./out/fromClassToFunctions
