all: ticTacToeResult typicalTransformations

.outputFolder:
	mkdir -p out
	
ticTacToeResult: .outputFolder
	g++ -std=c++17 ticTacToeResult.cpp -Wall -Wextra -Werror -o out/ticTacToeResult
	./out/ticTacToeResult
	
typicalTransformations: .outputFolder
	g++ -std=c++17 typicalTransformations.cpp -o out/typicalTransformations
	./out/typicalTransformations

