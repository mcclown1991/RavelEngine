#pragma once

class BaseObject {
public:
	BaseObject() {};
	~BaseObject() {};
};

template<class T>
class Object : public BaseObject {
public:
	Object() {};
	~Object() {};

private:
	T val;
};