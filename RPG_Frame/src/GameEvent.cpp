//#include "GameEvent.h"
//
//
//GameFrame::GameEvent::GameEvent(std::string id):
//	eventID(id)
//{
//}
//
//GameFrame::GameEvent::GameEvent():
//	eventID("default"),
//	discription("default event")
//{
//}
//
//
//GameFrame::EventManager::EventManager(EventThread* eventThread):
//	mEventThread(eventThread)
//{
//}
//
//GameFrame::EventThread::EventThread(class Game* game):
//	mGame(game)
//{
//	eventManager = new EventManager(this);
//	/*mtx = new std::mutex();
//	eventThread = new std::thread(std::bind(&EventManager::EventProcessingThread, eventManager, std::ref(*mtx)));*/
//}
//
//GameFrame::EventThread::~EventThread()
//{
//	eventThread->join(); // Make sure to wait for the thread to finish
//	delete eventThread;
//}
