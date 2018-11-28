all: basicFunctionalComposition composeFunctions

.outputFolder:
	mkdir -p out

basicFunctionalComposition: .outputFolder
	g++ -std=c++17 basicFunctionalComposition.cpp -o out/basicFunctionalComposition
	./out/basicFunctionalComposition

composeFunctions: .outputFolder
	g++ -std=c++17 composeFunctions.cpp -o out/composeFunctions
	./out/composeFunctions

shoppingcarttests: .outputFolder
	g++ -std=c++17 shoppingcartTests.cpp -o out/shoppingcarttests

shoppingcart: .outputFolder
	g++ -std=c++17 shoppingcart.cpp -o out/shoppingcart
	./out/shoppingcart
