all:
	@g++ src/*.cpp -std=c++11 -lsqlite3 -o bin/client
	@ls -l bin/client
