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
#include	"AnimSpriteComponent.h"

using namespace std;
namespace GameFrame { 
	class Dialogbox : public ScreenUi {
	public:
		Dialogbox(class Game* game, const string& fileName);//游戏地址；对话剧本文件名
		~Dialogbox();
		void HandKeyPress(int key)override;
		void Draw(SDL_Renderer* renderer) override;
		void AddText(const string& text, const string& speaker);
		void RemoveText(const string& text){};
		void LoadScript(const string& filename);
		void update()override;
		void close()override;

		typedef struct ActorDialog {
			vector<string> dialogue;
			string speaker;
		}ActorDialog;
		typedef struct ActorDialogTexture {
			vector<Texture*> dialogue;
			Texture* speaker;
		}ActorDialogTexture;

		bool IsFin;

		friend class ActorObject;

	private:
		void NextText();
		void DrawText(SDL_Renderer* renderer);
		void DrawSpeakerBox(SDL_Renderer* renderer);
		void StringDecode(string str, const string& splits, vector<string>& rst);

		Texture* Portrait;
		vector<ActorDialogTexture*> CurrTextTex;//当前渲染出的文本图像
		int CurrText;//当前渲染文本在容器中的位置
		vector<ActorDialog*> mTexts;//格式化文本库//每一个元素都是一段格式化后的文本，格式化文本用容器储存
		Font* mTextFont;//字体
		//AnimSpriteComponent* OpenAnim;
		//每次绘画新的对话都从格式化文本库mTexts中取出新的文本，然后渲染成图像放到CurrTextTex里，产生下个对话时则先释放掉旧对话纹理，再渲染新的存入
		ActorDialogTexture* TextConverToTexture(ActorDialog* strlist);
		AnimSpriteComponent* mAnimComponent;
	};
}

#endif __Dialogbox__