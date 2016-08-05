# ifndef _BASELOCK_H_
# define _BASELOCK_H_

#include <windows.h>

//�������͵����Ļ���
class BaseLock
{
public:
	BaseLock(){}
	virtual ~BaseLock(){}
	virtual void lock() const = 0 ;
	virtual void unlock() const = 0 ;
};

//�������̳л���
class Mutex :public BaseLock
{
public:
	Mutex();
	~Mutex();
	virtual void lock() const;
	virtual void unlock() const;
private:
#if defined _WIN32
	HANDLE m_hMutex;
#endif
};


class CLock
{
public:
	CLock(const BaseLock & baseLock):m_cBaseLock(baseLock){
		//���캯����ͨ�����������ü�������(��̬)
		m_cBaseLock.lock();
	}
	~CLock(){
		//���������Ƚ���
		m_cBaseLock.unlock();
	}
private:
	//�����ñ�������Ҫ�ڳ�ʼ���б��ʼ
	//��̬����
	const BaseLock& m_cBaseLock;
};







#endif 