all: add immutabilityPassByValue immutabilityPassByReference immutabilityPointers lambdaIO immutableCapture lambdasAndClasses

.outputFolder:
	mkdir -p out

add: .outputFolder
	g++ -std=c++17 add.cpp -o out/add
	./out/add

immutabilityPassByValue: .outputFolder
	g++ -std=c++17 immutabilityPassByValue.cpp -o out/immutabilityPassByValue
	./out/immutabilityPassByValue

immutabilityPassByReference: .outputFolder
	g++ -std=c++17 immutabilityPassByReference.cpp -o out/immutabilityPassByReference
	./out/immutabilityPassByReference

immutabilityPointers: .outputFolder
	g++ -std=c++17 immutabilityPointers.cpp -o out/immutabilityPointers
	./out/immutabilityPointers

lambdaIO: .outputFolder
	g++ -std=c++17 lambdaIO.cpp -o out/lambdaIO
	./out/lambdaIO

immutableCapture: .outputFolder
	g++ -std=c++17 immutableCapture.cpp -o out/immutableCapture
	./out/immutableCapture

lambdasAndClasses: .outputFolder
	g++ -std=c++17 lambdasAndClasses.cpp -o out/lambdasAndClasses
	./out/lambdasAndClasses
