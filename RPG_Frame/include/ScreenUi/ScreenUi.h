#ifndef __ScreenUi__
#define __ScreenUi__
#include	"Math2.h"
#include	<SDL.h>
#include	<string>
#include	<vector>
#include	"Texture.h"
#include	<algorithm>
#include	<functional>
#include	"GameObject.h"

namespace GameFrame {
	class ScreenUi : public GameObject {
	public:
		ScreenUi(class Game* game, const std::string& fileName);
		~ScreenUi();
		enum class UiKeyOccupy
		{
			EFull,
			EHalf,
			ENone
		};
		UiKeyOccupy GetKeyOccurpy() { return keyOccup; };
		virtual void close();
		virtual void ProcessInput(class InputSystem* keystate){};
		virtual void HandKeyPress(int key){};//���ڽ��ܼ���״̬���ڶ�ʱ����Ӧ��Σ�������Ҫ���⺯������Ӧ
		virtual void update();
		virtual void Draw(SDL_Renderer* renderer);
		virtual void AddButton(const std::string& name, Vector2 pos, Texture* tex, std::function<void()> OnClick){};

		void LoadTexture(const std::string& fileName);
		
		std::vector<class Button*> mButtons;

	protected:
		int					Width;
		int					Height;
		class Texture*		mTexture;
		UiKeyOccupy			keyOccup;	//����ռ�������ȫռ�á���ռ�á���ռ�ã�
	};
}


#endif __ScreenUi__