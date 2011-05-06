#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <FacebookNetwokClient_def.h>
#include <FacebookDialog.h>
#include <QUrl>

class QWebView;
class QSplashScreen;

class DialogLogin : public FacebookDialog
{
    Q_OBJECT

public:

    DialogLogin( DialogEvent *pStartCmd = NULL, QWidget *parent = 0 );

    ~DialogLogin();

    virtual void SetUI();

    virtual bool HandleUserEvent( const DialogEvent *pEvent );

    virtual DIALOGS_ID_T Id() const { return DIALOG_LOGIN; }

    static FacebookDialog * Instance( DialogEvent *pStartCmd = NULL );

protected:

private slots:

   void OnWebViewLoadFinished();

   void OnWebViewLoadProgress( int aProgressState );

   void OnWebViewLinkClicked( const QUrl& aURL );

   void OnFaceBookNetwokManagerStatusChanged( FACEBOOK_REQUEST_T aState );

private:

   static FacebookDialog *m_pInstance;

   QSplashScreen *m_pSplashScreen;

   QWebView *m_pWebView;
};

#endif // DIALOGLOGIN_H
