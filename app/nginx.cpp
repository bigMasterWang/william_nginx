#include <stdio.h>
#include <stdlib.h>
#include "ngx_c_conf.h"


//配置文件是第一个要解决的问题
//文本文件，除了注释之外不用中文
//以#号为注释行
int main()
{
	printf("nginx_william 正在启动\n");
	CConfig* my_config = CConfig::getInstance();
	if (my_config->Load("nginx.conf") == false)
	{
		printf("配置文件读取失败，退出\n");
		exit(1);
	}
	printf("加载完毕\n");
	const char* dbInfo = my_config->getString("dbInfo");
	//int lintenPort = my_config->getIntDefault("listenPort", 0);
	if (dbInfo != NULL)
		printf("dbinfo = %s\n", dbInfo);
	//printf("lintenPort = d%", lintenPort);
	return 0;
}
