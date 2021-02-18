#pragma once
#include "RavelEngine.h"
#include "RavelBehaviour.h"
#include "Factory.h"

template <class T>
class Button : public RavelBehaviour {
public:
	Button();
	virtual ~Button();
	virtual Button* Clone() {
		return Memory()->alloc<Button<T>>();
	}

	virtual void LoadFromFile(std::string const& file);

	virtual void OnDestory() { 
		_Callback = nullptr;
		obj = nullptr; // release pointer to reference
		this->~Button<T>(); 
	}
	virtual void OnMouseDown();

	void Initialise(T* self) {
		obj = self;
	}
	void AddLisenter( RavelAction<T> callback );

	size_t _id;
	T* obj;

private:
	using Callback = void (T::*)(int ID);
	Callback func;

	RavelAction<T> _Callback;

public:
	void BindCallback(Callback functor);
};

template <class T>
Button<T>::Button() : _id(0), obj(nullptr), func(nullptr), _Callback(nullptr)
{
}

template <class T>
Button<T>::~Button()
{
}

template<class T>
inline void Button<T>::LoadFromFile(std::string const & file)
{
	// do standard loading of component
	std::ifstream json;
	json.open(file);
	rapidjson::IStreamWrapper isw(json);
	rapidjson::Document doc;
	doc.ParseStream(isw);

	if(doc.IsObject()) {
		rapidjson::Value& root = doc["Button"];

		IsActive = root["IsActive"].GetBool();

		Vector2 pos;
		pos.x = root["Transform"]["X"].GetFloat();
		pos.y = root["Transform"]["Y"].GetFloat();

		transform->position = pos;
	}

	json.close();
}

template <class T>
void Button<T>::OnMouseDown()
{
	if (!obj) return;
	//(obj->*func)(_id);
	(obj->*_Callback)();
}

template<class T>
inline void Button<T>::AddLisenter(RavelAction<T> callback)
{
	_Callback = callback;
}

template<class T>
void Button<T>::BindCallback(Callback functor)
{
	func = functor;
}