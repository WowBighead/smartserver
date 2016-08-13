# ifndef _BASELOCK_H_
# define _BASELOCK_H_
#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#include <pthread.h>
#endif

#include <iostream>
using namespace std;
//�������͵����Ļ���
class BaseLock
{
public:
	BaseLock(){}
	virtual ~BaseLock(){}
	virtual void lock()  = 0 ;
	virtual void unlock()  = 0 ;
};

//�������̳л���
class Mutex :public BaseLock
{
public:
	Mutex();
	~Mutex();
	virtual void lock() ;
	virtual void unlock() ;
private:
#if defined _WIN32
	HANDLE m_hMutex;
#endif

#ifdef __linux__
	pthread_mutex_t m_hMutex;
#endif
};


class CLock
{
public:
	CLock(  BaseLock *baseLock):m_cBaseLock(baseLock){
		//���캯����ͨ�����������ü�������(��̬)
		m_cBaseLock->lock();
	}
	~CLock(){
		//���������Ƚ���
		m_cBaseLock->unlock();
	}
private:
	//�����ñ�������Ҫ�ڳ�ʼ���б��ʼ
	//��̬����
	BaseLock* m_cBaseLock;
};







#endif 
