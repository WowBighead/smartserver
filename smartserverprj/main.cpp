// libeventtest.cpp : Defines the entry point for the console application.
//

// LibeventTest.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include "stdafx.h"
#include"../NetWorkSystem/networksystem.h"
int main(int argc, char **argv)
{
	bool initialRes = NetWorkSystem::getSingleton().initial();
	
	NetWorkSystem::getSingleton().run();
	
	getchar();

    return 0;
}

