PROG_NAME = prog
LIBRARY_FILES = -lglut -lGLU -lGL lib_soil/libSOIL.a
CPP_FILES = *.cpp animation/*.cpp camera/*.cpp robot/*.cpp light/*.cpp serialize/*.cpp vertex/*.cpp
all:
	@echo -n "Compiling files into" $(PROG_NAME) "..."
	@g++ -o $(PROG_NAME) $(CPP_FILES) $(LIBRARY_FILES)
	@echo "done"

clean:
	@echo "Cleaning files..."
	@rm -f *.o

