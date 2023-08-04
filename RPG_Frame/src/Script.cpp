#include	"Script.h"
#include	"ActorObject.h"
GameFrame::Script::Script():
	mScriptState(ScriptState::Hide),
	EventStack(nullptr),
	RuningAct(nullptr)
{
	EventStack = new ActListLink();
	EventStack->CreateList();
}


void GameFrame::Script::update()
{
	if (mScriptState == Script::ScriptState::Fin) {//如果剧本已经结束则跳过
		return;
	}
	//if (Actors.empty()) {//如果没有参演人员则跳过
	//	return;
	//}
	//剧本发生条件:人物1级且剧本未发生
	if (/*mScriptCondition() && */mScriptState == Script::ScriptState::Hide) {
		SetScriptState(Script::ScriptState::Running);//条件满足，剧本开始//条件应该由外部导入，这里做成一个函数
		//将行动链的第一个结点加载到RuningAct
		RuningAct = EventStack->head->nextNode;
	}
	//如果剧本已经开始
	if (mScriptState == Script::ScriptState::Running) {
		if (RuningAct->data->state == ScriptState::Hide) {
			//如果当前的行为还未开始，则先判断该行为是否发生，如果发生则切换为开始,判断函数写在act()中
			//比如剧本要求获得某个道具后才能交任务，即道具获得后才能触发后续剧情
			RuningAct->data->mAct();	
		}
		else if (RuningAct->data->state == ScriptState::Running) {
			//如果当前的行为正在运行，则跳过
			RuningAct->data->mAct();
			return;
		}
		else {
			//如果当前行动已经结束，则将进度前进
			if (RuningAct->nextNode != nullptr) {
				RuningAct = RuningAct->nextNode;
			}
			else {
				mScriptState = Script::ScriptState::Fin;
				return;
			}
		}
	}
}

void GameFrame::Script::AddActivity(Activity* act) {
	EventStack->Emplace_back(act);
}

GameFrame::ActorObject* GameFrame::Script::FindActor(std::string actorName)
{
	if (Actors.empty()) {
		return nullptr;
	}
	for (auto act : Actors) {
		if (act->GetActorName() == actorName) {
			return act;
		}
	}
	return nullptr;
}

GameFrame::Script::ActListLink::ActListLink():
	head(nullptr),
	tail(nullptr)
{
}

void GameFrame::Script::ActListLink::CreateList()
{
	auto h = new LinkNode;
	h->data = NULL;
	h->nextNode = h;
	head = h;
	tail = head;
}

void GameFrame::Script::ActListLink::CreateList(Activity* headnode)
{
	auto h = new LinkNode;
	h->data = headnode;
	h->nextNode = NULL;
	head = h;
	tail = head;
}

void GameFrame::Script::ActListLink::Emplace_back(Activity* node)
{
	auto n = new LinkNode;
	n->data = node;
	n->nextNode = NULL;
	tail->nextNode = n;
	tail = n;
}

void GameFrame::Script::ActListLink::DestroyList()
{
	LinkNode* p;
	LinkNode* ptr;
	p = head;
	while (p != NULL)
	{
		ptr = p;
		p = p->nextNode;
		delete[]ptr;
	}
}

