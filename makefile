### General variables to change
OUTPUT_NAME = main
SRC = main.cpp

### More or less fixed variables below
CC = g++

# define any compile-time flags
CFLAGS = -std=c++11

# define any directories containing header files other than /usr/include
#
INCLUDES = -Iinclude

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -Llib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:

# Note: The order of the libs matters
LIBS = \
-lgoogle_calendar_api \
-lgoogle_gmail_api \
-lgoogle_storage_api \
-lgoogleapis_oauth2 \
-lgoogleapis_curl_http \
-lgoogleapis_http \
-lgoogleapis_jsonplayback \
-lgoogleapis_scribes \
-ljsoncpp \
-lgoogleapis_jsoncpp \
-lgoogleapis_json \
-lgoogleapis_utils \
-lpthread \
-lcurl \
-lssl \
-lcrypto \
-ldl \
-lgoogleapis_openssl_codec \
-lglog \
-lgoogleapis_internal

# Output folders
BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src

#SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
#OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .cpp of all words in the macro SRC
# with the .o suffix
OBJ = $(SRC:.cpp=.o)

# Concat obj/ to all the obj
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJ))

# Make sure that when make encounters a file named clean, don't invoke the clean rule
.PHONY : clean

### Make file rules to build a program to the obj/ folder from src/ folder

program : $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR)/$(OUTPUT_NAME) $(OBJS) $(LFLAGS) $(LIBS)

# Pattern matching rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	rm -rf obj bin

### New line needed for make
