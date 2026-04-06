# Build libs
gcc \
  -Werror -Wpedantic -Wall -g -c -std=c99 \
  -I./lib/nergassert/include \
  ./lib/nergassert/src/nergassert.c \
  -o ./build/nergassert.o 

gcc \
  -Werror -Wpedantic -Wall -g -c -std=c99 \
  -I./lib/nergger/include \
  ./lib/nergger/src/logger.c \
  -o ./build/logger.o 

# Build builder
gcc \
  -Werror -Wpedantic -Wall -g -c -std=c99 \
  -I./include \
  -I./lib/nergassert/include \
  -I./lib/nergger/include \
  ./src/builder.c \
  -o ./build/builder.o 

# Build tests
gcc \
  -Werror -Wpedantic -Wall -g -c -std=c99 \
  -Iinclude \
  -I./lib/nergassert/include \
  -I./lib/nergger/include \
  ./tests/test.c \
  -o ./build/test.o

# Link them togheter 
gcc \
  -Werror -Wpedantic -Wall -g -std=c99 \
  ./build/nergassert.o \
  ./build/logger.o \
  ./build/builder.o \
  ./build/test.o \
  -o ./bin/tests
