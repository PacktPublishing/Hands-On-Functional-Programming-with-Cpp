all: basicFunctionalComposition composeFunctions decomposeMultipleArguments

.outputFolder:
	mkdir -p out

basicFunctionalComposition: .outputFolder
	g++ -std=c++17 basicFunctionalComposition.cpp -o out/basicFunctionalComposition
	./out/basicFunctionalComposition

composeFunctions: .outputFolder
	g++ -std=c++17 composeFunctions.cpp -o out/composeFunctions
	./out/composeFunctions

decomposeMultipleArguments: .outputFolder
	g++ -std=c++17 decomposeMultipleArguments.cpp -o out/decomposeMultipleArguments
	./out/decomposeMultipleArguments
