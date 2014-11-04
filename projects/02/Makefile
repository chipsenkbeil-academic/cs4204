PROG_NAME = prog
LIBRARY_FILES = -lglut -lGLU -lGL lib_soil/libSOIL.a
CPP_FILES = *.cpp camera/*.cpp robot/*.cpp light/*.cpp
prog:
	@echo -n "Compiling files into" $(PROG_NAME) "..."
	@g++ -o $(PROG_NAME) $(CPP_FILES) $(LIBRARY_FILES)
	@echo "done"

clean:
	@echo "Cleaning files..."
	@rm -f *.o

