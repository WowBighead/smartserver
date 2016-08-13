// libeventtest.cpp : Defines the entry point for the console application.
//

// LibeventTest.cpp : 定义控制台应用程序的入口点。
//

#ifdef _WIN32
#include "stdafx.h"
#endif

#include"../NetWorkSystem/networksystem.h"
#include <fstream>
#include "../ProtoBuf/smart.msg.pb.h"
#include "../basethread.h"
#include "../NetWorkSystem/networker.h"

#pragma comment(lib, "libprotobuf.lib")  
#pragma comment(lib, "libprotoc.lib")

int main(int argc, char **argv)
{
	bool initialRes = NetWorkSystem::getSingleton().initial();

	cout <<"111111111"<<endl;
	
	if(!initialRes)
	{
		return 0;
	}

	NetWorkSystem::getSingleton().run();


	cout << "after run!!!" <<endl;
	NetWorkSystem::getSingleton().release();
	
	getchar();
	cout << "after get char!!!"<<endl;
    return 0;
}

