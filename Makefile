CC=tcc

BINS=kill tty touch echo mount sync umount nice sleep
all: $(BINS)

$(BINS): %: %.c
	$(CC) -o $@ $<

clean:
	rm $(BINS)
