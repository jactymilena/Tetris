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
    
    fenetre1.setWindowIcon(*icon);
    fenetre1.show();
    mciSendString(L"open Tetris.mp3 type mpegvideo alias maintheme", nullptr, 0, nullptr);
    mciSendString(L"play maintheme repeat", NULL, 0, NULL);
   // MCIERROR error = mciSendString(L"setaudio maintheme volume to 25", nullptr, 0, nullptr);
    
    //PlaySound(L"Tetris.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC | SND_LOOP);
    fenetre.setWindowIcon(*icon);
    fenetre.show();

    delete icon;
    return app.exec();
}
