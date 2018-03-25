# Parallel-Programming #
#### Language: C++ & C ####

### **Assignment 1 - Basic concepts:** ###



dining.cpp - Dining Philosophers

---

### **Assignment 2 - Threads and Locks:** ###

	To compile: Navigate to wished Exercise and type ”make” to compile the program. 
	When the program is compiled, type ./main -h to get information about how to run 
	each program.

**2.1** - Numerical Integration

	definiteIntegrator.cpp

**2.2** - Sieve of Eratosthenes (find primes)

	sieveOfEratosthenes.cpp

**2.3** - Concurrent Data Structure

	benchmark_example_cgl1.cpp
	benchmark_example_cgl_tatas3.cpp

---

### **Assignment 3 - OpenMP:** ###

**3.1** - Sieve of Eratosthenes

	Go to folder: Exercise1, and execute "make"
	then use "./main" [Amount of threads] [Maximum value in range]
	./main 8 100000

**3.2** - Conway’s Game of Life
	Go to folder: Exercise2, and execute "make"
	then use "./gol" [Array dimension] [Time steps] [Amount of threads]\n"
	example: ./gol 100000 4 8

**3.3** - Merge Sort Using OpenMP Tasks

	1) for No pruning: then use 
	./Merge_sortNP [Array dimension] [Amount of threads]
	example: ./Merge_sortNP 100000000 8
	
	2) for Pruning: then use 
	./Merge_sortP  [Array dimension] [Amount of threads] [Threshold]
	example: ./Merge_sortP 100000000 8 2
	
	3) for One task spawn incl Pruning use:
	./Merge_sortS  [Array dimension] [Amount of threads] [Threshold]
	example: ./Merge_sortS 100000000 8 2
