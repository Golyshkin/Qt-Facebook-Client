///////////////////////////////////////////////////////////
//  DialogManager.h
//  Implementation of the Class DialogManager
//  Created on:      26-Apr-2011 9:24:48 AM
//  Original author: Golyshkin A.
///////////////////////////////////////////////////////////

#if !defined(EA_44956409_37EF_4379_B821_00A821CE5335__INCLUDED_)
#define EA_44956409_37EF_4379_B821_00A821CE5335__INCLUDED_

#include <FacebookLogger.h>
#include <QStack>

class FacebookDialog;
class DialogEvent;
class FacebookNetwokManager;

enum DIALOGS_ID_T
{
    DIALOG_UNKNOWN,
    DIALOG_LOGIN,
    DIALOG_MAINMENU,
    DIALOG_MYFRIENDS,
    DIALOG_MYFRIENDS_DETAILS,
    DIALOG_GROUPS,
    DIALOG_GROUPS_DETAILS,
    DIALOG_NEWS
};

typedef FacebookDialog * ( *DIALOG_CB )( DialogEvent *pStartCmd );

struct DIALOGS_MAP_T
{
	DIALOGS_ID_T id;
	DIALOG_CB cb;
};

class DialogManager : public QObject
{
   Q_OBJECT

   friend class FacebookDialog;

public:

   DialogManager( DIALOGS_ID_T aStartDialog = DIALOG_LOGIN );

	virtual ~DialogManager();

   bool PushDialog( DIALOGS_ID_T aDialog, DialogEvent *pStartCmd = NULL );

   bool PopDialog();

   bool ReplaceDialog( DIALOGS_ID_T aDialog, DialogEvent *pStartCmd = NULL );

   bool SendEvent( const DialogEvent& aEvent, DIALOGS_ID_T aTarget );

   bool SendEventBroadcast( const DialogEvent& aEvent );

   bool PostEvent( DialogEvent *pEvent, DIALOGS_ID_T aTarget );

   bool PostEventBroadcast( DialogEvent *pEvent );

   FacebookNetwokManager * GetNetworkManager() const { return m_pNetworkManager; }

   FacebookLogger & GetLogger() { return m_Logger; }

   enum
   {
      DIALOG_OPASITY = 80
   };

protected:

   virtual void timerEvent ( QTimerEvent *pTimerEvent );

   bool ShowMainMenu();

private:

   enum
   {
      OPASITY_TIMER_DURATION = 10
   };

   typedef int DIALOG_MANAGER_TIMER_ID;

   void InitializeDialog( FacebookDialog *pDialog );

   DialogManager( const DialogManager& theDialogManager);

   QStack< FacebookDialog *> m_dialogs;

   FacebookNetwokManager * m_pNetworkManager;

   FacebookLogger m_Logger;

   DIALOG_MANAGER_TIMER_ID m_PostEventTimerId, m_PostBroadcastEventTimerId;

   DIALOG_MANAGER_TIMER_ID m_OpasityCloseDialogTimerId, m_OpasityShowDialogTimerId;

   DIALOG_MANAGER_TIMER_ID m_OpasityCloseDialogsTillMainMenuTimerId;

   DialogEvent *m_pDialogPostEvent;

   DialogEvent *m_pDialogPostBroadcastEvent;

   DIALOGS_ID_T m_DialogPostEventTarget;

   qreal m_WindowOpasityEndLevel;

   qreal m_WindowOpasityInterval;
};

#endif // !defined(EA_44956409_37EF_4379_B821_00A821CE5335__INCLUDED_)
