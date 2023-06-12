CPP      = $(CROSS_COMPILE)g++
LD      = $(CROSS_COMPILE)ld


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

%.o: %.cpp
	$(CPP) $(CFLAGS) -c $< -o $@
