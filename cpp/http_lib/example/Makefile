CXXFLAGS = -O2 -std=c++17 -I.. -Wall -Wextra -pthread

all: test

test : test.cc ../include/request.hpp
	$(CXX) -o test $(CXXFLAGS) test.cc

clean:
	rm test