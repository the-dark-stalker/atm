
#ifndef CLOGGER_H
#define CLOGGER_H
#include "Base.h"

#include <string>
#include <iostream>

class LoggerImpl;
  
class Logger
{
  public:    
    Logger( LoggerImpl* p );
    virtual ~Logger( );
    virtual void log( std::string & str ) = 0;
  protected:
    LoggerImpl * pimpl;
};
  
class ConsoleLogger : public Logger
{
  public:    
    ConsoleLogger();
    void log( std::string & str );
};
  
class FileLogger : public Logger
{
  public:    
    FileLogger( std::string & file_name );
    void log( std::string & str );
  private:
    std::string file;
};
  
class SocketLogger : public Logger
{
  public:    
    SocketLogger( std::string & remote_host, int remote_port );
    void log( std::string & str );
  private:
    std::string host;
    int    port;
};

class LoggerImpl
{
  public:    
    virtual ~LoggerImpl( ) {}
    virtual void console_log( std::string & str ) = 0;
    virtual void file_log( 
                    std::string & file, std::string & str ) = 0;
    virtual void socket_log( 
           std::string & host, int port, std::string & str ) = 0;
};

class ST_LoggerImpl : public LoggerImpl
{
  public:
    void console_log( std::string & str );
    void file_log   ( std::string & file, std::string & str );
    void socket_log ( 
            std::string & host, int port, std::string & str );
};
  
class MT_LoggerImpl : public LoggerImpl
{
  public:
    void console_log( std::string & str );
    void file_log   ( std::string & file, std::string & str );
    void socket_log ( 
            std::string & host, int port, std::string & str );
};

#endif // CLOGGER_H
