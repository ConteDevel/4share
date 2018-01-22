#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>

class Logger : public QObject
{
    Q_OBJECT
public:
    // log levels
    enum LogLevel
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    static Logger* Instance(QObject* parent=0);
    static void Destroy();

    bool setLogFileName(QString fileName);
    bool setMinLogLevel(LogLevel minLogLevel);
    void logMsg(QString msg, LogLevel logLevel = INFO);

signals:
    void newLogMsg(QString msg);

private:
    QString getLogLevelString(LogLevel logLevel);

    Logger(QObject* parent);
    //Logger(Logger const&) = 0;
    //Logger& operator=(Logger const&) = 0;
    ~Logger();

    static LogLevel minLogLevel_;
    static QFile logFile_;
    static QString logFileName_;
    static Logger* logger_;
};

#endif // LOGGER_H
