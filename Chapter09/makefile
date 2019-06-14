all: testPureFunctions pokerHands

.outputFolder:
	mkdir -p out

testPureFunctions: .outputFolder
	g++ -std=c++17 testPureFunctions.cpp -Wall -Wextra -Werror -o out/testPureFunctions
	./out/testPureFunctions

pokerHands: .outputFolder
	g++ -std=c++17 pokerHands.cpp -Wall -Wextra -Werror -o out/pokerHands
	./out/pokerHands
