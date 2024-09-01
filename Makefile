CC=tcc

BINS=kill tty touch echo mount sync umount nice sleep tee wc yes rev ln
all: $(BINS)

$(BINS): %: %.c
	$(CC) -w -o $@ $<

clean:
	rm $(BINS)
