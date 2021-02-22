#pragma once
#include "RavelBehaviour.h"

namespace Ravel {
	class Controller : public RavelBehaviour {
	public:
		Controller();
		virtual ~Controller();
		virtual Controller* Clone() {
			return Memory()->alloc<Controller>();
		}

		virtual void OnDestory();
		
	};
}