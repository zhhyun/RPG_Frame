#ifndef __ScreenUi__
#define __ScreenUi__
#include	"Math2.h"
#include	<SDL.h>
#include	<string>
#include	<vector>
#include	"Texture.h"
#include	<algorithm>
#include	<functional>

namespace GameFrame {
	class ScreenUi {
	public:
		ScreenUi(class Game* game, const std::string& fileName);
		~ScreenUi();
		enum class UiState
		{
			EActive,
			EClosing
		};
		enum class UiKeyOccupy
		{
			EFull,
			EHalf,
			ENone
		};
		UiState GetUiState() { return mState; };
		UiKeyOccupy GetKeyOccurpy() { return keyOccup; };
		void close();
		virtual void ProcessInput(class InputSystem* keystate){};
		virtual void HandKeyPress(int key){};//���ڽ��ܼ���״̬���ڶ�ʱ����Ӧ��Σ�������Ҫ���⺯������Ӧ
		virtual void update();
		virtual void Draw(SDL_Renderer* renderer);
		virtual void AddButton(const std::string& name, Vector2 pos, Texture* tex, std::function<void()> OnClick){};

		void LoadTexture(const std::string& fileName);
		
		std::vector<class Button*> mButtons;

	protected:
		class Game*			mGame;
		int					Width;
		int					Height;
		Vector2				mPos;//����λ��
		UiState				mState;
		class Texture*		mTexture;
		UiKeyOccupy			keyOccup;	//����ռ�������ȫռ�á���ռ�á���ռ�ã�
	};
}


#endif __ScreenUi__