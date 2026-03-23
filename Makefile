.PHONY: all test

CXXFLAGS = -Wall -Wextra -Weffc++ -std=c++14 -MMD

all: vector-tests

test: vector-tests
	@./$^

vector-tests: main.o
	$(CXX) -o $@ $^

-include main.d

clean:
	@$(RM) vector-tests
	@$(RM) main.d
	@$(RM) main.o
