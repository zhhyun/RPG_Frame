#ifndef __Dialogbox__
#define __Dialogbox__
#include	"ScreenUi.h"
#include	"Math2.h"
#include	<SDL.h>
#include	<string>
#include	<vector>
#include	"Texture.h"
#include	<algorithm>
#include	"Fonts.h"

namespace GameFrame { 
	class Dialogbox : public ScreenUi {
	public:
		Dialogbox(class Game* game, const std::string& fileName, const std::string& portrait, class Font* font);
		~Dialogbox();
		void HandKeyPress(int key)override;
		void NextText();
		void Draw(SDL_Renderer* renderer) override;
		void AddText(const std::string& text);
		void RemoveText(const std::string& text);

	private:
		Texture* Portrait;
		Texture* CurrTextTex;//��ǰ��Ⱦ�����ı�
		int CurrText;
		std::vector<std::string> mTexts;//�ı���
		Font* mTextFont;//����
	};
}

#endif __Dialogbox__