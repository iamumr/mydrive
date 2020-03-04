#include "include/logger.h"

#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/RollingFileAppender.hh>

#include <iostream>
using std::cout;
using std::endl;

Mylogger * Mylogger::_pInstance = nullptr;

Mylogger * Mylogger::getInstance()
{
	if(!_pInstance) {
		_pInstance = new Mylogger();
	}
	return _pInstance;
}

void Mylogger::destroy()
{
	if(_pInstance)
		delete _pInstance;
}

Mylogger::Mylogger()
: _cat(log4cpp::Category::getRoot().getInstance("logger"))
{
	using namespace log4cpp;
	PatternLayout * ptn1 = new PatternLayout();
	ptn1->setConversionPattern("%d:%p %c %x: %m%n");
	PatternLayout * ptn2 = new PatternLayout();
	ptn2->setConversionPattern("%d:%p %c %x: %m%n");

	OstreamAppender * os = new OstreamAppender("os", &cout);
	os->setLayout(ptn1);

	RollingFileAppender * rollfile = new RollingFileAppender(
		"rollfile",
		"wd.log",
		10 * 1024 * 1024,
		10);
	rollfile->setLayout(ptn2);

	_cat.addAppender(os);
	_cat.addAppender(rollfile);
	_cat.setPriority(Priority::INFO);
}

Mylogger::~Mylogger()
{
	log4cpp::Category::shutdown();
}


void Mylogger::error(const char * msg)
{
	_cat.error(msg);
}

void Mylogger::info(const char * msg)
{
	_cat.info(msg);
}

void Mylogger::warn(const char * msg)
{
	_cat.warn(msg);
}

void Mylogger::debug(const char * msg)
{
	_cat.debug(msg);
}
