#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

class Handle;

class Manager {
public:
	Manager() {}
	virtual void init() = 0;
	virtual void update(void* = NULL) = 0;
	virtual Handle createComponent(void* = NULL) = 0;
	virtual ~Manager() {};
};

#endif