#define SCREEN_W 800.0
#define SCREEN_H 600.0
#define SCREEN_SCALE = SCREEN_W/SCREEN_H
#define FPS 60.0
#define PlayerH 64
#define PlayerW 64
#define TILEH 16*2
#define TILEW 16*2
#define PROGRAMME_TITLE  "Test Game Frame 2022-10-1"
#define SCREEN_X 100
#define SCREEN_Y 100

#define BarSHEET_W 480.0
#define BarSHEET_H 17.0
#define BAR_SCREEN_SCALE SCREEN_W / BarSHEET_W

#define BarGameSHEET_W SCREEN_W
#define BarGameSHEET_H BarSHEET_H * BAR_SCREEN_SCALE
#define BarSHEET_X 0
#define BarSHEET_Y SCREEN_H - BarGameSHEET_H +1



#define HPBARSHEET_W 102
#define HPBARSHEET_H 13
#define HPBARSHEET_X 0
#define HPBARSHEET_Y 17
#define HPBarSHEET_X_IN_SCREEN HPBARSHEET_X
#define HPBarSHEET_Y_IN_SCREEN BarSHEET_Y + 7
#define HPBarSHEET_W_IN_SCREEN HPBARSHEET_W * BAR_SCREEN_SCALE
#define HPBarSHEET_H_IN_SCREEN HPBARSHEET_H * BAR_SCREEN_SCALE

#define HP_W 91
#define HP_X 10

#define PLAYERNAME �峤

//��ɫ
#define Crimson		220,20,60	//�ɺ�ɫ
#define Red 		255,0,0		//����
#define White		255,255,255	//����
#define Black 		0,0,0		//����
#define DimGray		105,105,105//�����Ļ�ɫ
#define Orange		255,165,0	//��ɫ
#define OrangeRed	255, 69, 0	//�Ⱥ�ɫ
#define DoderBlue	30,144,255	//������	


//�Ի���
#define DialogueFontSize 30
#define DialogueSpeakerBoxW 220
#define DialogueSpeakerBoxH 62
#define DialogueFontColor Crimson
#define SpeakerFontColor  Orange