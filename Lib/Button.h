#pragma once
#include "RavelEngine.h"
#include "Component.h"
#include "Factory.h"

template <class T>
class Button : public Component {
public:
	Button();
	virtual ~Button();

	virtual void OnStart();
	virtual void Update();
	virtual void OnDestory();

	virtual void OnMouseDown();

	void AddLisenter( RavelAction callback );

	size_t _id;
	T* obj;

private:
	using Callback = void (T::*)(int ID);
	Callback func;

	RavelAction _Callback;

public:
	void BindCallback(Callback functor);
};

template <class T>
Button<T>::Button()
{
}

template <class T>
Button<T>::~Button()
{
}

template <class T>
void Button<T>::OnStart()
{
}

template <class T>
void Button<T>::Update()
{
}

template <class T>
void Button<T>::OnDestory()
{
}

template <class T>
void Button<T>::OnMouseDown()
{
	(obj->*func)(_id);
}

template<class T>
inline void Button<T>::AddLisenter(RavelAction callback)
{
	_Callback = callback;
}

template<class T>
void Button<T>::BindCallback(Callback functor)
{
	func = functor;
}