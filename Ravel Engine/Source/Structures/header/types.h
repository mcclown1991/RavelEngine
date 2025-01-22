#pragma once

class BaseObject {
public:
	BaseObject() {};
	virtual ~BaseObject() {};
	virtual void OnDestory() {};
};

template<class T>
class Object : public BaseObject {
public:
	Object() {};
	Object(T const& val) {
		this->val = val;
	}
	~Object() {};

	virtual void OnDestory() {
		this->~Object();
	}
	
	T data() const { return val; }
	void set(T const& value) { val = value; }

private:
	T val;
};