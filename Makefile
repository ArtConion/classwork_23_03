CXXFLAGS = -Wall -Wextra -Weffc++ -std=c++14 -MMD

vector-tests: main.o
	$(CXX) -o $@ $^

-include main.d
