#include "FenetrePrincipale.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    FenetrePrincipale fenetre1;
    QPixmap pixmap("tetrisIcon.jpeg");
    QIcon *icon;
    icon = new QIcon();
    icon->addPixmap(pixmap);
    

    fenetre1.setWindowIcon(*icon);
    fenetre1.show();

    delete icon;
    return app.exec();
    
}