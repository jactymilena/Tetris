/*===================================
Auteur: fona1101 elka0602 saej3101
Nom du fichier: main.cpp
Date: 15 avril 2021
But: Fichier principal
====================================*/

#include "FenetrePrincipale.h"
#include <QApplication>
#include <mciapi.h>
#include <qdebug.h>

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
    mciSendString(L"open Tetris.mp3 type mpegvideo alias maintheme", nullptr, 0, nullptr);
    mciSendString(L"play maintheme repeat", NULL, 0, NULL);
    
    fenetre.setWindowIcon(*icon);
    fenetre.show();

    delete icon;
    return app.exec();
}
