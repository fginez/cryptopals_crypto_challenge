OUTDIR=./bin/

src = \
  $(wildcard ../src/crypto/*.c) \
	$(wildcard ../src/tests/*.c) \
	$(wildcard ../src/util/*.c)

obj = $(src:.c=.o)

CFLAGS=
LDFLAGS=-lrt -lcrypto

.PHONY: clean cryptopals_crypto_challenge

all: cryptopals_crypto_challenge

cryptopals_crypto_challenge: $(obj)
	$(CC) -o $(OUTDIR)/$@ $^ $(LDFLAGS)

clean:
	rm -f $(obj) $(OUTDIR)/cryptopals_crypto_challenge
