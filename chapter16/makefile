all: lambdas partialApplication functionalComposition

.outputFolder:
	mkdir -p out

lambdas: .outputFolder
	g++-8 -std=c++2a -Iinclude/ lambdas.cpp -Wall -Wextra -Werror -o out/lambdas
	./out/lambdas

partialApplication: .outputFolder
	g++-8 -std=c++2a -Iinclude/ partialApplication.cpp -Wall -Wextra -Werror -o out/partialApplication
	./out/partialApplication

functionalComposition: .outputFolder
	g++-8 -std=c++2a -Iinclude/ functionalComposition.cpp -Wall -Wextra -Werror -o out/functionalComposition
	./out/functionalComposition
