CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
AR      = $(CROSS_COMPILE)ar
NM      = $(CROSS_COMPILE)nm


OBJS = temp.o
LIBA = libtemp.a

#CFLAGS += -Wall -I../ta/include -I$(TEEC_EXPORT)/include -I./include
CFLAGS += -Wall -I../include
#Add/link other required libraries here
#LDADD += -lteec -L$(TEEC_EXPORT)/lib



.PHONY: all
all: $(LIBA)

$(LIBA): $(OBJS)
	$(AR) -rcs $@ $<

.PHONY: clean
clean:
	rm -f $(OBJS) $(LIBA)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

