all:
	@g++ src/*.cpp -std=c++11  -o bin/client
	@ls -l bin/client
