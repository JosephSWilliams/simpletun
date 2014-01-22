# change CC to something else if make has issues
# to determine your systems default C compiler
# CC = gcc46

simpletun:
	@echo 'building simpletun using "$(CC)"'
	$(CC) src/tun.c -o tun
	$(CC) src/tunserver.c -o tunserver
	$(CC) src/tunclient.c -o tunclient
	$(CC) src/tunclient-udp.c -o tunclient-udp
	$(CC) src/sendpasswd.c -o sendpasswd
	$(CC) src/recvpasswd.c -o recvpasswd
	$(CC) src/curvecpclientauth.c -o curvecpclientauth
	$(CC) src/ucspi-socks4aclient.c -o ucspi-socks4aclient

keypair:
	@echo 'building keypair using "$(CC)"'
	$(CC) src/dh.c -o dh -l nacl
	$(CC) src/keypair.c -o keypair -l nacl /usr/lib/randombytes.o
	
all: simpletun keypair
