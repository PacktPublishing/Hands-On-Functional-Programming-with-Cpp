all: immutability loop join compare functionalSum

.outDir:
	mkdir -p out

immutability: .outDir
	g++ -std=c++17 immutability.cpp -o out/immutability
	./out/immutability

loop: .outDir
	g++ -std=c++17 loop.cpp -o out/loop	
	./out/loop

join: .outDir
	g++ -std=c++17 join.cpp -o out/join
	./out/join

compare: .outDir
	g++ -std=c++17 compare.cpp -o out/compare
	./out/compare

functionalSum: .outDir
	g++ -std=c++17 functionalSum.cpp -o out/functionalSum
	./out/functionalSum
