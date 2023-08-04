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
		Dialogbox(class Game* game, const string& fileName);//��Ϸ��ַ���Ի��籾�ļ���
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
		vector<ActorDialogTexture*> CurrTextTex;//��ǰ��Ⱦ�����ı�ͼ��
		int CurrText;//��ǰ��Ⱦ�ı��������е�λ��
		vector<ActorDialog*> mTexts;//��ʽ���ı���//ÿһ��Ԫ�ض���һ�θ�ʽ������ı�����ʽ���ı�����������
		Font* mTextFont;//����
		//AnimSpriteComponent* OpenAnim;
		//ÿ�λ滭�µĶԻ����Ӹ�ʽ���ı���mTexts��ȡ���µ��ı���Ȼ����Ⱦ��ͼ��ŵ�CurrTextTex������¸��Ի�ʱ�����ͷŵ��ɶԻ���������Ⱦ�µĴ���
		ActorDialogTexture* TextConverToTexture(ActorDialog* strlist);
		AnimSpriteComponent* mAnimComponent;
	};
}

#endif __Dialogbox__