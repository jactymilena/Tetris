#include <QApplication>
#include "FenetreBarGraph.h"

int main(int argv, char* argc[]) {
	QApplication app(argv, argc);
	FenetreBarGraph fenetre;

	fenetre.show();

	return app.exec();
}