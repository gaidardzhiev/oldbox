CC=tcc

BINS=kill tty touch echo mount
all: $(BINS)

$(BINS): %: %.c
	$(CC) -o $@ $<

clean:
	rm $(BINS)
