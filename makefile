CXX = g++
CXXFLAGS = -Wall -Werror -D DEBUG
INCPATH = Dependencies/include
LIBPATH = Dependencies/lib
LIBS = -lopengl32 -lglfw3 -lglew32 -lgdi32
SRCPATH = src
BUILDPATH = build

# src/main.cpp - all the .cpp files
SRCS = $(wildcard $(SRCPATH)/*.cpp)
# build/main.o - all the .o files
OBJS = $(patsubst $(SRCPATH)/%.cpp,$(BUILDPATH)/%.o,$(SRCS))
# deps maybe not need
DEPS = $(patsubst %.cpp,%.d,$(SRCS))

target = main.exe

all: $(target)

$(target): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) -I$(INCPATH) -L$(LIBPATH) $(LIBS)

$(OBJS): $(BUILDPATH)/%.o : $(SRCPATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INCPATH) -L$(LIBPATH) $(LIBS)

%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MM -MF"$@" $(SRCS)

.PHONY: clean
clean:
	rm ./$(target).exe

-include: $(DEPS)