#include <QApplication>
#include <DialogManager.h>
#include <QtNetwork/qnetworkproxy.h>

int main( int argc, char *argv[] )
{
   QApplication a( argc, argv );

   QNetworkProxy proxy;
   proxy.setType(QNetworkProxy::HttpProxy);
   proxy.setHostName("proxy.telma.nn");
   proxy.setPort(3128);
   QNetworkProxy::setApplicationProxy(proxy);

   DialogManager manager;
//test
   return a.exec();
}
