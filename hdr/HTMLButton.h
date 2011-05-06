///////////////////////////////////////////////////////////
//  TelecaFacebookDialog.h
//  Implementation of the Class TelecaFacebookDialog
//  Created on:      05-May-2011 9:24:48 AM
//  Original author: Golyshkin A.
///////////////////////////////////////////////////////////

#ifndef HTMLBUTTON_H
#define HTMLBUTTON_H

#include <QLabel>

class HTMLButton: public QLabel
{
   Q_OBJECT

public:
   HTMLButton( QString aString, QWidget *parent = 0 ) : QLabel( aString, parent )
   {
      setAlignment( Qt::AlignLeft );
   }

protected:

   virtual void mousePressEvent( QMouseEvent *pEvent )
   {
      emit pressed();
   }

   virtual void mouseReleaseEvent( QMouseEvent *pEvent )
   {
      emit released();
      emit clicked();
   }

signals:

   void clicked();

   void pressed();

   void released();
};

#endif // HTMLBUTTON_H
