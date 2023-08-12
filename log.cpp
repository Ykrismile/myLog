#include "log.h"

namespace myserver {
    Logger::Logger(const std::string& name = "root")
    :m_name(name){

    }

    void Logger::addAppender(LogAppender::ptr appender){
        m_appenders.push_back(appender);

    }

	void Logger::delAppender(LogAppender::ptr appender){
        for(auto it = m_appenders.begin();it != m_appenders.end(); it++){
            if(*it == appender){
                m_appenders.erase(it);
                break;
            }
        }
    }
	
	void Logger::log(LogLevel::Level level,LogEvent::ptr event){
        if(level>=m_level){
            for(auto& i:m_appenders){
                i->log(level,event);
            }
        }
    }

	void Logger::debug(LogEvent::ptr event){
        debug(Loglevel::DEBUG, event);
    }

	void Logger::info(LogEvent::ptr event){
        debug(Loglevel::INFO, event);
    }

	void Logger::warn(LogEvent::ptr event){
        debug(Loglevel::WARN, event);
    }

	void Logger::error(LogEvent::ptr event){
        debug(Loglevel::ERROR, event);
    }

	void Logger::fatal(LogEvent::ptr event){
        debug(Loglevel::FATAL, event);
    }

    FileLogAppender::FileLogAppender(const std::string& filename)
    :m_filename(filename){

    }

    void FileLogAppender::Log(LogLevel::Level,LogEvent::ptr event){

    }

    bool FileLogAppender::reopen(){
        if(m_filestream){
            m_filestream.close();
        }
        m_filestream.open(m_filename);
        return !!m_filestream;
    }

    void StdoutLogAppender::Log(LogLevel::Level,LogEvent::ptr event){
        if(level>=m_level){
            std::cout<< m_formatter.(event);
        }
    }
}