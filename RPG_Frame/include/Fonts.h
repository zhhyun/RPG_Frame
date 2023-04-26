#ifndef __Fonts__
#define __Fonts__
#include <unordered_map>
#include <SDL_ttf.h>
#include "Texture.h"
#include <string>

namespace GameFrame {
	//Font类储存一种字体,并可以根据给定文本输出纹理
	class Font {
	public:
		Font(class Game* game);
		~Font();
		bool Load(const std::string& fileName);
		void Unload();

		Texture* RenderText(const std::string& text, Uint8 R, Uint8 G, Uint8 B, int pointSize);

	private:
		std::unordered_map<int, TTF_Font*> mFontData;//int是字号
		class Game* mGame;
	};
}

#endif __Fonts__
