#ifndef __MYSERVER_LOG_H__
#define __MYSERVER_LOG_H__

#include <string>
#include <stdint.h>
#include <memory>
#include <list>


namespace myserver{


//日志事件
class LogEvent {
public:
	typedef std::shared_ptr<LogEvent> ptr;
	LogEvent();
private:
	const char* m_file = nullptr; //文件名
	int32_t m_line = 0; //行号
	int32_t m_elapse = 0; //程序启动到现在的毫秒数
	int32_t m_threadId = 0; //线程号
	uint32_t m_fiberId = 0; //协程号
	time_t m_time; //时间戳
	std::string m_content;
}

//日志级别
class LogLevel{
public:
	enum Level{
		DEBUG = 1,
		INFO = 2,
		WARN = 3,
		ERROR = 4,
		FATAL = 5
	};
};


//格式器
class LogFormatter{
public:
	typedef std::shared_ptr<LogFormatter> ptr;

	std::string format(LogEvent::ptr event);
private:
}

//日志输出地
class LogAppender{
public:
	typedef std::shared_ptr<LogAppender> ptr;
	virtual ~LogAppender();

	void Log(LogLevel::Level,LogEvent::ptr event);
private:
	LogLevel::level m_level;
};

//日志器	
class Logger {
public:
	typedef std::shared_ptr<Logger> ptr;

	Logger(const std::string& name = "root");
	
	void log(LogLevel::Level level,LogEvent::ptr event);

	void debug(LogEvent::ptr event);
	void info(LogEvent::ptr event);
	void warn(LogEvent::ptr event);
	void error(LogEvent::ptr event);
	void fatal(LogEvent::ptr event);
private:
	std::string m_name;     					//日志名称
	LogLevent::level m_level; 					//日志级别
	std::list<LogAppender::ptr> m_appenders;  //appender集合

	
};

//输出到控制台的appender
class StdoutLogAppender:public LogAppender{

};

//输出到文件的appender
class FileLogAppender:public LogAppender{

};


}

#endif
