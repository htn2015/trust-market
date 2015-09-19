all:
	@g++ -Wall -g -std=c++11 src/*.cpp src/lib/*/*.cpp -o bin/client
