#include <QWidget>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QDebug>
#include <QTimer>
#include <QLabel>;
#include <QApplication>

class FenetreBarGraph : public QWidget {
	Q_OBJECT
public:
	FenetreBarGraph();
public slots:
	//Lecture FPGA
	int lireFPGA();
private:
	QProgressBar* barGraph0;
	QProgressBar* barGraph1;
	QProgressBar* barGraph2;
	QProgressBar* barGraph3;

	QVBoxLayout* verticalLayout;
	QTimer* timer;
	QLabel* chanel0Label;
	QLabel* chanel1Label;
	QLabel* chanel2Label;
	QLabel* chanel3Label;

	QLabel* chanel0LabelValue;
	QLabel* chanel1LabelValue;
	QLabel* chanel2LabelValue;
	QLabel* chanel3LabelValue;

	QLabel* sortieTitre;

};