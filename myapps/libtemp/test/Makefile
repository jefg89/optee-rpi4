CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld


OBJS = test.o
BIN = temp_test

#CFLAGS += -Wall -I../ta/include -I$(TEEC_EXPORT)/include -I./include
CFLAGS += -Wall -I../include
LDADD += -ltemp -L../src
#Add/link other required libraries here
#LDADD += -lteec -L$(TEEC_EXPORT)/lib



.PHONY: all
all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $< $(LDADD)

.PHONY: clean
clean:
	rm -f $(OBJS) $(BIN)

%.o: %.c
	@echo "GCC is $(CC)"
	$(CC) $(CFLAGS) -c $< -o $@

