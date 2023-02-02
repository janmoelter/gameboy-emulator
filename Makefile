CXX=clang++
CXXFLAGS=-g -std=c++2a -O3
#LDFLAGS=-lm
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lm

RM=rm -rf
MKDIR=mkdir -p

SRCS=$(wildcard src/*.cpp)
OBJS=$(subst src/,obj/,$(subst .cpp,.o,$(SRCS)))

OUT=emulator

.PHONY : all
all : bin/$(OUT)

.PHONY: clean
clean:
	@$(RM) obj/

.PHONY: distclean
distclean:
	@$(RM) obj/ bin/


bin/$(OUT): $(OBJS)
	@$(MKDIR) bin/
	$(CXX) -o bin/$(OUT) $^ $(LDFLAGS)

obj/%.o: src/%.cpp obj/common.hpp.pch
	@$(MKDIR) obj/
	$(CXX) $(CXXFLAGS) -include-pch obj/common.hpp.pch -o $@ -c $<

obj/common.hpp.pch: src/common.hpp
	@$(MKDIR) obj/
	$(CXX) $(CXXFLAGS) -o $@ -c $<
