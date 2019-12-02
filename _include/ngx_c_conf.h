#ifndef __NGX__C__CONF__H__
#define __NGX__C__CONF__H__

#include <vector>
#include <mutex>
#include "ngx_global.h"



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
	static std::mutex myMutex;

	//得到单例的方法
	static CConfig* getInstance()
	{
		if (m_instance == NULL)
		{
			std::unique_lock<std::mutex>myUniqueLock(CConfig::myMutex);
			if (m_instance == NULL)
			{
				m_instance = new CConfig();
				static CInnerToReleaseConfig releaseClass;
			}
		}
		return m_instance;
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
	int getIntDefault(const char* p_itemname, const int def);

public:
	//配置信息存储列表
	std::vector<SPConf> m_ConfigItemList;
};


#endif
