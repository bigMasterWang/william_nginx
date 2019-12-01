﻿#ifndef __NGX__C__CONF__H__
#define __NGX__C__CONF__H__

#include <vector>
#include "ngx_global.h"
using namespace std;

/*
这是一个单例类，用来读取配置文件的信息
*/
class CConfig
{
private:
	CConfig();
public:
	~CConfig();
private:
	static CConfig* m_instance;
public:
	//得到单例的方法
	static CConfig* getInstance()
	{
		if (m_instance == NULL)
		{
			if (m_instance == NULL)
			{
				m_instance = new CConfig();
				static CInnerToReleaseConfig releaseClass;
			}
		}
	}
	//释放资源的内部类
	class CInnerToReleaseConfig
	{
	public:
		~CInnerToReleaseConfig()
		{
			if (CConfig::m_instance)
			{
				delete CConfig::m_instance;
				CConfig::m_instance = NULL;
			}
		}
	};

public:
	bool Load(const char* pconfName);
	const char* getString(const char* p_itemname);
	//int getIntDefault(const char* p_itemname, const int def);

public:
	//配置信息存储列表
	vector<SPConf> m_ConfigItemList;
};


#endif
