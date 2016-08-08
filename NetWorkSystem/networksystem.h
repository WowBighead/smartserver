#ifndef _NETWORKSYSTEM_H_
#define _NETWORKSYSTEM_H_

#include "../structtype.h"
#include "../singletonclass.h"
#include "tcphandler.h"
#include "networker.h"

#include <map>
using namespace std;
//����ʹ��libevent��ͨѶ��libevent�ײ�epoll����¼�����Ϊ4096���ɸ��������Լ���������
//libevent�ײ�selectû����������¼�����epoll��select���ж�Ӧ�������߼�
class NetWorkSystem : public Singleton<NetWorkSystem>
{
public:
	NetWorkSystem();
	~NetWorkSystem();
	bool initial();
	static  void tcpread_cb(struct bufferevent *bev, void *ctx);
	static  void tcpwrite_cb(struct bufferevent *bev, void *ctx);
	static  void tcperror_cb(struct bufferevent *bev, short what, void *ctx);
	static  void listener_read_cb(evutil_socket_t fd, short what, void *p);
	void run();
	void release();

private:
	void addConnection(evutil_socket_t fd, bufferevent * bev);
	void eraseConnection(  bufferevent * bev);
	void dealReadEvent(struct bufferevent *bev, void *ctx);
	event_base * m_pEvent_base ;
	evutil_socket_t  m_nListenfd ;
	event* m_pListenevent;
	std::map<evutil_socket_t, TcpHandler *> m_mapTcpHandlers;
	std::map<UInt64, TcpHandler *> m_mapConHandlers;
	UInt64 m_nConnId;
	NetWorker *  m_pNetWorkers[2];
};


#endif _NETWORKSYSTEM_H_