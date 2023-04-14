#ifndef __SpriteComponent__
#define __SpriteComponent__
#include "Component.h"
#include <string>
#include <unordered_map>

namespace GameFrame {
	class GameObject;
	class SpriteComponent : public Component {
	public:
		SpriteComponent(GameObject *gameobject, int draworder);
		~SpriteComponent(); 
		virtual void Draw(SDL_Renderer* renderer);
		void LoadTexture(std::string& fileName);//将贴图装载到容器中
		SDL_Texture* GetTexture(std::string& fileName);

	protected:
		SDL_Texture* mTexture;
		int mDrawOrder;
		//int mTexWidth;
		//int mTexHeight;
		std::unordered_map<std::string, SDL_Texture*> mTextures;
	};
}
#endif __SpriteComponent__