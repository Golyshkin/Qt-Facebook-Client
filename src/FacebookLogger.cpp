///////////////////////////////////////////////////////////
//  FacebookLogger.cpp
//  Implementation of the Class FacebookLogger
//  Created on:      26-Apr-2011 2:45:02 PM
//  Original author: Golyshkin A.
///////////////////////////////////////////////////////////

#include <FacebookLogger.h>
#include <QDateTime>
#include <QTextStream>
#include <QtDebug>

FacebookLogger::FacebookLogger( LOG_TYPE_T aLogType ) : m_LogFile( "Facebook.log" ), m_File( m_LogFile )
{
   m_LogType = aLogType;

   if ( m_LogType == LOG_FILE )
   {
      if ( QFile::exists( m_LogFile ) == true )
      {
         QFile::remove( m_LogFile );
      }

      m_File.open( QIODevice::WriteOnly | QIODevice::Append );
   }
}

FacebookLogger::~FacebookLogger()
{
   if ( m_File.isOpen() )
   {
      m_File.close();
   }
}

void
FacebookLogger::Log( const QString& aMessage, LOG_PRIORITY aPriority )
{
   if ( m_LogType == LOG_CONSOLE )
   {
      LogToConsole( aMessage, aPriority );
   }
   else
   {
      LogToFile( aMessage, aPriority );
   }
}

void
FacebookLogger::LogToFile( const QString& aMessage, LOG_PRIORITY aPriority )
{
   QTextStream stream( &m_File );

   stream.setCodec( "UTF-8" );

   PrepareLog( aPriority );

   stream << m_LogText.append( aMessage ) << endl;
}

void
FacebookLogger::LogToConsole( const QString& aMessage, LOG_PRIORITY aPriority )
{
   PrepareLog( aPriority );

   switch ( aPriority )
   {
      case PRIORITY_LOW:
      case PRIORITY_MEDIUM:
         qDebug() << m_LogText.append( aMessage );
         break;
      case PRIORITY_HI:
         qCritical() << m_LogText.append( aMessage );
         break;
      case PRIORITY_CRITICAL:
         qFatal( m_LogText.append( aMessage ).toAscii() );
         break;
   }
}

void
FacebookLogger::PrepareLog( LOG_PRIORITY aPriority )
{
   m_LogText.clear();

   QDateTime dateTime = QDateTime::currentDateTime();

   switch ( aPriority )
   {
      case PRIORITY_LOW:
         m_LogText.append( "Low: " );
         break;
      case PRIORITY_MEDIUM:
         m_LogText.append( "Med: " );
         break;
      case PRIORITY_HI:
         m_LogText.append( "Hi:  " );
         break;
      case PRIORITY_CRITICAL:
         m_LogText.append( "Crt: " );
         break;
   }

   m_LogText.append( dateTime.toString( "hh:mm:ss.zzz" ) + ":: " );
}
