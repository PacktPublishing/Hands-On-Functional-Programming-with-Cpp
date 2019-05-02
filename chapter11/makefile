SHELL := /bin/bash

all: parallelExecution memoization tailRecursion optimizedTailRecursion fullyOptimizedTailRecursion compileMemoryOptimization 

.outputFolder:
	mkdir -p out

parallelExecution: .outputFolder
	g++ -std=c++17 parallelExecution.cpp -Wall -Wextra -Werror -o out/parallelExecution
	./out/parallelExecution

memoization: .outputFolder
	g++ -std=c++17 memoization.cpp -Wall -Wextra -Werror -o out/memoization
	./out/memoization

tailRecursion: .outputFolder
	g++ -std=c++17 tailRecursion.cpp -Wall -Wextra -Werror -o out/tailRecursion
	./out/tailRecursion

optimizedTailRecursion: .outputFolder
	g++ -std=c++17 -foptimize-sibling-calls tailRecursion.cpp -Wall -Wextra -Werror -o out/optimizedTailRecursion
	./out/optimizedTailRecursion

fullyOptimizedTailRecursion: .outputFolder
	g++ -std=c++17 -O3 tailRecursion.cpp -Wall -Wextra -Werror -o out/fullyOptimizedTailRecursion
	./out/fullyOptimizedTailRecursion

compileMemoryOptimization: .outputFolder
	g++ -DNO_MOVE_ITERATOR -DMOVE_ITERATOR -DIN_PLACE -std=c++17 memoryOptimization.cpp -Wall -Wextra -Werror -o out/memoryOptimization

memoryConsumptionNoMoveIterator: .outputFolder 
	g++ -O3 -DNO_MOVE_ITERATOR -std=c++17 memoryOptimization.cpp -Wall -Wextra -Werror -o out/memoryOptimization
	./runWithMemoryConsumptionMonitoring memoryNoMoveIterator.log

memoryConsumptionInPlace: .outputFolder 
	g++ -O3 -DIN_PLACE -std=c++17 memoryOptimization.cpp -Wall -Wextra -Werror -o out/memoryOptimization
	./runWithMemoryConsumptionMonitoring memoryInPlace.log

memoryConsumptionFor: .outputFolder 
	g++ -O3 -DFOR -std=c++17 memoryOptimization.cpp -Wall -Wextra -Werror -o out/memoryOptimization
	./runWithMemoryConsumptionMonitoring memoryFor.log

memoryConsumptionMoveIterator: .outputFolder
	g++ -DMOVE_ITERATOR -std=c++17 memoryOptimization.cpp -Wall -Wextra -Werror -o out/memoryOptimization
	./runWithMemoryConsumptionMonitoring memoryMoveIterator.log

allMemoryLogs: memoryConsumptionNoMoveIterator memoryConsumptionInPlace memoryConsumptionFor memoryConsumptionMoveIterator

immutableDataStructures: .outputFolder
	g++ -std=c++17 -I./immer-0.5.0 -O3 immutableDataStructures.cpp -o out/immutableDataStructures
	./out/immutableDataStructures

