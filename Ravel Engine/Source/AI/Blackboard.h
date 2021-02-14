#pragma once
#include "../types.h"

#include <map>
#include <string>

namespace Ravel {
	namespace AI {
		class Blackboard {
		public:
			Blackboard() {};
			~Blackboard() {};

			// getter and setter
			bool GetBlackboardValueAsBool(std::string keyID);
			int GetBlackboardValueAsInt(std::string keyID);

		private:
			std::map<std::string, BaseObject*> m_Keys;
		};
	}
}