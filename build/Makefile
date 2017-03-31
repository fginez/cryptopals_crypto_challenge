OUTDIR=./bin/

src = \
  $(wildcard ../src/crypto/*.c) \
	$(wildcard ../src/tests/*.c) \
	$(wildcard ../src/util/*.c)

obj = $(src:.c=.o)

CFLAGS=-Wall
LDFLAGS=-lrt -lm -lcrypto

.PHONY: clean cryptopals_crypto_challenge

all:	cryptopals_crypto_challenge

debug:	CFLAGS+=-DDEBUG -D_DEBUG -g
debug:	CFLAGS+=-D_AES_DEBUG
debug:	all

cryptopals_crypto_challenge: $(obj)
	$(CC) -o $(OUTDIR)/$@ $^ $(LDFLAGS)

clean:
	rm -f $(obj) $(OUTDIR)/cryptopals_crypto_challenge
