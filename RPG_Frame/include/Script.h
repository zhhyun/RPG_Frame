#include	<string>
#include	<functional>
#include	<vector>
namespace GameFrame {
	class ActorObject;
	class Script {
	public:
		enum class ScriptState {
			Running,
			Fin,
			Hide
		};
		class  Activity {
		public:
			Activity():
				state(ScriptState::Hide)
			{};
			~Activity(){};

			void InitAct(std::function<void()> ScriptContent) { mAct = ScriptContent; };
			std::function<void()> mAct;
			ScriptState state;
		};
		typedef struct LinkNode {
			Activity* data;
			LinkNode* nextNode;
		}LinkNode;
		Script();
		~Script() {};

		class ActListLink
		{
		public:
			ActListLink();	
			~ActListLink(){};

			void CreateList();									//创建单链表，不带头结点
			void CreateList(Activity* headnode);				//创建单链表，带头结点 
			void Emplace_back(Activity* node);					//插入单链表结点 
			void DelNode(Activity* node);						//删除单链表结点 
			void DestroyList();									//销毁单链表 
			friend class Script;
		private:
			LinkNode* head;
			LinkNode* tail;
		};

		void update();
		void AddActivity(Activity* act); //加载参演人员和剧本;
		std::function<bool()> mScriptCondition;
		ActorObject* FindActor(std::string actorName);
		ScriptState GetScriptState() { return mScriptState; };
		void SetScriptState(ScriptState state) { mScriptState = state; };
		ActListLink* EventStack;//事件链
		std::vector<ActorObject*> Actors;//参演人员

	private:
		ScriptState mScriptState;
		LinkNode* RuningAct;//正在进行的行动
	};
}