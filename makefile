all: run
farm: clear main.cpp
	g++ -std=c++11 -Wall -g main.cpp plant.cpp farmer.cpp visual.cpp weather.cpp animal.cpp -o farm -lncurses -pthread
clear:
	rm -rf farm
run: farm
	./farm