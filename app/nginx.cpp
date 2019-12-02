#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "ngx_c_conf.h"

using namespace std;

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

	//my_config->m_intItem.push_back(1);
	//for (vector<int>::iterator it = my_config->m_intItem.begin(); it != my_config->m_intItem.end(); ++it)
	//{
	//	printf("%d\n",*it);
	//}

	const char* dbinfo = my_config->getString("dbInfo");
	int lintenport = my_config->getIntDefault("listenPort", 0);
	if (dbinfo != NULL)
		printf("dbinfo = %s\n", dbinfo);
	printf("lintenport = d%", lintenport);
	return 0;
}
