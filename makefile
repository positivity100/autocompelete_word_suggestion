all: main.cpp Dictionary.cpp Dictionary.hpp
	g++ -std=c++11 -o aa.exe Dictionary.cpp main.cpp