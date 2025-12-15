CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: daytime_client

daytime_client: daytime_client.cpp
	$(CXX) $(CXXFLAGS) -o daytime_client daytime_client.cpp

clean:
	rm -f daytime_client

.PHONY: all clean
