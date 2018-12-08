all: basicPartialApplication basicCurrying removeDuplication

.outputFolder:
	mkdir -p out

basicPartialApplication: .outputFolder
	g++ -std=c++17 basicPartialApplication.cpp -o out/basicPartialApplication
	./out/basicPartialApplication

basicCurrying: .outputFolder
	g++ -std=c++17 basicCurrying.cpp -o out/basicCurrying
	./out/basicCurrying

removeDuplication: .outputFolder
	g++ -std=c++17 removeDuplication.cpp -o out/removeDuplication
	./out/removeDuplication
