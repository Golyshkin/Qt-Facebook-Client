///////////////////////////////////////////////////////////
//  DialogManager.cpp
//  Implementation of the Class DialogManager
//  Created on:      26-Apr-2011 9:24:48 AM
//  Original author: Golyshkin A.
///////////////////////////////////////////////////////////

#include <DialogManager.h>
#include <FacebookDialog.h>
#include <QApplication>
#include <DialogEvent.h>

#include <DialogLogin.h>
#include <DialogMainMenu.h>
#include <DialogMyFriends.h>
#include <DialogMyFriendsDetails.h>

#include <FacebookNetwokManager.h>

static const DIALOGS_MAP_T DIALOGS_STARTUP_MAP[] = 
{
  { DIALOG_LOGIN,             DialogLogin::Instance              },
  { DIALOG_MAINMENU,          DialogMainMenu::Instance           },
  { DIALOG_MYFRIENDS,         DialogMyFriends::Instance          },
  { DIALOG_MYFRIENDS_DETAILS, DialogMyFriendsDetails::Instance   },  
  { DIALOG_UNKNOWN,           NULL                               }
};

DialogManager::~DialogManager()
{
   if ( m_pNetworkManager )
   {
      delete m_pNetworkManager;
   }

   if ( m_pDialogPostEvent )
   {
      delete m_pDialogPostEvent;
   }

   if ( m_pDialogPostBroadcastEvent )
   {
      delete m_pDialogPostBroadcastEvent;
   }
}

DialogManager::DialogManager( DIALOGS_ID_T aStartDialog )
: m_PostEventTimerId( 0 ), m_PostBroadcastEventTimerId( 0 ), m_pDialogPostEvent( NULL ), m_pDialogPostBroadcastEvent( NULL ),
  m_DialogPostEventTarget( DIALOG_UNKNOWN ), m_WindowOpasityEndLevel( DIALOG_OPASITY / 100 ), m_WindowOpasityInterval( 0.01 )
{
   m_pNetworkManager = new FacebookNetwokManager( &m_Logger );

   PushDialog( aStartDialog );
}

void
DialogManager::InitializeDialog( FacebookDialog *pDialog )
{
   pDialog->SetDialogManager( this );
   pDialog->SetUI();

   if ( pDialog->Id() != DIALOG_LOGIN )
   {
      // Login Dialog has splash screen and it should directly call show when all data will be initialized
      pDialog->show();
      DialogEvent event( DialogEvent::DIALOG_CMD_DAILOG_STARTED );
      pDialog->HandleUserEvent( &event );
   }

   m_OpasityShowDialogTimerId = startTimer( OPASITY_TIMER_DURATION );
}

bool
DialogManager::PushDialog( DIALOGS_ID_T aDialog, DialogEvent *pStartCmd )
{
   unsigned int index = 0;

   while( DIALOGS_STARTUP_MAP[ index ].cb != NULL )
   {
      if ( DIALOGS_STARTUP_MAP[ index ].id == aDialog )
      {
         FacebookDialog *pDialog = DIALOGS_STARTUP_MAP[ index ].cb( pStartCmd );

         if ( !m_dialogs.isEmpty() )
         {
            m_dialogs.top()->hide();
         }

         InitializeDialog( pDialog );
         m_dialogs.push( pDialog );

         return true;
      }

      ++index;
   }

   return false;
}

bool
DialogManager::PopDialog()
{
   m_OpasityCloseDialogTimerId = startTimer( OPASITY_TIMER_DURATION );

   return true;
}

bool
DialogManager::ShowMainMenu()
{
   // This functon is closing all dialogs above aDialog and displaying aDialog
   m_OpasityCloseDialogsTillMainMenuTimerId = startTimer( OPASITY_TIMER_DURATION );

   return true;
}

bool
DialogManager::ReplaceDialog( DIALOGS_ID_T aDialog, DialogEvent *pStartCmd )
{
   if ( !m_dialogs.isEmpty() )
   {
      m_dialogs.pop()->close();

      return PushDialog( aDialog, pStartCmd );
   }

   return false;
}

bool
DialogManager::SendEvent( const DialogEvent& aEvent, DIALOGS_ID_T aTarget )
{
   QStack< FacebookDialog *>::const_iterator iterator = m_dialogs.constBegin();

   while ( iterator != m_dialogs.constEnd() )
   {
      if ( (*iterator)->Id() == aTarget )
      {
         (*iterator)->HandleUserEvent( &aEvent );

         return true;
      }

      ++iterator;
   }

   return false;
}

bool
DialogManager::SendEventBroadcast( const DialogEvent& aEvent )
{
   bool result = false;
   QStack< FacebookDialog *>::const_iterator iterator = m_dialogs.constBegin();

   while ( iterator != m_dialogs.constEnd() )
   {
      result = true;

      (*iterator)->HandleUserEvent( &aEvent );

      ++iterator;
   }

   return result;
}

bool
DialogManager::PostEvent( DialogEvent *pEvent, DIALOGS_ID_T aTarget )
{
   // Post engine shouldn't be busy otherwise return false
   if ( !m_PostEventTimerId )
   {
      m_PostEventTimerId = startTimer( 0 );
      m_pDialogPostEvent = new DialogEvent( *pEvent );
      m_DialogPostEventTarget = aTarget;
      delete pEvent;

      return true;
   }

   return false;
}

bool
DialogManager::PostEventBroadcast( DialogEvent *pEvent )
{
   // Post engine shouldn't be busy otherwise return false
   if ( !m_PostBroadcastEventTimerId )
   {
      m_PostBroadcastEventTimerId = startTimer( 0 );
      m_pDialogPostBroadcastEvent = new DialogEvent( *pEvent );

      delete pEvent;

      return true;
   }

   return false;
}

void
DialogManager::timerEvent( QTimerEvent *pTimerEvent )
{
   if ( pTimerEvent->timerId() == m_PostEventTimerId )
   {
      killTimer( m_PostEventTimerId );
      m_PostEventTimerId = 0;

      QStack< FacebookDialog *>::const_iterator iterator = m_dialogs.constBegin();

      while ( iterator != m_dialogs.constEnd() )
      {
        if ( (*iterator)->Id() == m_DialogPostEventTarget )
        {
           (*iterator)->HandleUserEvent( m_pDialogPostEvent );
           break;
        }

         ++iterator;
      }

      delete m_pDialogPostEvent;
      m_pDialogPostEvent = NULL;

      m_DialogPostEventTarget = DIALOG_UNKNOWN;
   }
   else if ( pTimerEvent->timerId() == m_PostBroadcastEventTimerId )
   {
      killTimer( m_PostBroadcastEventTimerId );
      m_PostBroadcastEventTimerId = 0;
      QStack< FacebookDialog *>::const_iterator iterator = m_dialogs.constBegin();

      while ( iterator != m_dialogs.constEnd() )
      {
         (*iterator)->HandleUserEvent( m_pDialogPostBroadcastEvent );

         ++iterator;
      }

      delete m_pDialogPostBroadcastEvent;
      m_pDialogPostBroadcastEvent = NULL;
   }
   else if ( pTimerEvent->timerId() == m_OpasityCloseDialogTimerId )
   {
      if ( m_dialogs.top()->windowOpacity() > m_WindowOpasityEndLevel )
      {
         m_dialogs.top()->setWindowOpacity( m_dialogs.top()->windowOpacity() - m_WindowOpasityInterval );
      }
      else
      {
         killTimer( m_OpasityCloseDialogTimerId );

         m_dialogs.pop()->close();

         if ( !m_dialogs.isEmpty() )
         {
            m_dialogs.top()->show();
         }
      }
   }
   else if ( pTimerEvent->timerId() == m_OpasityCloseDialogsTillMainMenuTimerId )
   {
      if ( m_dialogs.top()->windowOpacity() > m_WindowOpasityEndLevel )
      {
         m_dialogs.top()->setWindowOpacity( m_dialogs.top()->windowOpacity() - m_WindowOpasityInterval );
      }
      else
      {
         killTimer( m_OpasityCloseDialogsTillMainMenuTimerId );

         while ( !m_dialogs.isEmpty() )
         {
            if ( m_dialogs.top()->Id() != DIALOG_MAINMENU )
            {
               m_dialogs.pop()->close();
            }
            else
            {
               break;
            }
         }

         if ( !m_dialogs.isEmpty() )
         {
            FacebookDialog * pDiaog = m_dialogs.top();
            m_dialogs.top()->show();
         }
      }
   }
   else if ( pTimerEvent->timerId() == m_OpasityShowDialogTimerId )
   {
      if ( m_dialogs.top()->windowOpacity() < 0.99 )
      {
         m_dialogs.top()->setWindowOpacity( m_dialogs.top()->windowOpacity() + m_WindowOpasityInterval );
      }
      else
      {
         killTimer( m_OpasityShowDialogTimerId );
      }
   }
}
