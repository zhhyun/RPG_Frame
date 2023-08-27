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
//		//事件最好创建即发布，把这两个功能封装起来
//		//事件基本类型、id、名称以及回调函数。事件的触发是由组件主动触发，因此不需要写触发条件
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
//		//发布事件，将发生的事件注册到队列，由事件发布者调用
//		void RegisterEvent(GameEvent* event) {
//			eventQueue.push(event);
//		}
//
//		//将订阅用户订阅的事件id加入到订阅表,由订阅者调用
//		void Subscribe(std::string id, std::function<void()> callback) {
//			subscribers[id].push_back(callback);
//		}
//
//		//执行事件，事件系统自动调用
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
//		//订阅表
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
//					// 处理事件，根据事件类型执行相应操作
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