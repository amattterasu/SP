tcp: 
	g++ -g tcp-server.cpp -o tcp-server 
	g++ -g tcp-client.cpp -o tcp-client 
clear: 
	rm tcp-server 
	rm tcp-client 
	rm udp-server 
	rm udp-client 
udp: 
	g++ -g udp-server.cpp -o udp-server 
	g++ -g udp-client.cpp -o udp-client 


