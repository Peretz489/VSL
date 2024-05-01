#include "logger.h"
#include <cassert>

using namespace logger;

int main()
{

{
    std::cout << "\tSingleton check: only one instance of logger is allowed" << std::endl;
    std::cout << "\t___________________" << std::endl;
    std::cout << "\t Trace level enabled, color output of all events must be shown" << std::endl;
    std::cout << "\t___________________" << std::endl;
    Logger *log_tr = Logger::Init(LogLevel::TRACE_LEVEL, LOG_TO_CONSOLE);
    log_tr->Trace("trace event");
    log_tr->Debug("debug event");
    log_tr->Info("info event");
    log_tr->Error("error event");
    log_tr->Fatal("fatal event");
    std::cout << "\t___________________" << std::endl;
    std::cout << "\t Attempt to create another instance with Fatal level,"<<std::endl;
    std::cout<< "\t Must be no changes in output" << std::endl;
    std::cout << "\t___________________" << std::endl;
    Logger *log_ft = Logger::Init(LogLevel::FATAL_LEVEL, LOG_TO_CONSOLE);
    log_ft->Trace("trace event");
    log_ft->Debug("debug event");
    log_ft->Info("info event");
    log_ft->Error("error event");
    log_ft->Fatal("fatal event");
    assert(log_tr==log_ft);
}

}