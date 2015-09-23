all:
	@g++ src/*.cpp -O3 -std=c++14 -lsqlite3 -o bin/client
	@ls -l bin/client
