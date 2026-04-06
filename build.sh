
# Build libs
gcc -I./lib/nergassert/include -g -c ./lib/nergassert/src/nergassert.c -o ./build/nergassert.o 
gcc -I./lib/nergger/include -g -c ./lib/nergger/src/logger.c -o ./build/logger.o 

# Build builder
gcc -I./include -I./lib/nergassert/include -I./lib/nergger/include -g -c ./src/builder.c -o ./build/builder.o 

# Build tests
gcc -Iinclude -g -c ./tests/test.c -o ./build/test.o

# Link them togheter 
gcc -Iinclude -g ./build/nergassert.o ./build/logger.o ./build/builder.o ./build/test.o -o ./bin/tests
