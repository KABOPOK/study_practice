CC=g++
CFLAGS=-c -pedantic-errors -g
LDFLAGS=
SOURCES=matrixlab.cpp algoritms.cpp fraction.cpp matrix.cpp to_256.cpp to_string.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=matrixlab

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
