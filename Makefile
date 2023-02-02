# Usage:
# make			# compile all binary
# make run		# run executable
# make clean	# remove ALL binaries, objects, and executable

# c++ compiler
CXX := g++

# compiler flags
CXXFLAGS := -std=c++11 -Wall -g

# build target
TARGET := AMH-Sorting

$(TARGET): main.o
	@echo "Linking..."
	@$(CXX) $(CXXFLAGS) main.o -o $(TARGET)
	@echo "Created unix executable :" $(TARGET)

main.o: main.cpp
	@echo "Compiling source files..."
	@$(CXX) -c $(CXXFLAGS) main.cpp

run: $(TARGET)
	@./$(TARGET)
	
.PHONY:
clean:
	@echo "Cleaning..."
	@$(RM) *.o
	@$(RM) $(TARGET)
