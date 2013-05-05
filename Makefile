simpletun:
	gcc src/tun.c -o tun
	gcc src/tunserver.c -o tunserver
	gcc src/tunclient.c -o tunclient
	gcc src/tunclient-udp.c -o tunclient-udp
	gcc src/sendpasswd.c -o sendpasswd
	gcc src/recvpasswd.c -o recvpasswd
	gcc src/curvecpclientauth.c -o curvecpclientauth
	gcc src/ucspi-socks4aclient.c -o ucspi-socks4aclient
