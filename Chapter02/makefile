all: sort incrementAll staticAccess pureFunction number

.outputFolder:
	mkdir -p out

sort: .outputFolder
	g++ -std=c++17 sort.cpp -o out/sort
	./out/sort

incrementAll: .outputFolder
	g++ -std=c++17 incrementAll.cpp -o out/incrementAll
	./out/incrementAll

staticAccess: .outputFolder
	g++ -std=c++17 staticAccess.cpp -o out/staticAccess
	./out/staticAccess

pureFunction: .outputFolder
	g++ -std=c++17 pureFunction.cpp -o out/pureFunction
	./out/pureFunction

number: .outputFolder
	g++ -std=c++17 number.cpp -o out/number
	./out/number
