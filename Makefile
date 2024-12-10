all: RiversAreTrees

RiversAreTrees: main.cpp implementation.cpp header.hpp
	g++ -g -Wall -std=c++11 main.cpp implementation.cpp -o outputExecutable
	./outputExecutable