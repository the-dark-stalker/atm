#include "Logger.h"

// Logger::Logger() { }

// Logger::~Logger() { }

Logger::Logger( LoggerImpl* p ) : pimpl(p) 
{ }
  
Logger::~Logger( ) 
{ 
    delete pimpl; 
}
  
ConsoleLogger::ConsoleLogger() : Logger( 
#ifdef MT
        new MT_LoggerImpl()
#else
        new ST_LoggerImpl()
#endif
    ) 
{ }
  
void ConsoleLogger::log( std::string & str ) 
{
    pimpl->console_log( str);
}
  
FileLogger::FileLogger( std::string & file_name ) : Logger(
#ifdef MT
  new MT_LoggerImpl()
#else
  new ST_LoggerImpl()
#endif
    ), file(file_name) 
{ }
       
void FileLogger::log( std::string & str ) 
{
    pimpl->file_log( file, str);
}
  
SocketLogger::SocketLogger( std::string & remote_host, 
                            int remote_port ) : Logger( 
#ifdef MT
  new MT_LoggerImpl()
#else
  new ST_LoggerImpl()
#endif
    ), host(remote_host), port(remote_port) 
{ }
  
void SocketLogger::log( std::string & str ) 
{
    pimpl->socket_log( host, port, str);
}
  
void ST_LoggerImpl::console_log( std::string & str ) 
{
  std::cout << "Single-threaded console logger" << std::endl;
}
     
void ST_LoggerImpl::file_log( std::string & file, std::string & str ) 
{
  std::cout << "Single-threaded file logger" << std::endl;
}
  
void ST_LoggerImpl::socket_log( 
                     std::string & host, int port, std::string & str ) 
{
  std::cout << "Single-threaded socket logger" << std::endl;
};
  
void MT_LoggerImpl::console_log( std::string & str ) 
{
  std::cout << "Multithreaded console logger" << std::endl;
}
     
void MT_LoggerImpl::file_log( std::string & file, std::string & str ) 
{
  std::cout << "Multithreaded file logger" << std::endl;
}
     
void MT_LoggerImpl::socket_log( 
                    std::string & host, int port, std::string & str ) 
{
  std::cout << "Multithreaded socket logger" << std::endl;
}
  
