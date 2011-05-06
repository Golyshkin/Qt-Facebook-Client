///////////////////////////////////////////////////////////
//  DialogEvent.cpp
//  Implementation of the Class DialogEvent
//  Created on:      26-Apr-2011 9:24:47 AM
//  Original author: Golyshkin A.
///////////////////////////////////////////////////////////

#include <DialogEvent.h>

DialogEvent::DialogEvent( DIALOG_CMD_T cmd, void *pData, int aDataSize )
: QEvent( QEvent::User ), m_pData( pData ), m_DataSize( aDataSize ), m_Cmd( cmd )
{

}

DialogEvent::DialogEvent( DialogEvent& aDialogEvent )
: QEvent( QEvent::User ), m_DataSize( aDialogEvent.m_DataSize ), m_Cmd( aDialogEvent.m_Cmd )
{
   if ( aDialogEvent.Data() != NULL )
   {
      m_pData = new char[ m_DataSize ];
      memcpy( m_pData, aDialogEvent.m_pData, m_DataSize );
   }
}

DialogEvent::~DialogEvent()
{
   if ( m_pData && m_DataSize )
   {
      delete m_pData;
   }
}
