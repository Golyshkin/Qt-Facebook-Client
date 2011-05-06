#ifndef DIALOG_MAINMENU_H
#define DIALOG_MAINMENU_H

#include <FacebookDialog.h>
#include <QSignalMapper>

class QPushButton;
class QLabel;

const int USER_PHOTO_HEIGHT = 400;
const int USER_PHOTO_WIDTH = 300;

enum MAIN_MENU_OPTIONS_T
{
   Profile =0,
   Friends,
   News,
   Messages,
   Groups,
   Events,
   Photos,
   About,
   AboutQT
};

const int MAIN_MENU_OPTIONS_NUMBER = 9;
const int MAX_GRID_ROW = 3;

class DialogMainMenu : public FacebookDialog
{
    Q_OBJECT

public:

    DialogMainMenu( DialogEvent *pStartCmd = NULL, QWidget *parent = 0 );

    ~DialogMainMenu();

    virtual void SetUI();

    virtual bool HandleUserEvent( const DialogEvent *pEvent );

    virtual DIALOGS_ID_T Id() const { return DIALOG_MAINMENU; }

    static FacebookDialog * Instance( DialogEvent *pStartCmd = NULL );

public slots:

    void OnBackClick();

    void OnOptionsClick( int );
private:

   static FacebookDialog *m_pInstance;

   QPushButton *m_pBackButton;

   QLabel *m_pPhotoImage;

   QLabel *m_pUserInfo;

   QLabel *m_pUserStatus;

   QLabel *m_pLabel;

   QPushButton *m_pMyFriendsButton;

   QPushButton *m_pMMOptions[MAIN_MENU_OPTIONS_NUMBER];

   QSignalMapper *m_pSignalMapper;

 //  void RequestPersonalData();
};
#endif // DIALOG_MAINMENU_H
