#ifndef __BackpackComponent__
#define __BackpackComponent__
#include "SpriteComponent.h"

namespace GameFrame {
	class GameObject;
	class BackpackComponent : public SpriteComponent {
	public:
		BackpackComponent();
		~BackpackComponent();
		void ProcessInput(const uint8_t* keystate); //override;
		void update(); //override;
	};
}
#endif // __BackpackComponent__
