all: ticTacToeResult typicalTransformations

.outputFolder:
	mkdir -p out
	
ticTacToeResult: .outputFolder
	g++ -std=c++17 ticTacToeResult.cpp -o out/ticTacToeResult
	./out/ticTacToeResult

typicalTransformations: .outputFolder
	g++ -std=c++17 typicalTransformations.cpp -o out/typicalTransformations
	./out/typicalTransformations

bank: .outputFolder
	g++ -std=c++17 bank.cpp -o out/bank
	./out/bank
