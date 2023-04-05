#ifndef __SpriteComponent__
#define __SpriteComponent__
#include "Component.h"

namespace GameFrame {
	class GameObject;
	class SpriteComponent : public Component {
	public:
		SpriteComponent(GameObject *gameobject, int draworder);
		~SpriteComponent(); 
		virtual void Draw(SDL_Renderer* renderer);
		virtual void SetTexture(SDL_Texture* texture);
	protected:
		SDL_Texture* mTexture;
		int mDrawOrder;
		int mTexWidth;
		int mTexHeight;
	};
}
#endif __SpriteComponent__