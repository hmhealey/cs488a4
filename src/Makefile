SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = $(SOURCES:.cpp=.d)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LDFLAGS = $(shell pkg-config --libs lua5.1) -llua5.1 -lpng
	CPPFLAGS = $(shell pkg-config --cflags lua5.1)
endif
ifeq ($(UNAME_S),Darwin)
	LDFLAGS = -llua5.1 -L/usr/local/lib -lpng
	CPPFLAGS = -I/usr/local/include/lua5.1 -I/usr/local/include
endif

CXXFLAGS = $(CPPFLAGS) -W -Wall -g -MMD -std=c++11
CXX = g++
MAIN = rt

all: $(MAIN)

depend: $(DEPENDS)

clean:
	rm -f *.o *.d $(MAIN)

$(MAIN): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $<

%.d: %.cpp
	@echo Building $@...
	@set -e; $(CC) -M $(CPPFLAGS) $< \
                  | sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
                [ -s $@ ] || rm -f $@

-include $(DEPENDS)
