#include <QDateTime>

#include "logger.h"

// Initialization of Logger static members
Logger* Logger::logger_ = 0;
QString Logger::logFileName_ = "";
Logger::LogLevel Logger::minLogLevel_ = Logger::LogLevel::DEBUG;

Logger::Logger(QObject* parent) : QObject( parent )
{

}

Logger::~Logger()
{

}

Logger *Logger::Instance(QObject* parent)
{
    if(!logger_) {
        logger_ = new Logger(parent);
        // TODO: open log file
    }
    return logger_;
}

void Logger::Destroy()
{
    if(logger_) {
        // TODO: close log file
        delete logger_;
    }
}

bool Logger::setLogFileName(QString fileName)
{
    logFileName_ = fileName;
    return true;
}

bool Logger::setMinLogLevel(Logger::LogLevel minLogLevel)
{
    minLogLevel_ = minLogLevel;
    return true;
}

void Logger::logMsg(QString msg, Logger::LogLevel logLevel)
{
    QString logMsg = "[ " + QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss") + " - "
             + getLogLevelString(logLevel) + " ]: " + msg;
    if (logLevel == LogLevel::ERROR) {
        emit newErrorLogMsg(logMsg, msg);
    }
    else {
        emit newLogMsg(logMsg);
    }
    // TODO: log in file
}

QString Logger::getLogLevelString(Logger::LogLevel logLevel)
{
    QString logLevelString = "UNKNOWN";
    switch (logLevel) {
    case LogLevel::DEBUG:
        logLevelString = "DEBUG";
        break;
    case LogLevel::INFO:
        logLevelString = "INFO";
        break;
    case LogLevel::WARNING:
        logLevelString = "WARNING";
        break;
    case LogLevel::ERROR:
        logLevelString = "ERROR";
        break;
    default:
        break;
    }
    return logLevelString;
}
