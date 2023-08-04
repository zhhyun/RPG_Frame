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
	if (mScriptState == Script::ScriptState::Fin) {//����籾�Ѿ�����������
		return;
	}
	//if (Actors.empty()) {//���û�в�����Ա������
	//	return;
	//}
	//�籾��������:����1���Ҿ籾δ����
	if (/*mScriptCondition() && */mScriptState == Script::ScriptState::Hide) {
		SetScriptState(Script::ScriptState::Running);//�������㣬�籾��ʼ//����Ӧ�����ⲿ���룬��������һ������
		//���ж����ĵ�һ�������ص�RuningAct
		RuningAct = EventStack->head->nextNode;
	}
	//����籾�Ѿ���ʼ
	if (mScriptState == Script::ScriptState::Running) {
		if (RuningAct->data->state == ScriptState::Hide) {
			//�����ǰ����Ϊ��δ��ʼ�������жϸ���Ϊ�Ƿ���������������л�Ϊ��ʼ,�жϺ���д��act()��
			//����籾Ҫ����ĳ�����ߺ���ܽ����񣬼����߻�ú���ܴ�����������
			RuningAct->data->mAct();	
		}
		else if (RuningAct->data->state == ScriptState::Running) {
			//�����ǰ����Ϊ�������У�������
			RuningAct->data->mAct();
			return;
		}
		else {
			//�����ǰ�ж��Ѿ��������򽫽���ǰ��
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

