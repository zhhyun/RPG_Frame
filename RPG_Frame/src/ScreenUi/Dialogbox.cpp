#include "Dialogbox.h"
#include "Game.h"
#include "Texture.h"
#include "DEFINES.h"
#include "fstream"
GameFrame::Dialogbox::Dialogbox(Game* game, const std::string& fileName) :
	Portrait(nullptr),
	CurrText(0),
	IsFin(false),
	ScreenUi(game, "Dialog")
{
	Portrait = new Texture("portrait"); 
	//Portrait->CreateFromTexture(mGame->GetTexture(portrait));
	keyOccup = UiKeyOccupy::EFull;
	Width = mTexture->GetWidth();
	Height = mTexture->GetHeight();
	mTextFont = mGame->GetFont("QingNiaoHuaGuang");
	LoadScript(fileName);
	Pos.x = 20;
	Pos.y = SCREEN_H - 220;
	//加载动画效果
	mAnimComponent = new AnimSpriteComponent(this,70);
	//对话打开动画
	Vector2 t = { 0,0 };
	string str1 = "DialogOpenAnim"; 
	string str2 = "DialogCloseAnim";
	Anim* DialogOpenAnim = new Anim(mGame->GetTexture(str1), 5, false, t, 40.0, 1087, 207);
	Anim* DialogCloseAnim = new Anim(mGame->GetTexture(str2), 5, false, t, 40.0, 1087, 206);
	mAnimComponent->AddAnimation(DialogOpenAnim, "DialogOpenAnim");
	mAnimComponent->AddAnimation(DialogCloseAnim, "DialogCloseAnim");
	mAnimComponent->PlayAnimation("DialogOpenAnim");
	//对话旋转指针
	
}

GameFrame::Dialogbox::~Dialogbox()
{
}

void GameFrame::Dialogbox::HandKeyPress(int key)
{
	if (key != SDLK_RETURN)
		return;
	else {
		if (mTexts.size()-1 > CurrText) {
			NextText();
		}
		else {
			IsFin = true;
		}
	}
}

void GameFrame::Dialogbox::NextText()
{
	CurrText++;
	CurrTextTex.emplace_back(TextConverToTexture(mTexts[CurrText]));
}

void GameFrame::Dialogbox::DrawText(SDL_Renderer* renderer)
{
	if (CurrTextTex.empty()) return;
	
	//绘制speaker
	SDL_Rect SpeakerRect{ 0,0,CurrTextTex[CurrText]->speaker->GetWidth(),CurrTextTex[CurrText]->speaker-> GetHeight()};
	SDL_Rect SpeakerdstRect{ 
		Pos.x  + (DialogueSpeakerBoxW - CurrTextTex[CurrText]->speaker->GetWidth() )/2,
		(SCREEN_H - 220 - 75)+ (DialogueSpeakerBoxH - CurrTextTex[CurrText]->speaker->GetHeight() )/2 ,
		CurrTextTex[CurrText]->speaker->GetWidth(),
		CurrTextTex[CurrText]->speaker->GetHeight() };

	SDL_RenderCopy(renderer, CurrTextTex[CurrText]->speaker->GetTexture(), &SpeakerRect, &SpeakerdstRect);

	SDL_Rect TextRect{ 0,0,0,0};
	SDL_Rect TextdstRect{ Pos.x + 25, SCREEN_H - 220 + 25 ,0,0 };
	for (auto iter : CurrTextTex[CurrText]->dialogue) {
		TextRect.w = iter->GetWidth();
		TextRect.h = iter->GetHeight();
		TextdstRect.w = TextRect.w;
		TextdstRect.h = TextRect.h;
		SDL_RenderCopy(renderer, iter->GetTexture(), &TextRect, &TextdstRect);
		TextdstRect.y += 35;
	}
}

void GameFrame::Dialogbox::DrawSpeakerBox(SDL_Renderer* renderer)
{
	auto SpeakerBox = new Texture("SpeekerBox");
	SpeakerBox->CreateFromTexture(mGame->GetTexture("Dialog_Speeker"));
	SDL_Rect SpeekerBoxRect{ 0,0,SpeakerBox->GetWidth(),SpeakerBox->GetHeight()};
	SDL_Rect SpeekerBoxdstRect{ Pos.x, Pos.y - 80 ,SpeakerBox->GetWidth(),SpeakerBox->GetHeight() };//用相对位置
	SDL_RenderCopy(renderer, SpeakerBox->GetTexture(), &SpeekerBoxRect, &SpeekerBoxdstRect);
}

void GameFrame::Dialogbox::Draw(SDL_Renderer* renderer)
{
	mAnimComponent->Draw(renderer);
	if (mAnimComponent->GetIsOver() && mAnimComponent->GetPlayingAnimName() == "DialogOpenAnim") {
		DrawSpeakerBox(renderer);
		DrawText(renderer);
	}
	if (mState == State::EWaitingDead && mAnimComponent->GetPlayingAnimName() == "DialogOpenAnim") {
		mAnimComponent->PlayAnimation("DialogCloseAnim");
	}
	else if (mState == State::EWaitingDead &&
		mAnimComponent->GetIsOver() &&
		mAnimComponent->GetPlayingAnimName() == "DialogCloseAnim") {
		mState = State::EDead;
	}

}

void GameFrame::Dialogbox::AddText(const std::string& text, const string& speaker)
{
	ActorDialog* strlist = new ActorDialog();
	strlist->speaker = speaker;
	StringDecode(text, "%%", strlist->dialogue);
	mTexts.emplace_back(strlist);

	if (CurrTextTex.empty()) {//渲染字体图案并储存
		CurrTextTex.emplace_back(TextConverToTexture(strlist));
	}
}

void GameFrame::Dialogbox::StringDecode(string str, const string& splits, vector<string>& rst)
{
	//读取字符文本，然后解析：
//（说话者）:
//台词（检测换行）
//字符变量替换：%c = 主角名字
//split规则：%%换行
	if (str == "")		return;
	//在字符串末尾也加入分隔符，方便截取最后一段
	string strs = str + splits;
	size_t pos = strs.find(splits);
	int step = splits.size();

	// 若找不到内容则字符串搜索函数返回 npos
	while (pos != strs.npos)
	{
		string temp = strs.substr(0, pos);
		rst.push_back(temp);
		//去掉已分割的字符串,在剩下的字符串中进行分割
		strs = strs.substr(pos + step, strs.size());
		pos = strs.find(splits);
	}
}

void GameFrame::Dialogbox::LoadScript(const string& filename)
{
	ifstream FILE;
	FILE.open(filename, ios::in);
	string str;
	string speaker = "???";
	FILE >> str;
	while (FILE >> str) {
		if (str[0] == '$' || str[str.length()-1] == '$') {
			str.erase(str.begin(), str.begin()+1);
			str.erase(str.end()-1, str.end());
			speaker = str;
		}
		else {
			AddText(str, speaker);
		}
	}
	FILE.close();
}

void GameFrame::Dialogbox::update()
{
	for (auto iter : mComponents) {
		iter->update();
	}
}

void GameFrame::Dialogbox::close()
{
	mState = State::EWaitingDead;
}

GameFrame::Dialogbox::ActorDialogTexture* GameFrame::Dialogbox::TextConverToTexture(ActorDialog* strlist)
{
	ActorDialogTexture* detex = new ActorDialogTexture();
	for (auto& iter : strlist->dialogue) {
		detex->dialogue.emplace_back(mTextFont->RenderText(iter, OrangeRed, DialogueFontSize));
	}
	detex->speaker = mTextFont->RenderText(strlist->speaker, SpeakerFontColor, DialogueFontSize);
	return detex;
}
