//#ifndef __GameEvent__
//#define __GameEvent__
//#include	<queue>
//#include	<mutex>
//#include	<functional>
//#include	<unordered_map>
//
//namespace GameFrame {
//	class GameEvent;
//	class EventManager;
//	class EventThread;
//
//	using CallbackFunction = std::function<void()>;
//
//	class GameEvent {
//	public:
//		//�¼���ô����������������������ܷ�װ����
//		//�¼��������͡�id�������Լ��ص��������¼��Ĵ����������������������˲���Ҫд��������
//		GameEvent(std::string id);
//		GameEvent();
//		~GameEvent(){};
//		 
//		void ResignCallback(CallbackFunction callBack) {
//			callback = callBack;
//		}
//		void CallbackOnEvent(){ callback(); };
//
//		friend class EventManager;
//	private:
//		std::string			eventID;
//		std::string			discription;
//		CallbackFunction	callback;
//	};
//
//	class EventManager {
//	public:
//		EventManager(EventThread* eventThread);
//		~EventManager() {};
//
//		//�����¼������������¼�ע�ᵽ���У����¼������ߵ���
//		void RegisterEvent(GameEvent* event) {
//			eventQueue.push(event);
//		}
//
//		//�������û����ĵ��¼�id���뵽���ı�,�ɶ����ߵ���
//		void Subscribe(std::string id, std::function<void()> callback) {
//			subscribers[id].push_back(callback);
//		}
//
//		//ִ���¼����¼�ϵͳ�Զ�����
//		void Publish(GameEvent& event) {
//			if (subscribers.find(event.eventID) != subscribers.end()) {
//				for (auto& callback : subscribers[event.eventID]) {
//					callback(/*event*/);
//				}
//			}
//		}
//
//		friend class EventThread;
//
//	private:
//		std::queue<GameEvent*> eventQueue;
//		//���ı�
//		std::unordered_map<std::string, std::vector<std::function<void()>>> subscribers;
//		EventThread* mEventThread;
//
//		void EventProcessingThread(std::mutex& mtx) {
//			while (true) {
//				if (!eventQueue.empty()) {
//					mtx.lock();
//					GameEvent* event = eventQueue.front();
//					eventQueue.pop();
//					mtx.unlock();
//					// �����¼��������¼�����ִ����Ӧ����
//					Publish(*event);
//				}
//			}
//		}
//	};
//	
//
//
//	class EventThread {
//	public:
//		EventThread(class Game* game);
//		~EventThread();
//
//		EventManager* GetManager() { return eventManager; };
//
//	private:
//		EventManager*			eventManager;
//		std::mutex*				mtx;
//		std::thread*			eventThread;
//		class Game*				mGame;
//	};
//}
//#endif