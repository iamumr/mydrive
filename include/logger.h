#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <log4cpp/Category.hh>

#include <string>
using std::string;


class Mylogger
{
public:
	static Mylogger * getInstance();
	static void destroy();

	template <class... Args>
	void error(Args... args)
	{	_cat.error(args...);	}

	void error(const char * msg);

	template <class... Args>
	void info(const char * msg, Args... args)
	{	_cat.info(msg, args...);	}

	void info(const char * msg);

	template <class... Args>
	void warn(const char * msg, Args... args)
	{	_cat.warn(msg, args...);	}

	void warn(const char * msg);

	template <class... Args>
	void debug(const char * msg, Args... args)
	{	_cat.debug(msg, args...);	}

	void debug(const char * msg);
	log4cpp::Category & getCategory(){	return _cat;}

	//void setPriority();

private:
	Mylogger();
	~Mylogger();

private:
	static Mylogger * _pInstance;
	log4cpp::Category & _cat;
};


#define prefix(msg)  string("[").append(__FILE__)\
	.append(":").append(__FUNCTION__)\
    .append(":").append(std::to_string(__LINE__))\
	.append("] ").append(msg).c_str()


#define LogError(msg, ...)  wd::Mylogger::getInstance()->error(prefix(msg), ##__VA_ARGS__)
#define LogInfo(msg, ...)  wd::Mylogger::getInstance()->info(prefix(msg), ##__VA_ARGS__)
#define LogWarn(msg, ...)  wd::Mylogger::getInstance()->warn(prefix(msg), ##__VA_ARGS__)
#define LogDebug(msg, ...)  wd::Mylogger::getInstance()->debug(prefix(msg), ##__VA_ARGS__)

#endif 
