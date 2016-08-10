#include "CLock.h"

//�ڹ��캯���ﴴ����
Mutex::Mutex()
{
	#if defined _WIN32
		m_hMutex = ::CreateMutex(NULL, FALSE, NULL);
	#endif

#ifdef __linux__
		int  r = pthread_mutex_init(&m_hMutex, 0);
		if(r != 0)
		{
			cout <<"Linux Lock init failed!!!"<<endl;
		}
#endif
}

//����������������
Mutex::~ Mutex()
{
	#if defined _WIN32
		::CloseHandle(m_hMutex);
	#endif

#ifdef __linux__
		int r = pthread_mutex_destroy(&m_hMutex);
		if(r != 0)
		{
			cout << "Linux destroy failed!!!"<<endl;
		}

#endif
}

//����������
void Mutex::lock() const
{
	#if defined _WIN32
	  DWORD d = WaitForSingleObject(m_hMutex, INFINITE);
	#endif

	#ifdef __linux__
		int r = pthread_mutex_lock(&m_Mutex);
		if(r != 0)
		{
			cout << "linux lock failed!!!"<<endl;
		}
	#endif

}

//����������
void Mutex::unlock() const
{
	#if defined _WIN32
	  ::ReleaseMutex(m_hMutex);
	#endif

#ifdef __linux__
	  ret = pthread_mutex_unlock(&tMutex);
	  if(ret != 0)
	  {
		  cout << "Linux unlock failed!!!" <<endl;
	  }
#endif
}