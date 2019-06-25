IDIR =include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=src/obj
LDIR =lib
SRC=src

LIBS =-lncurses

_DEPS = entities.h draw.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = invadescii.o entities.o draw.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SRC)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

invadescii: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ invadescii $(IDIR)/*~ 
