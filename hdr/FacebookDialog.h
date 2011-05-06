///////////////////////////////////////////////////////////
//  TelecaFacebookDialog.h
//  Implementation of the Class TelecaFacebookDialog
//  Created on:      26-Apr-2011 9:24:48 AM
//  Original author: Golyshkin A.
///////////////////////////////////////////////////////////

#if !defined(EA_5E763007_65F3_4242_B012_3D99E6A3EE17__INCLUDED_)
#define EA_5E763007_65F3_4242_B012_3D99E6A3EE17__INCLUDED_

#include <QDialog>
#include <DialogManager.h>
#include <QBoxLayout>

class DialogManager;
class DialogEvent;
class QPushButton;
class QFrame;

const int FACEBOOK_DIALOG_HEIGH = 480;
const int FACEBOOK_DIALOG_WIDTH = 640;

class FacebookDialog : public QDialog
{
   Q_OBJECT

public:

   FacebookDialog( DialogEvent *pStartCmd = NULL, QWidget *parent = 0 );

   ~FacebookDialog();

   virtual void SetUI();

   QBoxLayout * const GetMainLayout() { return m_pMainLayout; }

   void SetDialogManager( DialogManager *pDialogManager ) { m_pDialogManager = pDialogManager; }

   virtual bool HandleUserEvent( const DialogEvent *pEvent ) = 0;

   virtual DIALOGS_ID_T Id() const = 0;

protected:

   DialogManager * GetDialogManager() { return m_pDialogManager; }

   DialogManager * m_pDialogManager;

private slots:

   void OnBackClick() { m_pDialogManager->PopDialog(); }

   void OnMainMenuClick() { m_pDialogManager->ShowMainMenu(); }

private:

   QPushButton *m_pBackButton, *m_pHomeButton;

   QFrame *m_pHLine;

   QVBoxLayout *m_pMainLayout;
};

#endif // !defined(EA_5E763007_65F3_4242_B012_3D99E6A3EE17__INCLUDED_)
