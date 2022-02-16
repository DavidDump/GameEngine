# compiler options
CXX = g++
CXXFLAGS = -Wall -Werror -D DEBUG

# file includes and libraries
INCPATH = Dependencies/include
LIBPATH = Dependencies/lib
LIBS = -lopengl32 -lglfw3 -lglew32 -lgdi32

# directories where all the files are organized
SRCPATH = src
SUBDIRS = model
BUILDPATH = build

# src/main.cpp - all the .cpp files
SRCS = $(wildcard $(SRCPATH)/*.cpp)
# build/main.o - all the .o files
OBJS = $(patsubst $(SRCPATH)/%.cpp,$(BUILDPATH)/%.o,$(SRCS))
# build/main.d - all the .d file (maybe not need)
DEPS = $(patsubst $(SRCPATH)/%.cpp,$(BUILDPATH)/%.d,$(SRCS))

# Output file name
target = main.exe

all: $(target)

$(target): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) -I$(INCPATH) -L$(LIBPATH) $(LIBS)

$(OBJS): $(BUILDPATH)/%.o : $(SRCPATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INCPATH) -L$(LIBPATH) $(LIBS)

$(DEPS): $(BUILDPATH)/%.d : $(SRCPATH)/%.cpp
	$(CXX) $(CXXFLAGS) -MM -MF"$@" $<

.PHONY: clean
clean:
	rm ./$(target).exe

-include: $(DEPS)