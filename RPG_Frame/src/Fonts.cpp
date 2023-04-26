#include "Fonts.h"
#include "Game.h"

GameFrame::Font::Font(Game* game):
	mGame(game)
{
}

GameFrame::Font::~Font()
{
}

bool GameFrame::Font::Load(const std::string& fileName)
{
	std::vector<int> fontSizes = {
		8,9,10,11,12,14,16,18,20,22,24,26,28,
		30,32,34,36,38,40,42,44
	};
	for (auto size : fontSizes) {
		TTF_Font* FONT = TTF_OpenFont(fileName.c_str(), size);
		if (FONT == nullptr) {
			SDL_Log("加载字体失败");
			return false;
		}
		mFontData.emplace(size, FONT);
	}
	return true;
}

GameFrame::Texture* GameFrame::Font::RenderText(const std::string& text, Uint8 R, Uint8 G, Uint8 B, int pointSize)
{
	Texture* texture = nullptr;
	SDL_Color textColor{ R,G,B };
	auto iter = mFontData.find(pointSize);
	if (iter != mFontData.end()) {
		SDL_Surface* textSurface = TTF_RenderUTF8_Blended(iter->second, text.c_str(), textColor);
		if (!textSurface)
		{
			SDL_Log("失败:%s", SDL_GetError());
		}
		else
		{
			texture = new Texture();
			texture->CreateFromSurface(mGame->GetRenderer(), textSurface);
			SDL_FreeSurface(textSurface);
		}
	}
	else {
		SDL_Log("字符生成失败");
	}
	return texture;
}
