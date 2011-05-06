///////////////////////////////////////////////////////////
//  FacebookLogger.h
//  Implementation of the Class FacebookLogger
//  Created on:      26-Apr-2011 2:45:02 PM
//  Original author: Golyshkin A.
//
//  FacebookLogger fbLogger( FacebookLogger::LOG_CONSOLE );
//
//  fbLogger.Log( "Test Log" );
//  fbLogger.Log( "Test Log Low", FacebookLogger::PRIORITY_LOW );
//  fbLogger.Log( "Test Log Medium", FacebookLogger::PRIORITY_MEDIUM );
//  fbLogger.Log( "Test Log Hi", FacebookLogger::PRIORITY_HI );
//  fbLogger.Log( "Test Log Crt", FacebookLogger::PRIORITY_CRITICAL );
///////////////////////////////////////////////////////////

#if !defined(EA_9121890D_624A_47a7_8412_51BE5B74495F__INCLUDED_)
#define EA_9121890D_624A_47a7_8412_51BE5B74495F__INCLUDED_

#include <QString>
#include <QFile>

class FacebookLogger
{
public:

   enum LOG_TYPE_T
   {
      LOG_CONSOLE,
      LOG_FILE
   };

   enum LOG_PRIORITY
   {
      PRIORITY_LOW,
      PRIORITY_MEDIUM,
      PRIORITY_HI,
      PRIORITY_CRITICAL
   };

   FacebookLogger( LOG_TYPE_T aLogType = LOG_CONSOLE );

   virtual ~FacebookLogger();

   void Log( const QString& aMessage, LOG_PRIORITY aPriority = PRIORITY_LOW );

   void LogToFile( const QString& aMessage, LOG_PRIORITY aPriority );

   void LogToConsole( const QString& aMessage, LOG_PRIORITY aPriority );

   void SetLogType( LOG_TYPE_T aLogType ) { m_LogType = aLogType; };

protected:

   FacebookLogger( const FacebookLogger & theFacebookLogger ) {};

private:

   void PrepareLog( LOG_PRIORITY aPriority );

	LOG_TYPE_T m_LogType;

   QString m_LogFile;

   QString m_LogText;

   QFile m_File;
};

#endif // !defined(EA_9121890D_624A_47a7_8412_51BE5B74495F__INCLUDED_)
