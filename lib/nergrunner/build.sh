# Build libs
gcc \
  -Werror -Wpedantic -Wall -g -c -std=c23 \
  -I../nergassert/include/ \
  ../nergassert/src/nergassert.c \
  -o ./build/nergassert.o 

gcc \
  -Werror -Wpedantic -Wall -g -c -std=c23 \
  -I../nergger/include \
  ../nergger/src/logger.c \
  -o ./build/logger.o 

# Build runner
gcc \
  -Werror -Wpedantic -Wall -g -c -std=c23 \
  -I./include \
  -I../nergassert/include \
  -I../nergger/include \
  ./src/runner.c \
  -o ./build/runner.o 

# Build tests
gcc \
  -Werror -Wpedantic -Wall -g -c -std=c23 \
  -Iinclude \
  -I../nergassert/include \
  -I../nergger/include \
  ./tests/test.c \
  -o ./build/test.o

# Link them togheter 
gcc \
  -Werror -Wpedantic -Wall -g -std=c23 \
  ./build/nergassert.o \
  ./build/logger.o \
  ./build/runner.o \
  ./build/test.o \
  -o ./bin/tests
