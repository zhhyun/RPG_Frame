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

			void CreateList();									//��������������ͷ���
			void CreateList(Activity* headnode);				//������������ͷ��� 
			void Emplace_back(Activity* node);					//���뵥������ 
			void DelNode(Activity* node);						//ɾ���������� 
			void DestroyList();									//���ٵ����� 
			friend class Script;
		private:
			LinkNode* head;
			LinkNode* tail;
		};

		void update();
		void AddActivity(Activity* act); //���ز�����Ա�;籾;
		std::function<bool()> mScriptCondition;
		ActorObject* FindActor(std::string actorName);
		ScriptState GetScriptState() { return mScriptState; };
		void SetScriptState(ScriptState state) { mScriptState = state; };
		ActListLink* EventStack;//�¼���
		std::vector<ActorObject*> Actors;//������Ա

	private:
		ScriptState mScriptState;
		LinkNode* RuningAct;//���ڽ��е��ж�
	};
}