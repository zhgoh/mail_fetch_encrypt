### General variables to change
OUTPUT_NAME = test
SRC = main.cpp

### More or less fixed variables below
CC = g++

BIN_DIR = bin/
OBJ_DIR = obj/
SRC_DIR = src/

# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .cpp of all words in the macro SRC
# with the .o suffix
OBJ = $(SRC:.cpp=.o)

# Concat obj/ to all the obj
_OBJ := $(addprefix $(OBJ_DIR), $(OBJ))

# Make sure that when make encounters a file named clean, don't invoke the clean rule
.PHONY : clean

### Make file rules to build a program to the obj/ folder from src/ folder

program : $(_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(_OBJ) -o $(BIN_DIR)$(OUTPUT_NAME) 

# Pattern matching rule
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	$(CC) -c $< -o $@

clean :
	rm -rf obj bin

### New line needed for make
