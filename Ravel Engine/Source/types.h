#pragma once

class BaseObject {
public:
	BaseObject() {};
	virtual ~BaseObject() {};
};

template<class T>
class Object : public BaseObject {
public:
	Object() {};
	~Object() {};

	T data() const { return val; }
	void set(T const& value) { val = value; }

private:
	T val;
};