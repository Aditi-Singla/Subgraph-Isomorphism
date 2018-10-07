all: solve1 solve2

solve1: solveGraph.cpp
	g++ -o solve1 solveGraph.cpp

solve2: solveSatOutput.cpp
	g++ -o solve2 solveSatOutput.cpp
