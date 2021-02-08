CC	= @gcc 
CFLAGS  = -O2 -Wall -g

SOURCES	= main.c jpeg.c bmp.c mkimage.c

OBJECTS	= ${SOURCES:.c=.o}

OUT	= mkimage

LIBS = -ljpeg

all: $(OUT)
	@echo mkimage tool is seccussful!.
	@rm -f $(OBJECTS)

.PHONY: $(OUT)
$(OUT): $(OBJECTS)
	@$(CC) $(LDFLAGS) -o $(OUT) $(OBJECTS) $(LIBS)

