all: lambdas

.outputFolder:
	mkdir -p out

lambdas: .outputFolder
	g++-8 -std=c++2a -Iinclude/ lambdas.cpp -Wall -Wextra -Werror -o out/lambdas
	./out/lambdas
