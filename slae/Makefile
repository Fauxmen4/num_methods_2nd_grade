CC=g++
SOURCES=src/main.cpp src/matrix_t.cpp src/methods.cpp
EIGEN_LIB=/usr/local/include/Eigen

run: build
	@./bin/main

build:
	@$(CC) $(SOURCES) -I $(EIGEN_LIB) -o bin/main 

clean:
	@rm -rf *.o 
