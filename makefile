# En linea de comandos: "make main=pipes.c" o 
# "make main=shared_memory.c"
#
# Ademas puede limpiar los objetos y el
# ejecutable usando: "make clean"

SRC_DIR=./sources
HDR_DIR=./headers
OBJ_DIR=./objects

./elo321_tarea2.out: $(OBJ_DIR)/main.o $(OBJ_DIR)/functions.o
	gcc $(OBJ_DIR)/main.o $(OBJ_DIR)/functions.o -o ./elo321_tarea2.out
	
$(OBJ_DIR)/main.o: $(SRC_DIR)/$(main) $(HDR_DIR)/functions.h
	gcc -c $(SRC_DIR)/$(main) -o $(OBJ_DIR)/main.o
	
$(OBJ_DIR)/functions.o: $(SRC_DIR)/functions.c $(HDR_DIR)/functions.h
	gcc -c $(SRC_DIR)/functions.c -o $(OBJ_DIR)/functions.o 
	
clean:
	rm ./elo321_tarea2.out $(OBJ_DIR)/main.o $(OBJ_DIR)/functions.o
