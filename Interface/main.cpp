#include "FenetrePrincipale.h"
#include <QApplication>

int main(int argc, char* argv[])
 {
    QApplication app(argc, argv);

    FenetrePrincipale fenetre;
    fenetre.setFixedSize(900, 750);
    fenetre.setStyleSheet("background-image: url(background.png)");
    QPixmap pixmap("icon-cercle.png");
    QIcon *icon;
    icon = new QIcon();
    icon->addPixmap(pixmap);
    
    fenetre.setWindowIcon(*icon);
    fenetre.show();

    delete icon;
    return app.exec();
}
