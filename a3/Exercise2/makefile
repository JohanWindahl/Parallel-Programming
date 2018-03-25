# author: Daniel Ghandahari

CC=gcc
CFLAGS= -g -Wall -fopenmp -pthread

########## Linking ##########
main: $(_OBJ)
	@echo '########## Linking binary files ##########'
	@$(CC) Game_Of_Life.c -o gol $(CFLAGS)
	@echo '##########################################'
	@echo ''

########## Run ##########
run: main
	./$<
