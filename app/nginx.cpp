#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include "ngx_c_conf.h"
#include "ngx_commonFunc.h"
using namespace std;

//声明几个全局的参数变量
//环境变量内存大小
int ngx_environ_len = 0;
char* ngx_environ_place = NULL;
char** ngx_argv;

//配置文件是第一个要解决的问题
//文本文件，除了注释之外不用中文
//以#号为注释行
int main(int argc , char *const* argv)
{
	//初始化几个参数
	ngx_argv = (char**)argv;

	printf("nginx_william 正在启动\n");
	CConfig* my_config = CConfig::getInstance();


	if (my_config->Load("nginx.conf") == false)
	{
		printf("配置文件读取失败，退出\n");
		exit(1);
	}
	printf("加载完毕\n");


	for (int i = 0; environ[i]; i++)
	{
		printf("evriron[%d]地址=%x    ", i, (unsigned int)((unsigned long)environ[i]));
		printf("evriron[%d]内容=%s\n", i, environ[i]);
	}
	printf("开始拷贝环境变量\n");
	if (!ngx_copy_environ())
	{
		printf("环境变量拷贝失败\n");
		exit(1);
	}
	printf("拷贝环境变量成功\n");
	for (int i = 0; environ[i]; i++)
	{
		printf("evriron[%d]地址=%x    ", i, (unsigned int)((unsigned long)environ[i]));
		printf("evriron[%d]内容=%s\n", i, environ[i]);
	}

	for (int i = 0; i < argc; ++i)
	{
		printf("argv[%d]地址=%x    ", i, (unsigned int)((unsigned long)argv[i]));
		printf("argv[%d]内容=%s\n", i, argv[i]);
	}
	printf("开始设置线程名称\n");
	if (!ngx_set_title("nginx_master process"))
	{
		printf("重新设置主线程名称失败\n");
	}
	printf("线程名称设置成功\n");
	for (int i = 0; i < argc; ++i)
	{
		printf("argv[%d]地址=%x    ", i, (unsigned int)((unsigned long)argv[i]));
		printf("argv[%d]内容=%s\n", i, argv[i]);
	}


	for (;;)
	{
		sleep(1);
		printf("睡眠一秒\n");
	}

	return 0;
}
