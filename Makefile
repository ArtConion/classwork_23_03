CXXFLAGS = -Wall -Wextra -Weffc++ -std=c++14

vector-tests: main.o
	$(CXX) -o $@ $^
