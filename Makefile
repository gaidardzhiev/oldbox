CC=tcc

BINS=kill tty touch echo mount sync
all: $(BINS)

$(BINS): %: %.c
	$(CC) -o $@ $<

clean:
	rm $(BINS)
