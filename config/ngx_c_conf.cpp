#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include "ngx_c_conf.h"
#include "ngx_stringHelper.h"

CConfig* CConfig::m_instance = NULL;

//构造函数
CConfig::CConfig()
{

}
//析构函数
CConfig::~CConfig()
{
	std::vector<SPConf>::iterator mConfIter;
	for (mConfIter = m_ConfigItemList.begin(); mConfIter != m_ConfigItemList.end(); ++mConfIter)
	{
		delete (*mConfIter);
	}
	m_ConfigItemList.clear();
}
/*	bool Load(const char* ConfigFileName);
	const char* getString(const char* itemName);
	int getIntDefault(const char* itemName, const int def);
*/
bool CConfig::Load(const char* ConfigFileName)
{
	FILE* fp;
	fp = fopen(ConfigFileName, "r");
	if (fp == NULL)
		return false;
	char lineBuf[501];

	while (feof(fp))
	{
		//读取到空行
		if (fgets(lineBuf, 500, fp) == NULL)
			continue;
		//首字节为00
		if (lineBuf[0] == 0)
			continue;
		//处理特殊字符，如#注释
		if (*lineBuf == ';' || *lineBuf == '#' || *lineBuf == ' ' || *lineBuf == '\t' || *lineBuf == '\n')
			continue;

		//处理末尾的换行，空格
		while (strlen(lineBuf) > 0)
		{
			//如果为空格或者回车，长度减一
			if (lineBuf[strlen(lineBuf) - 1] == 32 || lineBuf[strlen(lineBuf) - 1] == 10 || lineBuf[strlen(lineBuf) - 1] == 13)
				lineBuf[strlen(lineBuf) - 1] = 0;
		}

		if (lineBuf[0] = 0)
			continue;

		//先不处理，这个作为配置节点
		if (*lineBuf == '[')
			continue;

		char* ptmp = strchr(lineBuf, '=');
		if (ptmp != NULL)
		{
			SPConf p_confitem = new SConfItem;
			memset(p_confitem, 0, sizeof(SConfItem));
			//将等号之前的给itemName
			strncpy(p_confitem->itemName, lineBuf, (int)(ptmp - lineBuf));
			//将等号之后的赋给itemContent
			strcpy(p_confitem->itemContent, ptmp + 1);
			//去除首末尾的空格
			Rtrim(p_confitem->itemName);
			Ltrim(p_confitem->itemName);
			Rtrim(p_confitem->itemContent);
			Ltrim(p_confitem->itemContent);
			m_ConfigItemList.push_back(p_confitem);

		}
	}

	fclose(fp);
	return true;
}

const char* CConfig::getString(const char* itemName)
{
	std::vector<SPConf>::iterator pos;
	for (pos = m_ConfigItemList.begin(); pos != m_ConfigItemList.end(); ++pos)
	{
		if (strcasecmp((*pos)->itemName, itemName) == 0)
			return (*pos)->itemContent;
	}
}

const int CConfig::getIntDefault(const char* itemName, const int def)
{
	std::vector<SPConf>::iterator pos;
	for (pos = m_ConfigItemList.begin(); pos != m_ConfigItemList.end(); ++pos)
	{
		if (strcasecmp((*pos)->itemName, itemName) == 0)
			return atoi((*pos)->itemContent);
	}
	return def;
}
