#include "FenetreBarGraph.h"

#include "CommunicationFPGA.h"



bool statutport = false;            // statut du port de communication qui sera cree

int compteur_temps = 0;
int swt = 0;                         // donnee recue du FPGA
int aff7sg_octet0 = 0;               // octet 0 (droite) pour afficheur 7 segments
int aff7sg_octet1 = 0;               // octet 0 (droite) pour afficheur 7 segments                    

const int nitermax = 10000;         // Nbre d'itération max de la boucle de lecture d'acquisition (limite pour tests)
									 // changer la condition de boucle sans cette limite selon le besoin de l'application
const int delai_boucle = 10;         // delai d'attente ajouté dans la boucle de lecture en ms

// numeros de registres correspondants pour les echanges FPGA <-> PC  ...
unsigned const int nreg_lect_stat_btn = 0;  // fpga -> PC  Statut et BTN lus FPGA -> PC
unsigned const int nreg_lect_swt = 1;       // fpga -> PC  SWT lus FPGA -> PC
unsigned const int nreg_lect_cmpt_t = 2;    // fpga -> PC  compteur temps FPGA -> PC 
unsigned const int nreg_lect_can0 = 3;      // fpga -> PC  canal 0 lus FPGA -> PC
unsigned const int nreg_lect_can1 = 4;      // fpga -> PC  canal 1 lus FPGA -> PC
unsigned const int nreg_lect_can2 = 5;      // fpga -> PC  canal 2 lus FPGA -> PC
unsigned const int nreg_lect_can3 = 6;      // fpga -> PC  canal 3 lus FPGA -> PC
unsigned const int nreg_ecri_aff7sg0 = 7;   // PC -> fpga (octet 0  aff.7 seg.)
unsigned const int nreg_ecri_aff7sg1 = 8;   // PC -> fpga (octet 1  aff.7 seg.)
unsigned const int nreg_ecri_aff7dot = 9;   // PC -> fpga (donnees dot-points)
unsigned const int nreg_ecri_led = 10;

FenetreBarGraph::FenetreBarGraph()
{
	barGraph0 = new QProgressBar();
	barGraph0->setStyleSheet("QProgressBar::chunk { background-color: #2196F3; width: 10px; margin: 0.5px } QProgressBar { border: 2px solid white; border-radius: 5px; background: white; text-align: center; color: black }");
	barGraph0->setMinimum(0);
	barGraph0->setMaximum(256);

	barGraph1 = new QProgressBar();
	barGraph1->setStyleSheet("QProgressBar::chunk { background-color: #2196F3; width: 10px; margin: 0.5px } QProgressBar { border: 2px solid white; border-radius: 5px; background: white; text-align: center; color: black }");
	barGraph1->setMinimum(0);
	barGraph1->setMaximum(256);

	barGraph2 = new QProgressBar();
	barGraph2->setStyleSheet("QProgressBar::chunk { background-color: #2196F3; width: 10px; margin: 0.5px } QProgressBar { border: 2px solid white; border-radius: 5px; background: white; text-align: center; color: black }");
	barGraph2->setMinimum(0);
	barGraph2->setMaximum(256);

	barGraph3 = new QProgressBar();
	barGraph3->setStyleSheet("QProgressBar::chunk { background-color: #2196F3; width: 10px; margin: 0.5px } QProgressBar { border: 2px solid white; border-radius: 5px; background: white; text-align: center; color: black }");
	barGraph3->setMinimum(0);
	barGraph3->setMaximum(256);

	sortieTitre = new QLabel("SORTIE :");
	chanel0Label = new QLabel("Channel 0");
	chanel1Label = new QLabel("Channel 1");
	chanel2Label = new QLabel("Channel 2");
	chanel3Label = new QLabel("Channel 3");

	chanel0LabelValue = new QLabel();
	chanel1LabelValue = new QLabel();
	chanel2LabelValue = new QLabel();
	chanel3LabelValue = new QLabel();

	verticalLayout = new QVBoxLayout();
	verticalLayout->addWidget(sortieTitre);
	verticalLayout->addWidget(chanel0Label);
	verticalLayout->addWidget(chanel0LabelValue);
	verticalLayout->addWidget(barGraph0);
	verticalLayout->addWidget(chanel1Label);
	verticalLayout->addWidget(chanel1LabelValue);
	verticalLayout->addWidget(barGraph1);
	verticalLayout->addWidget(chanel2Label);
	verticalLayout->addWidget(chanel2LabelValue);
	verticalLayout->addWidget(barGraph2);
	verticalLayout->addWidget(chanel3Label);
	verticalLayout->addWidget(chanel3LabelValue);
	verticalLayout->addWidget(barGraph3);

	timer = new QTimer();
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(lireFPGA()));
	timer->start(10);

	setLayout(verticalLayout);
}

int FenetreBarGraph::lireFPGA() {

	CommunicationFPGA port;
	static int canal_a_afficher = 0;
	int indice_canal_a_afficher = 0;
	int stat_btn = 0;
	int statut_circuit = 0;
	statutport = port.lireRegistre(nreg_lect_stat_btn, statut_circuit);

	if (statutport) statutport = port.lireRegistre(nreg_lect_stat_btn, stat_btn);     // lecture statut et BTN
	else { qDebug() << "Erreur du port nreg_lect_stat_btn"; exit(1); }

	int echconv[4];
	if (statutport) statutport = port.lireRegistre(nreg_lect_can0, echconv[0]);       // lecture canal 0
	else { qDebug() << "Erreur du port nreg_lect_can0"; exit(1); }
	if (statutport) statutport = port.lireRegistre(nreg_lect_can1, echconv[1]);       // lecture canal 1
	else { qDebug() << "Erreur du port nreg_lect_can1"; exit(1); }
	if (statutport) statutport = port.lireRegistre(nreg_lect_can2, echconv[2]);       // lecture canal 2
	else { qDebug() << "Erreur du port nreg_lect_can2"; exit(1); }
	if (statutport) statutport = port.lireRegistre(nreg_lect_can3, echconv[3]);       // lecture canal 3
	else { qDebug() << "Erreur du port nreg_lect_can3"; exit(1); }
	if (!statutport) {
		qDebug() << "Erreur du port dans la boucle";
		exit(1);
	}
	statutport = port.ecrireRegistre(nreg_ecri_led, 1);
	if ((stat_btn & 1) != 0)
	{
		//Phonème A
		if((echconv[0] > 202 && echconv[0] < 222) && (echconv[1] > 15 && echconv[1] < 35) && (echconv[2] > 0 && echconv[2] < 20) && (echconv[3] > 0 && echconv[3] < 15))
		{
			return 1;
		}
		//Phonème U
		else if((echconv[0] > 0 && echconv[0] < 20) && (echconv[1] > 0 && echconv[1] < 20) && (echconv[2] > 165 && echconv[2] < 185) && (echconv[3] > 40 && echconv[3] < 60))
		{
			return 2;
		}
		//Phonème E
		else if ((echconv[0] > 183 && echconv[0] < 203) && (echconv[1] > 227 && echconv[1] < 247) && (echconv[2] > 90 && echconv[2] < 110) && (echconv[3] > 15 && echconv[3] < 35))
		{
			return 3;
		}
		//Phonème I
		else if ((echconv[0] > 0 && echconv[0] < 20) && (echconv[1] > 90 && echconv[1] < 110) && (echconv[2] > 177 && echconv[2] < 197) && (echconv[3] > 15 && echconv[3] < 35))
		{
			return 4;
		}
	}
	else if ((stat_btn & 2) != 0)
	{
		canal_a_afficher++;

		if (canal_a_afficher  > 3) canal_a_afficher = 0;
	}

	barGraph0->setValue(echconv[0]);
	barGraph1->setValue(echconv[1]);
	barGraph2->setValue(echconv[2]);
	barGraph3->setValue(echconv[3]);

	chanel0LabelValue->setText(QString::number(echconv[0]));
	chanel1LabelValue->setText(QString::number(echconv[1]));
	chanel2LabelValue->setText(QString::number(echconv[2]));
	chanel3LabelValue->setText(QString::number(echconv[3]));

	qApp->processEvents();

	statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, canal_a_afficher);                    // envoyer numero canal_a_afficher afficheur 7 segments
	statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, echconv[canal_a_afficher]); // envoyer valeur echconv[] afficheur 7 segments

	return 0;
}
