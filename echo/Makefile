CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: echo_client

echo_client: echo_client.cpp
	$(CXX) $(CXXFLAGS) -o echo_client echo_client.cpp

clean:
	rm -f echo_client

.PHONY: all clean
