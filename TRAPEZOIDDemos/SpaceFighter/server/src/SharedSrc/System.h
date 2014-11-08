#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

class EngineRegister;

class System {
public:

	void virtual init(EngineRegister *engineRegister) {}
	void virtual update(EngineRegister *engineRegister, double dt) {}

};

#endif /* SYSTEM_H_INCLUDED */