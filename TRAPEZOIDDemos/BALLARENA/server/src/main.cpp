#include <iostream>
#include "server.h"

int main() {
	int port;
	std::cout << "Enter Port: ";
	std::cin >> port;
	Server server(port);
	while (1) {
		server.update();
	}

}