#ifndef __MapSpriteComponent__
#define __MapSpriteComponent__
#include	"SpriteComponent.h"
#include	<iostream>
#include	<fstream>
#include	<string>
#include	"Math2.h"

namespace GameFrame{
	class MapObject;
	class Elem {
	public:
		friend class MapSpriteComponent;
	private:
		std::string tex;
		Vector2 vec;
	};

	class MapSpriteComponent : public SpriteComponent {
	public:
		MapSpriteComponent(GameObject* mapobject, int draworder, const char* fileName);
		~MapSpriteComponent();

		void Draw(SDL_Renderer* renderer) override;
		void ReadMap(const char* fileName);

	private:
		std::vector <Elem*> mElems;
	};
}
#endif __MapSpriteComponent__