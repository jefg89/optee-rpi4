CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
CPP 	=$(CROSS_COMPILE)g++


BIN = sampler
OBJS = $(BIN).o
CFLAGS += -Wall 

.PHONY: all
all: $(BIN)

$(BIN): $(OBJS)
	$(CPP) -o $@ $< 
.PHONY: clean
clean:
	rm -f $(OBJS) $(BIN)

%.o: %.cc
	$(CPP) $(CFLAGS) -c $< -o $@
