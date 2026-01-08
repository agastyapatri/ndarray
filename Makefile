CC = clang
CFLAGS = -std=c23 -Wall -Wextra -O2
SRCS = main.c ndarray.c ndarray_math.c 
LDFLAGS = -lm
TARGET = main
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $(TARGET)
