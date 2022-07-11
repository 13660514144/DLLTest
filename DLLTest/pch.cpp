// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"
using namespace std;
// 当使用预编译的头时，需要使用此源文件，编译才能成功。
char* SayHello()
{
	int flg = 0;
	std::string str = "{\"code\":200,\"message\":\"hello c++ dll\",\"data\":[]}";
	char* p = (char*)str.data();
	try
	{
		//std::string str = "{\"code\":200,\"message\":\"hello c++ dll\",\"data\":[]}";		
		//const char* p=str.data() ;
		//strcpy_s(f, strlen(p)+1, p);
	}

	catch (int e)
	{
		flg = 1;
	}
	return p;
}
int readnet(char* str)
{
	int flg = 0;
	try
	{
	    char* p = str;
		strcpy_s(str, strlen(p) + 1, p);
	}
	catch (int e)
	{
		flg = 1;
	}
	return flg;
}
int  GetFileName(char* file)
{
	// 栈上定义
	// char * result =new char[10];

	// TODO:获取文件名

	// 获取文件名(堆上)
	int flg = 0;
	try
	{
		char result[10] = { 0 };
		result[0] = 'm';
		result[1] = 'e';
		result[2] = 'l';
		result[3] = 'p';
		result[4] = 'h';
		result[5] = 'i';
		result[6] = '.';
		result[7] = 'c';
		result[8] = '\0';
		result[9] = '\0';

		// 数据移植，填充出参
		strcpy_s(file, strlen(result) + 1, result);
	}
	catch (int e)
	{
		flg = 1;
	}
	return flg;
}
