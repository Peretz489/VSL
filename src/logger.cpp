#include "logger.h"
#include <iostream>
#include <chrono>
#include <sstream>
#include <ctime>
#include "termcolor.h"
#include <windows.h>
#include <sstream>

namespace logger
{
    Logger::Logger(LogLevel level, int log_target, const std::string &filename)
        : level_(level), target_(log_target), log_filename_(filename)
    {
    }

    Logger *Logger::Init(LogLevel level, int log_target, const std::string &filename)
    {
        static Logger inst(level, log_target, filename); // no changes allowed after init
        return &inst;
    }

    void Logger::Trace(const std::string &event)
    {
        if (level_ <= LogLevel::TRACE_LEVEL)
        {
            WriteToLog(event);
        }
    }
    void Logger::Debug(const std::string &event)
    {
        if (level_ <= LogLevel::DEBUG_LEVEL)
        {
            WriteToLog(event, LogLevel::DEBUG_LEVEL);
        }
    }
    void Logger::Info(const std::string &event)
    {
        if (level_ <= LogLevel::INFO_LEVEL)
        {
            WriteToLog(event, LogLevel::INFO_LEVEL);
        }
    }
    void Logger::Error(const std::string &event)
    {
        if (level_ <= LogLevel::ERROR_LEVEL)
        {
            WriteToLog(event, LogLevel::ERROR_LEVEL);
        }
    }
    void Logger::Fatal(const std::string &event)
    {
        if (level_ <= LogLevel::FATAL_LEVEL)
        {
            WriteToLog(event, LogLevel::FATAL_LEVEL);
        }
    }

    bool Logger::WriteToLog(const std::string &event, LogLevel level)
    {

        if (target_ & LOG_TO_FILE)
        {
            std::string log_level;
            switch (level)
            {
            case LogLevel::TRACE_LEVEL:
            {
                log_level = " Trace: ";
                break;
            }
            case LogLevel::DEBUG_LEVEL:
            {
                log_level = " Debug: ";
                break;
            }
            case LogLevel::INFO_LEVEL:
            {
                log_level = " Info: ";
                break;
            }
            case LogLevel::ERROR_LEVEL:
            {
                log_level = " Error: ";
                break;
            }
            case LogLevel::FATAL_LEVEL:
            {
                log_level = " Fatal: ";
                break;
            }
            }
            std::lock_guard<std::mutex> guard(mu_);
            std::fstream out(log_filename_, std::ios::app);
            out << GetTime() << log_level << event << std::endl;
            out.close();
        }
        
        if (target_ & LOG_TO_CONSOLE)
        {

            switch (level)
            {
            case LogLevel::TRACE_LEVEL:
            {
                out_ << termcolor::bright_magenta;
                break;
            }
            case LogLevel::DEBUG_LEVEL:
            {
                out_ << termcolor::white;
                break;
            }
            case LogLevel::INFO_LEVEL:

            {
                out_ << termcolor::green;
                break;
            }

            case LogLevel::ERROR_LEVEL:
            {
                out_ << termcolor::yellow;
                break;
            }
            case LogLevel::FATAL_LEVEL:
            {
                out_ << termcolor::bright_red;
                break;
            }
            }
            out_ << GetTime() << " " << event << termcolor::reset << std::endl;
        }
        return true;
    }

    std::string Logger::GetTime()
    {
#if defined(_WIN32) || defined(_WIN64)

        SYSTEMTIME st;
        GetLocalTime(&st);
        std::stringstream out_time;
        out_time << st.wYear << " " << st.wMonth << " " << st.wDay << " " << st.wHour << "." << st.wMinute << "." << st.wSecond << ":" << st.wMilliseconds;
        return out_time.str();

#elif defined(__unix__) || defined(__unix)

        using std::chrono::system_clock;
        auto currentTime = std::chrono::system_clock::now();
        char buffer[80];
        auto transformed = currentTime.time_since_epoch().count() / 1000000;
        auto millis = transformed % 1000;
        std::time_t tt;
        tt = system_clock::to_time_t(currentTime);
        auto timeinfo = localtime(&tt);
        strftime(buffer, 80, "%F %H:%M:%S", timeinfo);
        std::stringstream out;
        out << buffer << ".";
        if (millis == 0)
        {
            out << "000";
        }
        else if (millis < 10)
        {
            out << "00" << millis;
        }
        else if (millis < 100)
        {
            out << "0" << millis;
        }
        else
        {
            out << millis;
        };

        return out.str();
#endif
    }

    Logger &Logger::SetLogLevel(LogLevel level)
    {
        level_ = level;
        return *this;
    }

}