# author: Daniel Ghandahari

INC = include
SRC = src
OBJ = obj

CC=g++
CFLAGS= -g -Wall -std=c++11 -pthread -I $(INC) 



_OBJ = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(wildcard $(SRC)/*.cpp))

########## Compilation ##########
$(OBJ)/%.o: $(SRC)/%.cpp 
	@echo '########## Compiling source files ##########'
	@$(CC) -c -o $@ $< $(CFLAGS)
	@echo '############################################'
	@echo ''	
	
########## Linking ##########
main: $(_OBJ)
	@echo '########## Linking binary files ##########'
	@$(CC) -o $@ $^ $(CFLAGS)
	@echo '##########################################'
	@echo ''
	
########## Run ##########
run: main
	./$<	
