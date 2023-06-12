CPP      = $(CROSS_COMPILE)g++
LD      = $(CROSS_COMPILE)ld

BIN = tx
OBJS = $(BIN).o


CFLAGS += -Wall -O0 -I./




.PHONY: all
all: $(BIN)

$(BIN): $(OBJS)
	$(CPP) -o $@ $< 
.PHONY: clean
clean:
	rm -f $(OBJS) $(BIN)

%.o: %.cc
	$(CPP) $(CFLAGS) -c $< -o $@
