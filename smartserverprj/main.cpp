// libeventtest.cpp : Defines the entry point for the console application.
//

// LibeventTest.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include "stdafx.h"
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

	NetWorkSystem::getSingleton().run();

	NetWorkSystem::getSingleton().release();
	
	getchar();

    return 0;
}

