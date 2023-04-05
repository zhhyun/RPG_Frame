#include	"Game.h"
#include	"DEFINES.h"
#include	"PlayerObject.h"
#include	"NpcObject.h"
#include	"InputComponent.h"

namespace GameFrame {
	Game::Game() :
		mWindow(nullptr),
		IsRunning(true),
		mRenderer(nullptr),
		mTexture(nullptr),
		mIsUpdating(false),
		Font(nullptr)
	{

	}
	
	bool Game::Initialize() {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			SDL_Log("��ʼ��ʧ��:%s", SDL_GetError());
			return false;
		}

		mWindow = SDL_CreateWindow(
			"Test Game Frame 2022-10-1", 
			400,			//x
			200,			//y
			ScreenW,		//w
			ScreenH,		//h
			0);

		if (!mWindow) {
			SDL_Log("���ڳ�ʼ��ʧ��:%s", SDL_GetError());
			return false;
		}

		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
		
		if (!mRenderer) {
			SDL_Log("��Ⱦ����ʼ��ʧ��:%s", SDL_GetError());
			return false;
		}

		if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
			SDL_Log("image��ʼ��ʧ��:%s", SDL_GetError());
			return false;
		}
		if (TTF_Init() == -1){
			SDL_Log("ttf��ʼ��ʧ��:%s", SDL_GetError());
			return false;
		}

		LoadData();

		return true;
	}
	
	void Game::shutdown()
	{
		Unload();
		SDL_DestroyWindow(mWindow);
		SDL_DestroyRenderer(mRenderer);
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	void Game::loop() {
		while (IsRunning) {
			Event();
			Update();
			Draw();
		}
	}

	

	void Game::Event()
	{
		SDL_Event event;


	//�����������¼������ж��¼�������
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				IsRunning = false;
				break;
			default:
				break;
			}
		}
		
		const uint8_t* keyState = SDL_GetKeyboardState(NULL);
		
		mIsUpdating = true;
		GetGameObject<PlayerObject>()->GetComponent<InputComponent>()->ProcessInput(keyState);
		mIsUpdating = false;

	}

	void Game::CreateGameObject(GameObject* gameobject)//�����������ǽ��������˵���Ϸ����ע�ᵽgame��������
		//�ڳ����ﶨ��һ����Ϸ���󲻴�������Ϸ�ﴴ��һ����Ϸ����
		//����Ϸ�ﴴ��������Game��Ĵ�����������ʵ��
		//����������һ���ɸö�����ʱ ȥ�� ���Լ���ϵ��game���� ����
		//���ݵĲ������Ƕ�������Լ���ָ�룬�൱�ڰ��Լ�ע�ᵽGame������
	{
		if (mIsUpdating) {
			//����״̬�´�������Ϸ���󶼷��ڵȴ�����
			mPendingObjects.emplace_back(gameobject);
			//emplace_back��������β����
		}
		else {
			mGameObjects.emplace_back(gameobject);
		}
	}

	void Game::RemoveGameObject(GameObject* gameobject)
	{
		//find����vector��a��b�ڵ�ָ��Ԫ��
		//������һ��ָ���Ԫ�صĵ�����
		auto iter = std::find(mPendingObjects.begin(), mPendingObjects.end(), gameobject);

		if (iter != mPendingObjects.end()) {
			//��ɾ��Ԫ���Ƶ���β
			std::iter_swap(iter, mPendingObjects.end() - 1);
			//�ƻ�˳��ɾ����β
			mPendingObjects.pop_back();//
		}

		 iter = std::find(mGameObjects.begin(), mGameObjects.end(), gameobject);
		 if (iter != mGameObjects.end()){
			 std::iter_swap(iter, mPendingObjects.end() - 1);
			 //�ƻ�˳��ɾ����β
			 mPendingObjects.pop_back();//
		 }
	}

	SDL_Texture* Game::GetTexture(const std::string& filename)
	{
		SDL_Texture* tex = nullptr;
		auto iter = mTextures.find(filename);
		if (iter != mTextures.end()) {
			tex = iter->second;
		}
		return tex;
	}

	void Game::Update()
	{
		SDL_Delay(10);

		mIsUpdating = true;
		for (auto gameobejct : mGameObjects) {
			gameobejct->update();
		}

		mIsUpdating = false;

		for (auto pendingObject : mPendingObjects) {
			mGameObjects.emplace_back(pendingObject);
		}

		mPendingObjects.clear();

		std::vector<GameObject*> deadObject;
		for (auto deadObject : mGameObjects) {
			//if(deadObject)
		}

		for (auto deadObject : deadObject) {
			delete deadObject;
		}
	}

	void Game::Draw()
	{
		//���������
		SDL_RenderClear(mRenderer);


		SDL_Color textColor{ 255,255,255 };
		int m_Width;
		int m_Height;
		
		SDL_Surface* textSurface = TTF_RenderText_Solid(Font, "sdl_ttf", textColor);
		if (!textSurface)
		{
			SDL_Log("ʧ��:%s", SDL_GetError());
		}
		else
		{
			mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
			if (!mTexture)
			{
				SDL_Log("ʧ��:%s", SDL_GetError());
			}
			else
			{
				int textureW;
				int textureH;
				SDL_Rect soildRect = { 0,0,textSurface->w,textSurface->h };
				SDL_RenderCopy(mRenderer, mTexture, nullptr, &soildRect);
				// ���������������������С��
				m_Width = textSurface->w;
				m_Height = textSurface->h;
			}
		}



		// �ͷ���ʱ����
		SDL_FreeSurface(textSurface);

		for (auto iter : mGameObjects) {
			iter->Draw(mRenderer);
		}

		//����������
		SDL_RenderPresent(mRenderer);
	}
	

	void Game::LoadTexture(const std::string& fileName, const std::string& newName) {
		auto iter = mTextures.find(newName);
		if (iter != mTextures.end()) {
			SDL_DestroyTexture(iter->second);
			mTextures.erase(iter);
		}

		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf) {
			SDL_Log("ͼƬ����ʧ��");
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex) {
			SDL_Log("ͼƬ��ʽת��ʧ��");
		}

		mTextures.emplace(newName,tex);
	}

	void Game::LoadData()
	{
		LoadTexture("sprite/2.png",	"Player");
		LoadTexture("sprite/1.png", "Npc");
		Font = TTF_OpenFont("Fonts/1.TTF", 28);
		PlayerObject* Player = new PlayerObject(this);
		NpcObject* Npc = new NpcObject(this);
	}
	void Game::Unload()
	{
		
		//SDL_DestroyTexture(mTexture);
		while (!mGameObjects.empty())
		{
			delete mGameObjects.back();
		}
	}
}


