all: 
	mkdir -p out
	g++ -std=c++17 immutability.cpp -o out/immutability
	g++ -std=c++17 loop.cpp -o out/loop	
	g++ -std=c++17 join.cpp -o out/join
	g++ -std=c++17 compare.cpp -o out/compare
