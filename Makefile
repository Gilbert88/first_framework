CXX = g++
CXXFLAGS = -g -O2 -pthread -std=c++0x
LDFLAGS += -lmesos -lpthread -lprotobuf
CXXCOMPILE = $(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@
CXXLINK = $(CXX) $(INCLUDES) $(CXXFLAGS) -o $@

default: all
all: first_framework

HEADERS = first_framework.hpp

%: %.cpp $(HEADERS)
	$(CXXLINK) $< $(LDFLAGS)

clean:
	(rm -f first_framework)
