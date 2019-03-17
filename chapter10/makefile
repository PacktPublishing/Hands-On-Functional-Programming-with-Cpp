all: pokerHands

.outputFolder:
	mkdir -p out

pokerHands: .outputFolder
	g++ -std=c++17 pokerHands.cpp -Wall -Wextra -Werror -o out/pokerHands
	./out/pokerHands
