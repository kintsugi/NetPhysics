#include <iostream>
#include <string>
#include "Engine.h"



int main(int argc, char* argv[]) {
	NetPhysics::Engine engine;
	engine.init();
	while (1) {
		engine.update();
	}
}
		
