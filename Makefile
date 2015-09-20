all:
	@g++ -Wall -g -std=c++11 src/*.cpp src/vendor/*/*.cpp -o bin/client
