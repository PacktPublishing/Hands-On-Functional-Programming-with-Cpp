all: shoppingcart

.outputFolder:
	mkdir -p out

shoppingcarttests: .outputFolder
	g++ -std=c++17 shoppingcartTests.cpp -o out/shoppingcarttests

shoppingcart: .outputFolder
	g++ -std=c++17 shoppingcart.cpp -o out/shoppingcart
	./out/shoppingcart
