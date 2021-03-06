CXX = g++
CXXFLAGS = -g -O2 -pthread -std=c++0x
LDFLAGS += -lmesos -lpthread -lprotobuf
CXXCOMPILE = $(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@
CXXLINK = $(CXX) $(INCLUDES) $(CXXFLAGS) -o $@

default: all
all: first_framework ff_executor 

HEADERS = first_framework.hpp constant.hpp

%: %.cpp $(HEADERS)
	$(CXXLINK) idAstar.cpp mapstruct.cpp $< $(LDFLAGS)

clean:
	(rm -f first_framework ff_executor)
