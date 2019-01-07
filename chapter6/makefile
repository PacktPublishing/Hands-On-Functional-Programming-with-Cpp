all: ticTacToeResult 

.outputFolder:
	mkdir -p out
	
ticTacToeResult: .outputFolder
	g++ -std=c++17 ticTacToeResult.cpp -o out/ticTacToeResult
	./out/ticTacToeResult

bank: .outputFolder
	g++ -std=c++17 bank.cpp -o out/bank
	./out/bank
