#include "MyClass.h"

MyClass::MyClass(QWidget *parent)
	: QMainWindow(parent)
{
	this->setWindowTitle("Sortowanie");
	
	QWidget *centralWidget = new QWidget; 
	QWidget *table = new QWidget; 
	QWidget *timers = new QWidget;
	QVBoxLayout *mainLayout = new QVBoxLayout; 
	QHBoxLayout *settingsLayout = new QHBoxLayout; 
	QGroupBox *settings = new QGroupBox; 
	QHBoxLayout *tableLayout = new QHBoxLayout;
	QPushButton *startallButton = new QPushButton("Rozpocznij wszystkie");
	QPushButton *stopallButton = new QPushButton("Zatrzymaj wszystkie");
	QPushButton *restartallButton = new QPushButton("Zrestartuj wszystkie");

	
	QPushButton *startBubblesortButton = new QPushButton("Start");
	QPushButton *stopBubblesortButton = new QPushButton("Stop");
	QPushButton *restartBubblesortButton = new QPushButton("Restart");
	QGroupBox *settingsBubblesort = new QGroupBox; 
	QVBoxLayout *settingsBubblesortLayout = new QVBoxLayout; 

															 
	QPushButton *startInsertionsortButton = new QPushButton("Start");
	QPushButton *stopInsertionsortButton = new QPushButton("Stop");
	QPushButton *restartInsertionsortButton = new QPushButton("Restart");
	QGroupBox *settingsInsertionsort = new QGroupBox; 
	QVBoxLayout *settingsInsertionsortLayout = new QVBoxLayout; 


																
	QPushButton *startSelectionsortButton = new QPushButton("Start");
	QPushButton *stopSelectionsortButton = new QPushButton("Stop");
	QPushButton *restartSelectionsortButton = new QPushButton("Restart");
	QGroupBox *settingsSelectionsort = new QGroupBox; 
	QVBoxLayout *settingsSelectionsortLayout = new QVBoxLayout; 


																
	QPushButton *startHeapsortButton = new QPushButton("Start");
	QPushButton *stopHeapsortButton = new QPushButton("Stop");
	QPushButton *restartHeapsortButton = new QPushButton("Restart");
	QGroupBox *settingsHeapsort = new QGroupBox; 
	QVBoxLayout *settingsHeapsortLayout = new QVBoxLayout; 


														   
	connect(startBubblesortButton, SIGNAL(clicked()), this, SLOT(startBubblesort()));
	connect(stopBubblesortButton, SIGNAL(clicked()), this, SLOT(stopBubblesort()));
	connect(restartBubblesortButton, SIGNAL(clicked()), this, SLOT(restartBubblesort()));

	connect(startInsertionsortButton, SIGNAL(clicked()), this, SLOT(startInsertionsort()));
	connect(stopInsertionsortButton, SIGNAL(clicked()), this, SLOT(stopInsertionsort()));
	connect(restartInsertionsortButton, SIGNAL(clicked()), this, SLOT(restartInsertionsort()));

	connect(startSelectionsortButton, SIGNAL(clicked()), this, SLOT(startSelectionsort()));
	connect(stopSelectionsortButton, SIGNAL(clicked()), this, SLOT(stopSelectionsort()));
	connect(restartSelectionsortButton, SIGNAL(clicked()), this, SLOT(restartSelectionsort()));

	connect(startHeapsortButton, SIGNAL(clicked()), this, SLOT(startHeapsort()));
	connect(stopHeapsortButton, SIGNAL(clicked()), this, SLOT(stopHeapsort()));
	connect(restartHeapsortButton, SIGNAL(clicked()), this, SLOT(restartHeapsort()));

	connect(startallButton, SIGNAL(clicked()), this, SLOT(startAll()));
	connect(stopallButton, SIGNAL(clicked()), this, SLOT(stopAll()));
	connect(restartallButton, SIGNAL(clicked()), this, SLOT(restartAll()));


	settings->setTitle("Ustawienia");
	settings->setLayout(settingsLayout);

	settingsLayout->addWidget(settingsBubblesort);
	settingsLayout->addWidget(settingsInsertionsort);
	settingsLayout->addWidget(settingsSelectionsort);
	settingsLayout->addWidget(settingsHeapsort);

	settingsInsertionsort->setTitle("Sortowanie przez wstawianie");
	settingsBubblesort->setTitle(QString::fromUtf8("Sortowanie b�belkowe"));
	settingsSelectionsort->setTitle(QString::fromUtf8("Sortowanie przez wymian�"));
	settingsHeapsort->setTitle("Sortowanie stogowe");
	settingsBubblesort->setLayout(settingsBubblesortLayout);
	settingsInsertionsort->setLayout(settingsInsertionsortLayout);
	settingsSelectionsort->setLayout(settingsSelectionsortLayout);
	settingsHeapsort->setLayout(settingsHeapsortLayout);


	settingsBubblesortLayout->addWidget(startBubblesortButton);
	settingsBubblesortLayout->addWidget(stopBubblesortButton);
	settingsBubblesortLayout->addWidget(restartBubblesortButton);
	settingsInsertionsortLayout->addWidget(startInsertionsortButton);
	settingsInsertionsortLayout->addWidget(stopInsertionsortButton);
	settingsInsertionsortLayout->addWidget(restartInsertionsortButton);
	settingsSelectionsortLayout->addWidget(startSelectionsortButton);
	settingsSelectionsortLayout->addWidget(stopSelectionsortButton);
	settingsSelectionsortLayout->addWidget(restartSelectionsortButton);
	settingsHeapsortLayout->addWidget(startHeapsortButton);
	settingsHeapsortLayout->addWidget(stopHeapsortButton);
	settingsHeapsortLayout->addWidget(restartHeapsortButton);

	tableLayout->addWidget(bubblesortLabel);
	tableLayout->addWidget(insertionsortLabel);
	tableLayout->addWidget(selectionsortLabel);
	tableLayout->addWidget(heapsortLabel);

	name->setText("By Piotr Krawiec");

	timers->setLayout(tableLayout);

	mainLayout->addWidget(table);
	table->setMinimumSize(1050, 550);
	mainLayout->addWidget(timers);
	timers->setMaximumSize(1050, 50);
	mainLayout->addWidget(settings);
	mainLayout->addWidget(startallButton);
	mainLayout->addWidget(stopallButton);
	mainLayout->addWidget(restartallButton);
	mainLayout->addWidget(name);



	centralWidget->setLayout(mainLayout);

	this->setCentralWidget(centralWidget);
	this->setMaximumSize(1050, 900);
	this->setMinimumSize(1050, 900);

	std::srand(time(NULL));
	for (int k = 0; k < 35; k++)
		bubblesortTable[k] = rand() % 250;
	for (int k = 0; k < 35; k++)
		insertionsortTable[k] = rand() % 250;
	for (int k = 0; k < 35; k++)
		selectionsortTable[k] = rand() % 250;
	for (int k = 0; k < 36; k++)
		heapsortTable[k] = rand() % 250;

	isstopedBubbleSort = 1;
	isstopedInsertionSort = 1;
	isstopedSelectionSort = 1;
	isstopedHeapSort = 1;
	insertionsortI = 0;
	selectionsortI = 0;
	heapsortSize = 35;
	isheapCreated = 0;
	bubblesortP = 0;

	klucz = 0;
	m = 0;
	n = 0;



	bubblesortLabel->setText("Czas: 0 sekund.");
	selectionsortLabel->setText("Czas: 0 sekund.");
	insertionsortLabel->setText("Czas: 0 sekund.");
	heapsortLabel->setText("Czas: 0 sekund.");


}

void MyClass::paintEvent(QPaintEvent *e)
{
	QPainter p;
	p.begin(this);
	
	QBrush niebieski(QColor(51, 160, 210));
	QBrush fioletowy(QColor(174, 83, 255));
	QBrush jasnyniebieski(QColor(36, 195, 255));
	QBrush yellow(QColor(255, 226, 36));
	p.setClipping(1);
	p.setPen(Qt::NoPen);
	p.setBrush(niebieski);
	for (int l = 0; l < 35; l++)
	{
		p.drawRect(5, 20 + 15 * l, bubblesortTable[l] + 5, 10);
	}
	p.setBrush(fioletowy);
	for (int l = 0; l < 35; l++)
	{
		p.drawRect(265, 20 + 15 * l, insertionsortTable[l] + 5, 10);
	}
	p.setBrush(jasnyniebieski);
	for (int l = 0; l < 35; l++)
	{
		p.drawRect(525, 20 + 15 * l, selectionsortTable[l] + 5, 10);
	}
	p.setBrush(yellow);
	for (int l = 1; l < 36; l++)
	{
		p.drawRect(785, 5 + 15 * l, heapsortTable[l] + 5, 10);
	}

	p.end();
}


void MyClass::startBubblesort()
{
	if (isstopedBubbleSort == 1)
	{
		isstopedBubbleSort = 0;
		qDebug() << "Start";
		bubblesortTimer.reset();
		sortBubblesort();
		update();
	}
}
void MyClass::stopBubblesort()
{
	if (isstopedBubbleSort == 0)
	{
		qDebug() << "Stop";
		isstopedBubbleSort = 1;
	}
}
void MyClass::restartBubblesort()
{
	this->bubblesortLabel->setText("Czas: 0 sekund.");
	qDebug() << "Restart";
	std::srand(time(NULL));
	for (int k = 0; k < 35; k++)
		bubblesortTable[k] = rand() % 250;
	update();
	bubblesortP = 0;
}
void MyClass::sortBubblesort()
{
	if (isstopedBubbleSort == 0) {
		double add = bubblesortTimer.elapsed();
		QString text = "Czas: ";
		text += QString::number(add);
		text += " sekund.";
		this->bubblesortLabel->setText(text);
		if (bubblesortP < 35)
		{
			if (bubblesortTable[bubblesortP] > bubblesortTable[bubblesortP + 1])
			{
				bubblesortZamiana = true; 
				schowekBubblesort = bubblesortTable[bubblesortP];
				bubblesortTable[bubblesortP] = bubblesortTable[bubblesortP + 1];
				bubblesortTable[bubblesortP + 1] = schowekBubblesort;
				update();
			}
			bubblesortP++;
		}
		else if (bubblesortP == 35)
		{
			bubblesortP = 0;
			if (!bubblesortZamiana)
				stopBubblesort();
		}
		QTimer::singleShot(250, this, SLOT(sortBubblesort()));
	}
}

void MyClass::startInsertionsort()
{
	if (isstopedInsertionSort == 1)
	{
		insertionsortTimer.reset();
		isstopedInsertionSort = 0;
		qDebug() << "Startinsertion";
		sortInsertionsort();
		update();
	}
}
void MyClass::stopInsertionsort()
{
	if (isstopedInsertionSort == 0)
	{
		qDebug() << "Stop";
		isstopedInsertionSort = 1;
	}
}
void MyClass::restartInsertionsort()
{

	this->insertionsortLabel->setText("Czas: 0 sekund.");


	qDebug() << "Restartinsertion";
	std::srand(time(NULL));
	for (int k = 0; k < 35; k++)
		insertionsortTable[k] = rand() % 250;
	insertionsortI = 0;
	update();
}
void MyClass::sortInsertionsort()
{
	if (isstopedInsertionSort == 0) {

		double add = insertionsortTimer.elapsed();

		QString text = "Czas: ";
		text += QString::number(add);
		text += " sekund.";

		this->insertionsortLabel->setText(text);

		if (m>0 && insertionsortTable[m - 1]>klucz) {
			insertionsortTable[m] = insertionsortTable[m - 1];
			m--;
			insertionsortTable[m] = klucz;
		}
		if (!(m>0 && insertionsortTable[m - 1]>klucz))
		{
			if (n == 50) {
				stopInsertionsort();
			}
			m = n;
			if (n < 50)
				klucz = insertionsortTable[n];
			n++;
		}

		QTimer::singleShot(250, this, SLOT(sortInsertionsort()));
		update();
	}
}

void MyClass::startSelectionsort() {
	if (isstopedSelectionSort == 1)
	{
		selectionsortTimer.reset();
		isstopedSelectionSort = 0;
		qDebug() << "Start selection";
		sortSelectionsort();
		update();
	}
}
void MyClass::stopSelectionsort() {
	if (isstopedSelectionSort == 0)
	{
		qDebug() << "Stop";
		isstopedSelectionSort = 1;
	}
}
void MyClass::restartSelectionsort() {
	this->selectionsortLabel->setText("Czas: 0 sekund.");

	qDebug() << "Restart selectionsort";
	selectionsortI = 0;
	std::srand(time(NULL));
	for (int k = 0; k < 35; k++)
		selectionsortTable[k] = rand() % 250;
	update();
}
void MyClass::sortSelectionsort() {
	if (isstopedSelectionSort == 0) {

		double add = selectionsortTimer.elapsed();

		QString text = "Czas: ";
		text += QString::number(add);
		text += " sekund.";

		this->selectionsortLabel->setText(text);

		if (selectionsortI < 35)
		{
			max = selectionsortI; 
			for (j = selectionsortI + 1; j < 35; j++) 
			{
				if (selectionsortTable[j] < selectionsortTable[max]) 
					max = j;
			}
			
			schowekSelectionsort = selectionsortTable[max];
			selectionsortTable[max] = selectionsortTable[selectionsortI];
			selectionsortTable[selectionsortI] = schowekSelectionsort;
			selectionsortI++;
			update();
			QTimer::singleShot(200, this, SLOT(sortSelectionsort()));
		}
		else {
			stopSelectionsort();
		}
	}
}
void MyClass::startHeapsort() {
	if (isheapCreated == 0) {
		budKopiec(heapsortTable, heapsortSize);
		isheapCreated = 1;
		heapsortSize = 35;
	}
	if (isstopedHeapSort == 1)
	{
		heapsortTimer.reset();
		isstopedHeapSort = 0;
		heapsortI = heapsortSize;
		qDebug() << "Start heap";
		sortHeapsort();
		update();
	}
}
void MyClass::stopHeapsort() {
	if (isstopedHeapSort == 0)
	{
		qDebug() << "Stop heapsort";
		isstopedHeapSort = 1;
	}
}
void MyClass::restartHeapsort() {
	this->heapsortLabel->setText("Czas: 0 sekund.");
	qDebug() << "Restart heapsort";
	heapsortSize = 35;
	std::srand(time(NULL));
	for (int k = 0; k < 36; k++)
		heapsortTable[k] = rand() % 250;
	update();
	isheapCreated = 0;
}
void MyClass::sortHeapsort() {
	if (isstopedHeapSort == 0) {

		double add = heapsortTimer.elapsed();

		QString text = "Czas: ";
		text += QString::number(add);
		text += " sekund.";
		this->heapsortLabel->setText(text);

		if (heapsortI > 1)
		{
			schowekHeapsort = heapsortTable[heapsortI];
			heapsortTable[heapsortI] = heapsortTable[1];
			heapsortTable[1] = schowekHeapsort;
			heapsortSize--;
			heapify(heapsortTable, heapsortSize, 1);
			update();
			heapsortI--;
			QTimer::singleShot(200, this, SLOT(sortHeapsort()));
		}
		else {
			stopHeapsort();
		}
	}
}
void MyClass::heapify(int *tab, int heap_size, int i) {
	int largest, temp;
	int l = 2 * i, r = (2 * i) + 1;
	if (l <= heap_size && tab[l] > tab[i])
		largest = l;
	else largest = i;
	if (r <= heap_size && tab[r] > tab[largest])
		largest = r;
	if (largest != i) {
		temp = tab[largest];
		tab[largest] = tab[i];
		tab[i] = temp;
		heapify(tab, heap_size, largest);
	}
}
void MyClass::budKopiec(int *tab, int rozmiar) {
	for (int i = rozmiar / 2; i > 0; i--)
		heapify(tab, rozmiar, i);
}

void MyClass::startAll()
{
	startBubblesort();
	startInsertionsort();
	startSelectionsort();
	startHeapsort();
}
void MyClass::stopAll()
{
	stopBubblesort();
	stopInsertionsort();
	stopSelectionsort();
	stopHeapsort();
}
void MyClass::restartAll()
{
	restartBubblesort();
	restartInsertionsort();
	restartSelectionsort();
	restartHeapsort();
}

