#pragma once
#include <fstream>
#include <string>
#include <mutex>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#define TERMCOLOR_TARGET_WINDOWS
#endif

namespace logger
{

#define LOG_TO_FILE 0b01
#define LOG_TO_CONSOLE 0b10

    enum class LogLevel
    {
        TRACE_LEVEL,
        DEBUG_LEVEL,
        INFO_LEVEL,
        ERROR_LEVEL,
        FATAL_LEVEL
    };

    class Logger
    {
    public:
        static Logger *Init(LogLevel level, int log_target, const std::string &filename="log.txt");
        void Trace(const std::string &event);
        void Debug(const std::string &event);
        void Info(const std::string &event);
        void Error(const std::string &event);
        void Fatal(const std::string &event);

        std::string GetTime();

    private:
        Logger(LogLevel level, int log_target, const std::string &filename);
        ~Logger() = default;
        Logger(Logger &other) = delete;
        Logger &operator=(Logger &other) = delete;

        Logger &SetLogLevel(LogLevel level);

        bool WriteToLog(const std::string &event, LogLevel level = LogLevel::TRACE_LEVEL);

        std::mutex mu_;
        std::string log_filename_;
        std::ostream &out_ = std::cout;
        LogLevel level_;
        int target_;
    };

}