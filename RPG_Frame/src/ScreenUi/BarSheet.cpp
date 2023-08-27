#include	"BarSheet.h"
#include	"DEFINES.h"
#include	"PlayerObject.h"	

GameFrame::BarSheet::BarSheet(Game* game, const std::string& fileName, PlayerObject* Player):
	ScreenUi(game,fileName)
{
	Player = Player;
	keyOccup = UiKeyOccupy::ENone;
}

GameFrame::BarSheet::~BarSheet()
{
}

void GameFrame::BarSheet::Draw(SDL_Renderer* renderer)
{
	//取底部的bar
	/*SDL_Rect imageRect{ 0,0,BarSHEET_W,BarSHEET_H };
	/*SDL_Rect dstRect{ BarSHEET_X, BarSHEET_Y,BarGameSHEET_W,BarGameSHEET_H };*/
	//SDL_Rect imageRect{ 0,0,531,236 };
	//SDL_Rect dstRect{ 0, 0,531*0.6,236*0.6 };
	//SDL_RenderCopy(renderer, mTexture, &imageRect, &dstRect);*/

	////画血条
	//SDL_SetRenderDrawColor(renderer, 220, 20, 60, 255);
	//// 设置长方形的坐标以及宽高
	//SDL_Rect rect;
	//rect.x = HP_X * BAR_SCREEN_SCALE;
	//rect.y = HPBarSHEET_Y_IN_SCREEN + 5;
	//rect.w = HP_W * BAR_SCREEN_SCALE * ( (float)Player->GetHp() / (float)Player->GetMaxHp() );
	//rect.h = HPBarSHEET_H_IN_SCREEN - 10;
	//SDL_RenderFillRect(renderer, &rect);

	////取血条框
	//imageRect.x = HPBARSHEET_X;
	//imageRect.y = HPBARSHEET_Y;
	//imageRect.w = HPBARSHEET_W;
	//imageRect.h = HPBARSHEET_H;
	//dstRect.x = HPBarSHEET_X_IN_SCREEN;
	//dstRect.y = HPBarSHEET_Y_IN_SCREEN;
	//dstRect.w = HPBarSHEET_W_IN_SCREEN;
	//dstRect.h = HPBarSHEET_H_IN_SCREEN;
	//SDL_RenderCopy(renderer, mTexture, &imageRect, &dstRect);
}
