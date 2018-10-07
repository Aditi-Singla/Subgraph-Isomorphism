all: solve1 solve2

solve1: src/solveGraph.cpp
	g++ -O3 -std=c++11 -o solve1 src/solveGraph.cpp

solve2: src/solveSatOutput.cpp
	g++ -O3 -std=c++11 -o solve2 src/solveSatOutput.cpp

clean:
	rm -f solve1 solve2 data/temp data/*.satinput data/*.satoutput data/*mapping