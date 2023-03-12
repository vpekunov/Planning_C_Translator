.SUFFIXES:

SRC_DIR := ./Examples
LDFLAGS := -lm -lpthread
CPPFLAGS := -fopenmp -fgnu-tm -fpermissive -O4 -std=c++11

SRCS=$(wildcard $(SRC_DIR)/*.cpp)

CCS=$(SRCS:.cpp=.cc)

EXES=$(SRCS:.cpp=)

all: $(EXES)

%: %.cc
	g++ $(CPPFLAGS) -o $@ -I../ $< $(LDFLAGS)

%.cc: %.cpp
	./Reenterable -strict-pre-checks -strict-plc-checks $< $@

clean:
	rm -rf $(CCS)
	rm -rf $(EXES)
