#ifndef __NpcObject__
#define __NpcObject__
#include "ActorObject.h"

namespace GameFrame {
	class NpcObject : public ActorObject {
	public:
		NpcObject(Game* game, MapObject* map, const std::string& name);
		~NpcObject();

	private:

	};
}
#endif __NpcObject__