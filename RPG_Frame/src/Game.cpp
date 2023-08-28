#include	"Game.h"
#include	"DEFINES.h"
#include	"PlayerObject.h"
#include	"NpcObject.h"
#include	"InputComponent.h"
#include	"MoveComponent.h"
#include	"MapObject.h"
#include    <Python.h>
#include	"BarSheet.h"
#include	"PauseMenu.h"
#include	<algorithm>

#include	<thread>
#include	<queue>
#include	<functional>
#include	<mutex>

#include	"Cursor.h"
#include	"Fonts.h"
#include	"Dialogbox.h"
#include	"BattleSystem.h"
#include	"Script.h"
#include	"Camera.h"


namespace GameFrame {
	Game::Game() :
		mWindow(nullptr),
		IsRunning(true),
		mGameState(GameState::EActive),
		mRenderer(nullptr),
		mTexture(nullptr),
		mIsUpdating(false),
		ProcessEvents(true),
		mTickCount(0),
		mCursor(nullptr),
		mAnimTickCount(0)
	{
		mInputSystem = new InputSystem;
	}
	
	bool Game::Initialize() {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			SDL_Log("初始化失败:%s", SDL_GetError());
			return false;
		}

		mWindow = SDL_CreateWindow(
			PROGRAMME_TITLE,
			SCREEN_X,			//x
			SCREEN_Y,			//y
			SCREEN_W,			//w
			SCREEN_H,			//h
			0);

		if (!mWindow) {
			SDL_Log("窗口初始化失败:%s", SDL_GetError());
			return false;
		}

		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
		
		if (!mRenderer) {
			SDL_Log("渲染器初始化失败:%s", SDL_GetError());
			return false;
		}

		if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
			SDL_Log("image初始化失败:%s", SDL_GetError());
			return false;
		}
		if (TTF_Init() == -1){
			SDL_Log("ttf初始化失败:%s", SDL_GetError());
			return false;
		}
		if(!mInputSystem->Initialize()) {
			SDL_Log("输入处理系统初始化失败:%s", SDL_GetError());
			return false;
		}
		//初始化python
		Py_Initialize();
		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append('./scripts')");

		//禁用系统光标
		SDL_ShowCursor(SDL_FALSE);

		LoadData();

		return true;
	}
	
	void Game::shutdown()
	{
		Unload();
		SDL_DestroyWindow(mWindow);
		SDL_DestroyRenderer(mRenderer);
		mInputSystem->ShutDown();
		TTF_Quit();
		Py_Finalize();
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
		if (ProcessEvents) {
			SDL_Event event;
			bool IsTo = true;
			mInputSystem->PrepareUpdate();
			//当队列中有事件，则判断事件的类型
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					IsRunning = false;
					break;
				case SDL_KEYDOWN:
					//优先检测ui,决定键值传递
					//全部传递到ui里，适用于主菜单，背包等类
					if (!mUIStack.empty() && mUIStack.back()->GetKeyOccurpy() == PauseMenu::UiKeyOccupy::EFull) {
						mUIStack.back()->HandKeyPress(event.key.keysym.sym);
						IsTo = false;
					}
					////只针对单个值传递，适用于和游戏机制同时运行的ui
					//else if (mUIStack.back()->GetKeyOccurpy() == PauseMenu::UiKeyOccupy::EHalf) {

					//}
				//检查键值是否启动ui
					else if (event.key.keysym.sym == SDLK_SPACE) {
						auto mPauseMenu = new PauseMenu(this, "PauseMenu");
						IsTo = false;
					}
					else if (event.key.keysym.sym == SDLK_1) {
						Texture* tex = new Texture("Bridge");
						tex->CreateFromTexture(GetTexture("Bridge"));
						mBattleSystem = new BattleSystem(tex, this, Player);
					}
					else if (event.key.keysym.sym == SDLK_RETURN) {
						auto testScript = new Script();
						mScriptStack.emplace_back(testScript);

						auto i = new Script::Activity();
						i->InitAct([this, i] {
							if (i->state == Script::ScriptState::Running) {
								if (Player->GetmDialog()->IsFin) {
									Player->CloseDialog();
									i->state = Script::ScriptState::Fin;
								}
							}
							else if (Player->GetLv() == 1 && i->state == Script::ScriptState::Hide) {
								i->state = Script::ScriptState::Running;
								Player->CreateDialog("./scripts/1.txt");
							}
							});

						auto j = new Script::Activity();
						j->InitAct([this, j] {
							Vector2 p = { 500,500 };
							if (j->state == Script::ScriptState::Running) {
								if (Player->GetComponent<MoveComponent>()->MoveTo(p)) {
									j->state = Script::ScriptState::Fin;
								}
							}
							else if (Player->GetLv() == 1 && j->state == Script::ScriptState::Hide) {
								j->state = Script::ScriptState::Running;
								Player->GetComponent<MoveComponent>()->MoveTo(p);
							}
							});

						testScript->AddActivity(i);
						testScript->AddActivity(j);
						IsTo = false;
					}
				default:
					break;
				}
			}

			mIsUpdating = true;

			if (IsTo) {
				//输入系统获取设备状态
				mInputSystem->update();
				ProcessInput();
			}

			mIsUpdating = false;
		}
		
	}


	void Game::AddGameObject(GameObject* gameobject, const std::string& Name)
	{
		//排序、判断游戏更新状态并插入指定容器
		mGameObjects.emplace(Name, gameobject);
	}

	void Game::RemoveGameObject(GameObject* gameobject)
	{
		////find查找vector从a到b内的指定元素
		////并返回一个指向该元素的迭代器
		//auto iter = std::find(mPendingObjects.begin(), mPendingObjects.end(), gameobject);

		//if (iter != mPendingObjects.end()) {
		//	//将删除元素移到队尾
		//	std::iter_swap(iter, mPendingObjects.end() - 1);
		//	//破坏顺序删除队尾
		//	mPendingObjects.pop_back();//
		//}

		// iter = std::find(mGameObjects.begin(), mGameObjects.end(), gameobject);
		// if (iter != mGameObjects.end()){
		//	 std::iter_swap(iter, mPendingObjects.end() - 1);
		//	 //破坏顺序删除队尾
		//	 mPendingObjects.pop_back();//
		// }
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

	GameObject* Game::GetGameObject(const std::string& name)
	{
		GameObject* go = nullptr;
		auto iter = mGameObjects.find(name);
		if (iter != mGameObjects.end()) {
			go = iter->second;
		}
		return go;
	}

	void Game::ProcessInput()
	{
		if (!mGameObjects.empty()) {
			for (auto gameobejct = mGameObjects.begin(); gameobejct != mGameObjects.end(); gameobejct++) {
				gameobejct->second->ProcessInput(mInputSystem);
			}
		}
		//更新鼠标状态，鼠标状态具体会触发什么事件交给各个ui的update判定
		auto mouse = mInputSystem->GetState().mouse;
		mCursor->SetMousePos(mouse.mMousePos);
		
		if ((mouse.mCurrState & SDL_BUTTON(SDL_BUTTON_LEFT)) == 1) {
			mCursor->SetIsPress(PressState::PLeft);
		}
		else if ((mouse.mCurrState & SDL_BUTTON(SDL_BUTTON_RIGHT)) == 1) {

		}
		else if ((mouse.mCurrState & SDL_BUTTON(SDL_BUTTON_MIDDLE)) == 1) {

		}
		else {
			mCursor->SetIsPress(PressState::None);
		}
	}

	void Game::SetAnimTicks(Uint32 count)
	{
		mAnimTickCount = count;
	}

	void Game::PushUI(ScreenUi* ui)
	{
		mUIStack.emplace_back(ui);
	}

	Font* Game::GetFont(const std::string& Fontname)
	{
		Font* f = nullptr;
		auto iter = mFonts.find(Fontname);
		if (iter != mFonts.end()) {
			f = iter->second;
		}
		return f;
	}

	void Game::Update()
	{

		if (mGameState == GameState::EPause) {
			mUIStack.back()->update();
			return;
		}

		float fm = (1.0 / FPS) * 1000.0f;//单位毫秒
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + fm))
			;
		mTickCount = SDL_GetTicks();
		//float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;//单位秒
		mIsUpdating = true;

		//剧本先于其他对象更新
		if (!mScriptStack.empty()) {
			for (auto script : mScriptStack) {
				script->update();
			}
		}
		if (mCamera) {
			mCamera->Update();
		}
		if (!mGameObjects.empty()) {
			for (auto gameobejct = mGameObjects.begin(); gameobejct != mGameObjects.end(); gameobejct++) {
				gameobejct->second->update();
			}
		}
		//mPhysSpace->Update();
		if (!mUIStack.empty()) {
			//更新ui
			for (auto ui : mUIStack) {
				if (ui->GetState() == ScreenUi::State::EActive) {
					ui->update();//检查鼠标是否在ui界面按钮上的函数写在ui的update中
				}	
			}
			//删除关闭状态的ui
			for (auto ui = mUIStack.begin(); ui != mUIStack.end(); ) {
				if (( * ui)->GetState() == ScreenUi::State::EDead) {
					ui = mUIStack.erase(ui);
					continue;
				}
				ui++;
			}
		}
		

		mIsUpdating = false;

		for (auto pendingObject : mPendingObjects) {
			//mGameObjects.emplace(pendingObject);
		}

		mPendingObjects.clear();

		std::vector<GameObject*> deadObject;
		/*for (auto deadObject : mGameObjects) {
			if(deadObject)
		}*/

		for (auto deadObject : deadObject) {
			delete deadObject;
		}
	}

	void Game::Draw()
	{
		//清除缓冲区
		SDL_RenderClear(mRenderer);
		if (mTexture)
		{
			SDL_DestroyTexture(mTexture);
		}

		GetGameObject("1")->Draw(mRenderer);
		
		if (!mUIStack.empty()) {
			for (auto ui : mUIStack) {
				ui->Draw(mRenderer);
			}
		}
		if (mBattleSystem) {
			mBattleSystem->Draw(mRenderer);
		}

		mCursor->Draw(mRenderer);
		//交换缓冲区
		SDL_RenderPresent(mRenderer);
	}
	
	void Game::LoadTexture(const std::string& loadpath, const std::string& newName) {
		auto iter = mTextures.find(newName);
		if (iter != mTextures.end()) {
			SDL_DestroyTexture(iter->second);
			mTextures.erase(iter);
		}

		SDL_Surface* surf = IMG_Load(loadpath.c_str());
		if (!surf) {
			SDL_Log("图片加载失败");
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex) {
			SDL_Log("图片格式转换失败");
		}

		mTextures.emplace(newName,tex);
	}

	void Game::LoadData()
	{	
		LoadTexture("Portraits/PC Computer - Sakura Dungeon - Cat.png", "Cat");
		LoadTexture("sprite/1.png", "Npc"); 
		LoadTexture("sprite/2.png",	"Player");
		LoadTexture("sprite/tilesheet_0.png", "tile"); 
		LoadTexture("sprite/barsheet.png", "barsheet");
		LoadTexture("sprite/PauseMenu.png", "PauseMenu");
		LoadTexture("sprite/Button.png", "Button");
		LoadTexture("sprite/Cursor.png", "Cursor");
		LoadTexture("sprite/Alfonse.png", "Alfonse");
		LoadTexture("sprite/Mobile - Fire Emblem Heroes - Bridge.png", "Bridge");
		LoadTexture("sprite/mainBoard.png", MainBoard);
		
		LoadTexture("sprite/Dialog_Speeker.png", "Dialog_Speeker");
		LoadTexture("sprite/Dialog_OptionsBox.png", "Dialog_OptionsBox");
		LoadTexture("sprite/DialogOpenAnim.png", "DialogOpenAnim");
		LoadTexture("sprite/DialogCloseAnim.png", "DialogCloseAnim");
		
		LoadTexture("sprite/Mainmenu.png", "Mainmenu");

		auto QingNiaoHuaGuang = new Font(this);
		if (QingNiaoHuaGuang->Load("Fonts/1.TTF")) {
			mFonts.emplace("QingNiaoHuaGuang",QingNiaoHuaGuang);
		}
		//mEventThread = new EventThread(this);
		LoadMap();
		
		Texture* cur = new Texture("Cursor");
		cur->CreateFromTexture(GetTexture("Cursor"));
		mCursor = new Cursor(cur);
		mCamera = new Camera(this);
		//
		////测试添加事件
		//GameEvent* event_01 = new GameEvent(GameEvent::EventType::MoveEvent, (std::string)"0000001", (std::string)"upmove");
		//mEventThread->GetManager()->RegisterEvent(event_01);
		//
		//for (int i = 0; i < 10; ++i) {
		//	Event event("Event " + std::to_string(i));
		//	mtx.lock();
		//	eventQueue.push(event);
		//	mtx.unlock();
		//	std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 模拟事件产生间隔
		//}

		//BarSheet* paused = new BarSheet(this, "PauseMenu", Player);
		//Player->BattleStart(Npc);
	}
	
	void Game::Unload()
	{
		SDL_DestroyTexture(mTexture);
		while (!mGameObjects.empty())
		{
			//delete mGameObjects.back();
		}
	}
	

	//GameEvent::EventType StringToEventType(const std::string& eventTypeStr) {
	//	if (eventTypeStr == "Collision") {
	//		return GameEvent::EventType::CollisionEvent;
	//	}
	//	else if (eventTypeStr == "SysEvent") {
	//		return GameEvent::EventType::SysEvent;
	//	}
	//	else if (eventTypeStr == "MoveEvent") {
	//		return GameEvent::EventType::MoveEvent;
	//	}
	//	// 如果无法识别字符串，可以返回一个默认值或抛出异常
	//	//return ;
	//}

	void Game::LoadSysEvent(const std::string& loadpath)
	{
		std::ifstream inputFile(loadpath);
		if (!inputFile.is_open()) {
			SDL_Log("Load json error.");
			return;
		}

		nlohmann::json jsonData;

		inputFile >> jsonData;
		inputFile.close();

		//std::vector<GameEvent> presetEvents;
		/*for (const auto& event : jsonData) {
			GameEvent presetEvent(event["eventID"]);
			mSystemEvents.push_back(&presetEvent);
		}*/

	}

	void Game::LoadMap() {
		MapObject* map = new MapObject(this, "MAP","1");
		//Npc = new NpcObject(this, village_sence, "Npc");
		Player = new PlayerObject(this, map->GetCurrSence(), "Player");
	}


}