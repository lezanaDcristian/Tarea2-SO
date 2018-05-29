# En linea de comandos escribir "make" creará ambos ejecutables
# "elo322_tarea2_pipes.out" y "elo322_tarea2_shm.out"
#
# Ademas puede limpiar los objetos y los ejecutables usando:
# "make clean"

SRC_DIR=./sources
HDR_DIR=./headers
OBJ_DIR=./objects

OPT_GCC=-std=c99 -Wall -Wextra
OPT=-D_XOPEN_SOURCE=700
LIB=-lrt

all: elo322_tarea2_pipes.out elo322_tarea2_shm.out

./elo322_tarea2_pipes.out: $(OBJ_DIR)/pipes.o $(OBJ_DIR)/functions.o
	gcc $(OPT_GCC) $(OPT) $(OBJ_DIR)/pipes.o $(OBJ_DIR)/functions.o -o ./elo322_tarea2_pipes.out $(LIB)
	
./elo322_tarea2_shm.out: $(OBJ_DIR)/shared_memory.o $(OBJ_DIR)/functions.o
	gcc $(OPT_GCC) $(OPT) $(OBJ_DIR)/shared_memory.o $(OBJ_DIR)/functions.o -o ./elo322_tarea2_shm.out $(LIB)
	
$(OBJ_DIR)/pipes.o: $(SRC_DIR)/pipes.c $(HDR_DIR)/functions.h
	gcc -c $(SRC_DIR)/pipes.c -o $(OBJ_DIR)/pipes.o
	
$(OBJ_DIR)/shared_memory.o: $(SRC_DIR)/pipes.c $(HDR_DIR)/functions.h
	gcc -c $(SRC_DIR)/shared_memory.c -o $(OBJ_DIR)/shared_memory.o
	
$(OBJ_DIR)/functions.o: $(SRC_DIR)/functions.c $(HDR_DIR)/functions.h
	gcc -c $(SRC_DIR)/functions.c -o $(OBJ_DIR)/functions.o

clean:
	rm ./elo322_tarea2_pipes.out ./elo322_tarea2_shm.out $(OBJ_DIR)/*.o
