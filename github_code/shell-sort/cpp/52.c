#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sorts/bubblesort.h"
#include "sorts/selectionsort.h"
#include "sorts/shellsort.h"
#include "sorts/mergesort.h"
#include "sorts/quicksort.h"
#include "sorts/countingsort.h"
#include "timemanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _size = {500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 10000000, 100000000}; // max index - 9
    _currentSizeIndex = 0;
    _currentSortIndex = 0;
    _sortInt.push_back([&]() { // index 0
        this->onClickBubbleSort();
        this->onClickBubbleSort();
        return this->onClickBubbleSort(); });
    _sortInt.push_back([&]() { // index 1
        this->onClickSelectionSort();
        this->onClickSelectionSort();
        return this->onClickSelectionSort(); });
    _sortInt.push_back([&]() { // index 2
        this->onClickShellSort("Shell");
        this->onClickShellSort("Shell");
        return this->onClickShellSort("Shell"); });
    _sortInt.push_back([&]() { // index 3
        this->onClickShellSort("Pratt");
        this->onClickShellSort("Pratt");
        return this->onClickShellSort("Pratt"); });
    _sortInt.push_back([&]() { // index 4
        this->onClickShellSort("Pratt2");
        this->onClickShellSort("Pratt2");
        return this->onClickShellSort("Pratt2"); });
    _sortInt.push_back([&]() { // index 5
        this->onClickMergeSort();
        this->onClickMergeSort();
        return this->onClickMergeSort(); });
    _sortInt.push_back([&]() { // index 6
        this->onClickQuickSort();
        this->onClickQuickSort();
        return this->onClickQuickSort(); });
    _sortInt.push_back([&]() { // index 7
        this->onClickCountingSort();
        this->onClickCountingSort();
        return this->onClickCountingSort(); });

    _sortDouble.push_back([&]() {
        this->onClickBubbleSortD();
        this->onClickBubbleSortD();
        return this->onClickBubbleSortD(); });
    _sortDouble.push_back([&]() {
        this->onClickSelectionSortD();
        this->onClickSelectionSortD();
        return this->onClickSelectionSortD(); });
    _sortDouble.push_back([&]() {
        this->onClickShellSortD("Shell");
        this->onClickShellSortD("Shell");
        return this->onClickShellSortD("Shell"); });
    _sortDouble.push_back([&]() {
        this->onClickShellSortD("Pratt");
        this->onClickShellSortD("Pratt");
        return this->onClickShellSortD("Pratt"); });
    _sortDouble.push_back([&]() {
        this->onClickShellSortD("Pratt2");
        this->onClickShellSortD("Pratt2");
        return this->onClickShellSortD("Pratt2"); });
    _sortDouble.push_back([&]() {
        this->onClickMergeSortD();
        this->onClickMergeSortD();
        return this->onClickMergeSortD(); });
    _sortDouble.push_back([&]() {
        this->onClickQuickSortD();
        this->onClickQuickSortD();
        return this->onClickQuickSortD(); });
//    connect(ui->pushButtonStartSort, SIGNAL(clicked()), this, SLOT(onClickSelectionSort()));
//    connect(ui->pushButtonStartSort, SIGNAL(clicked()), this, SLOT(onClickShellSort()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonStartSort_clicked()
{
    sortIntRandom();
    sortIntSorted();
    sortIntReverse();
    sortDoubleRandom();
    sortDoubleSorted();
    sortDoubleReverse();
}

void MainWindow::onClickSelectionSort()
{
    static int runCount;
    SelectionSort <int> selSort;
    selSort.sort();
    qDebug() << "selection sort time:" << selSort.getAlgorithmTime();
    ++runCount;
    if(runCount >= 3)
    {
        double algTimeSum = selSort.getAlgTimeSum()/3;
        this->saveResultToFile("Selection", algTimeSum);
        ui->textOutput->append("Selection: " + QString::number(algTimeSum));
        runCount = 0;
    }
}

void MainWindow::onClickShellSort(QString sequenceName)
{
    static int runCount;
    ShellSort <int> shell(sequenceName);
    shell.sort();
    qDebug() << "shell sort time:" << shell.getAlgorithmTime();
    ++runCount;
    if(runCount >= 3)
    {
        if(sequenceName == "Shell") {
            double algTimeSum = shell.getAlgTimeSumShell()/3;
            saveResultToFile("Shell(Shell sequence)", algTimeSum);
            ui->textOutput->append("Shell(Shell sequence): " + QString::number(algTimeSum));
        }
        else
            if(sequenceName == "Pratt") {
                double algTimeSum = shell.getAlgTimeSumPratt()/3;
                saveResultToFile("Shell(Pratt sequence)",algTimeSum);
                ui->textOutput->append("Shell(Pratt sequence): " + QString::number(algTimeSum));
            }
            else
            {
                double algTimeSum = shell.getAlgTimeSumPrattSecond()/3;
                saveResultToFile("Shell(PrattSecond sequence)", algTimeSum);
                ui->textOutput->append("Shell(PrattSecond sequence): " + QString::number(algTimeSum));
            }
        runCount = 0;
    }
}

void MainWindow::onClickMergeSort()
{
    static int runCount;
    MergeSort <int> mSort;
    mSort.sort();
    qDebug() << "merge sort time:" << mSort.getAlgorithmTime();
    ++runCount;
    if(runCount >= 3)
    {
        double algTimeSum = mSort.getAlgTimeSum()/3;
        saveResultToFile("Merge", algTimeSum);
        ui->textOutput->append("Merge: " + QString::number(algTimeSum));
        runCount = 0;
    }
}

void MainWindow::onClickQuickSort()
{
    static int runCount;
    QuickSort <int> quSort;
    quSort.sort();
    qDebug() << "quick sort time: " << quSort.getAlgorithmTime();
    ++runCount;
    if(runCount >= 3)
    {
        double algTimeSum = quSort.getAlgTimeSum()/3;
        saveResultToFile("Quick", algTimeSum);
        ui->textOutput->append("Quick: " + QString::number(algTimeSum));
        runCount = 0;
    }

}

void MainWindow::onClickCountingSort()
{
    static int runCount;
    CountingSort <int> cSort;
    cSort.sort();
    qDebug() << "counting sort time: " << cSort.getAlgorithmTime();
    ++runCount;
    if(runCount >= 3)
    {
        double algTimeSum = cSort.getAlgTimeSum()/3;
        saveResultToFile("Counting", algTimeSum);
        ui->textOutput->append("Counting: " + QString::number(algTimeSum));
        runCount = 0;
    }
}

void MainWindow::onClickBubbleSort()
{
    static int runCount;
    BubbleSort <int> bSort;
//    auto hTimer = std::async(std::launch::async, &runTimer, this);
    bSort.sort();
//    stopTimerFlag = true;
    qDebug() << "Simple Bubble: " << bSort.getAlgorithmTime();
    bSort.sortOptimized();
    qDebug() << "Optimized Bubble: " << bSort.getAlgorithmTime();
    bSort.sortWithFlag();
    qDebug() << "bubble sort with flag time: " << bSort.getAlgorithmTime();
    ++runCount;
    if(runCount >= 3)
    {
        double algTimeSumSimple = bSort.getAlgTimeSumSimple()/3;
        double algTimeSumOptimized = bSort.getAlgTimeSumOptimized()/3;
        double algTimeSumWithFlag = bSort.getAlgTimeSumWithFlag()/3;
        saveResultToFile("Simple Bubble", algTimeSumSimple);
        saveResultToFile("Optimized Bubble", algTimeSumOptimized);
        saveResultToFile("With flag Bubble", algTimeSumWithFlag);
        ui->textOutput->append("Simple Bubble: " + QString::number(algTimeSumSimple));
        ui->textOutput->append("Optimized Bubble: " + QString::number(algTimeSumOptimized));
        ui->textOutput->append("With flag Bubble: " + QString::number(algTimeSumWithFlag));
        runCount = 0;
    }
}


void MainWindow::onClickSelectionSortD()
{
    static int runCount;
    SelectionSort <double> selSort;
    selSort.sort();
    ++runCount;
    if(runCount >= 3)
    {
        double algTimeSum = selSort.getAlgTimeSum()/3;
        this->saveResultToFile("Selection", algTimeSum);
        ui->textOutput->append("Selection: " + QString::number(algTimeSum));
        runCount = 0;
    }
    qDebug() << "selection sort time:" << selSort.getAlgorithmTime();
}

void MainWindow::onClickShellSortD(QString sequenceName)
{
    static int runCount;
    ShellSort <double> shell(sequenceName);
    shell.sort();
    ++runCount;
    if(runCount >= 3)
    {
        if(sequenceName == "Shell") {
            double algTimeSum = shell.getAlgTimeSumShell()/3;
            saveResultToFile("Shell(Shell sequence)", algTimeSum);
            ui->textOutput->append("Shell(Shell sequence): " + QString::number(algTimeSum));
        }
        else
            if(sequenceName == "Pratt") {
                double algTimeSum = shell.getAlgTimeSumPratt()/3;
                saveResultToFile("Shell(Pratt sequence)", algTimeSum);
                ui->textOutput->append("Shell(Pratt sequence): " + QString::number(algTimeSum));
            }
            else
            {
                double algTimeSum = shell.getAlgTimeSumPrattSecond()/3;
                saveResultToFile("Shell(PrattSecond sequence)", algTimeSum);
                ui->textOutput->append("Shell(PrattSecond sequence): " + QString::number(algTimeSum));
            }
        runCount = 0;
    }
    qDebug() << "shell sort time:" << shell.getAlgorithmTime();
}

void MainWindow::onClickMergeSortD()
{
    static int runCount;
    MergeSort <double> mSort;
    mSort.sort();
    ++runCount;
    if(runCount >= 3)
    {
        double algTimeSum = mSort.getAlgTimeSum()/3;
        saveResultToFile("Merge", algTimeSum);
        ui->textOutput->append("Merge: " + QString::number(algTimeSum));
        runCount = 0;
    }
    qDebug() << "merge sort time:" << mSort.getAlgorithmTime();
}

void MainWindow::onClickQuickSortD()
{
    static int runCount;
    QuickSort <double> quSort;
    quSort.sort();
    ++runCount;
    if(runCount >= 3)
    {
        double algTimeSum = quSort.getAlgTimeSum()/3;
        saveResultToFile("Quick", algTimeSum);
        ui->textOutput->append("Quick: " + QString::number(algTimeSum));
        runCount = 0;
    }
    qDebug() << "quick sort time: " << quSort.getAlgorithmTime();
}

void MainWindow::onClickBubbleSortD()
{
    static int runCount;
    BubbleSort <double> bSort;
    bSort.sort();
    qDebug() << "simple bubble sort time: " << bSort.getAlgorithmTime();
    bSort.sortOptimized();
    qDebug() << "optimized bubble sort time: " << bSort.getAlgorithmTime();
    bSort.sortWithFlag();
    qDebug() << "bubble sort with flag time: " << bSort.getAlgorithmTime();
    ++runCount;
    if(runCount >= 3)
    {
        double algTimeSumSimple = bSort.getAlgTimeSumSimple()/3;
        double algTimeSumOptimized = bSort.getAlgTimeSumOptimized()/3;
        double algTimeSumWithFlag = bSort.getAlgTimeSumWithFlag()/3;
        saveResultToFile("Simple Bubble", algTimeSumSimple);
        saveResultToFile("Optimized Bubble", algTimeSumOptimized);
        saveResultToFile("With flag Bubble", algTimeSumWithFlag);
        ui->textOutput->append("Simple Bubble: " + QString::number(algTimeSumSimple));
        ui->textOutput->append("Optimized Bubble: " + QString::number(algTimeSumOptimized));
        ui->textOutput->append("With flag Bubble: " + QString::number(algTimeSumWithFlag));
        runCount = 0;
    }

}

void MainWindow::prepareArray(const unsigned int size, QString type)
{
    if(type == "int")
    {
        generateArray(_arrInt, _size[size]);
        saveArrayToFile(_arrInt);
        _arrInt.clear();
        return;
    }else
        if(type == "sorted int" || type == "s int")
        {
            generateArray(_arrInt, _size[size]);
            std::sort(_arrInt.begin(), _arrInt.end());
            saveArrayToFile(_arrInt);
            _arrInt.clear();
            return;
        }else
            if(type == "reverse int" || type == "r int")
            {
                generateArray(_arrInt, _size[size]);
                if(std::is_sorted(_arrInt.begin(), _arrInt.end()))
                    std::reverse(_arrInt.begin(), _arrInt.end());
                else
                    std::sort(_arrInt.begin(), _arrInt.end(), std::greater<int>());
                saveArrayToFile(_arrInt);
                _arrInt.clear();
                return;
            }
    if(type == "double")
    {
        generateArray(_arrDouble, _size[size]);
        saveArrayToFile(_arrDouble);
        _arrDouble.clear();
        return;
    }else
        if(type == "sorted double" || type == "s double")
        {
            generateArray(_arrDouble, _size[size]);
            std::sort(_arrDouble.begin(), _arrDouble.end());
            saveArrayToFile(_arrDouble);
            _arrDouble.clear();
            return;
        }else
            if(type == "reverse double" || type == "r double")
            {
                generateArray(_arrDouble, _size[size]);;
                if(std::is_sorted(_arrDouble.begin(), _arrDouble.end()))
                    std::reverse(_arrDouble.begin(), _arrDouble.end());
                else
                    std::sort(_arrDouble.begin(), _arrDouble.end(), std::greater<double>());
                saveArrayToFile(_arrDouble);
                _arrDouble.clear();
                return;
            }
    qDebug() << "File not created";
    exit(-1);
}

void MainWindow::generateArray(std::vector<double> &arr, unsigned const int size)
{
    arr.clear();
    arr.reserve(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<>dis(0, 100);
    for (unsigned int i = 0; i < size; ++i)
        try
        {
            arr.push_back(dis(gen));
        } catch(std::bad_alloc &thebadallocation)
        {
            qDebug() << "Bad memory allocate in function generateArray(double, size)";
            exit(-1);
        };
    qDebug() << "array generated";
}

void MainWindow::runTimer()
{
//    TimeManager tManager;
//    tManager.start();
//    while(true)
//    {
//        tManager.getTime();
//        double time = tManager.getAlgTime();
//        if(time >= 50000)
//        {
//            stopThreadFlag = true;
//            qDebug() << "Algorithm too slow";
//            tManager.stop();
//            return;
//        }
//        if(stopTimerFlag)
//        {
//            stopTimerFlag = false;
//            tManager.stop();
//            return;
//        }
//    }
    return;
}

template <class T>
void MainWindow::printArray(std::vector<T> &arr)
{
    if(arr.size() >= _size[4])
    {
        qDebug() << "Array too big for output";
        qDebug() << "First ellement of arr is " << arr[0] << " and last: " << arr[arr.size()-1];
        return;
    }
    QString str;
    for(auto arrEl : arr)
    {
        str = QString::number(arrEl) + ' ';
        ui->textOutput->append(str);
    }
}

void MainWindow::generateArray(std::vector<int> &arr, unsigned const int size)
{
    arr.clear();
    arr.reserve(size);
    srand(time(NULL));
    for(unsigned int i = 0; i < size; ++i)
        try
        {
            arr.push_back(rand()%200 + 1);
        }catch(std::bad_alloc &theBadAllocation)
        {
            qDebug() << "Bad memory allocate in function generateArray(int, size)";
            exit(-1);
        };
    qDebug() << "array generated";
}

template <class T>
void MainWindow::saveArrayToFile(std::vector<T> &arr)
{
    QFile hFile("arr.dat");
    if (!hFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Error in opening file arr.dat";
        return;
    }

    QTextStream out(&hFile);
    for(auto arrEl : arr)
    {
        out << arrEl << " ";
    }
    hFile.close();
    qDebug() << "Array saved to file";
}

template <class T>
void MainWindow::readArrayFromFile(std::vector<T> &arr)
{
    arr.clear();
    arr.reserve(_size[_currentSizeIndex]);
    QFile hFile("arr.dat");
    if (!hFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error in opening file arr.dat";
        return;
    }
    QTextStream in(&hFile);
    while(!in.atEnd())
    {
        T i ;
        in >> i;
        arr.push_back(i);
    }
    arr.pop_back();
}

void MainWindow::on_comboBoxSizeIndex_currentIndexChanged(int index)
{
    _currentSizeIndex = index;
}

void MainWindow::saveResultToFile(QString sortName, double time)
{
    QFile hFile("result.dat");
    if (!hFile.open(QIODevice::Append))
    {
        qDebug() << "Error in opening file arr.dat";
        return;
    }
    QTextStream textStream(&hFile);
    std::chrono::time_point<std::chrono::system_clock> currentData;
    currentData = std::chrono::system_clock::now();
    std::time_t date = std::chrono::system_clock::to_time_t(currentData);
    textStream << std::ctime(&date) << "\n";
    if(sortName == "Size")
        textStream << "----\n" << sortName << ": " << QString::number(time/3) << '\n';
    else
        if(sortName == "Simple Bubble" || sortName == "Optimized Bubble" || sortName == "With flag Bubble")
            textStream << "-" << sortName << ": " << QString::number(time/3) << '\n';
        else
            if(sortName == "Selection")
                textStream << "--" << sortName << ": " << QString::number(time/3) << '\n';
            else
                if(sortName == "Shell(Shell sequence)" || sortName == "Shell(Pratt sequence)" || sortName == "Shell(PrattSecond sequence)")
                    textStream << "---" << sortName << ": " << QString::number(time/3) << '\n';
                else
                    if(sortName == "Merge")
                        textStream << "----" << sortName << ": " << QString::number(time/3) << '\n';
                    else
                        if(sortName == "Quick")
                            textStream << "-----" << sortName << ": " << QString::number(time/3) << '\n';
                        else
                            if(sortName == "Counting")
                                textStream << "------" << sortName << ": " << QString::number(time/3) << '\n';
                            else
                                textStream << sortName << ": " << QString::number(time/3) << '\n';
    hFile.close();
}

void MainWindow::sortIntRandom()
{
    QFile hFile("result.dat");
    hFile.open(QIODevice::Append);
    saveResultToFile("\n\n-->Random INT: ", 1);
    for(unsigned int i = 0; i < _size.size(); ++i)
    {
        saveResultToFile("Size", _size[i]*3);
        ui->textOutput->append("Size: " + QString::number(_size[i]));
        prepareArray(i, "int");
        for(unsigned int j = 0; j < _sortInt.size(); ++j)
        {
            if(i < 6) {
                _sortInt[j]();
            }
            else
                if(i < 9 && j > 1)
                    _sortInt[j]();
                else
                    if(j > 4)
                        _sortInt[j]();
        }
    }
    hFile.close();
}

void MainWindow::sortIntSorted()
{
    QFile hFile("result.dat");
    if (!hFile.open(QIODevice::Append))
    {
        qDebug() << "Error in opening file arr.dat";
        return;
    }
    saveResultToFile("\n\n-->Sorted INT: ", 2);
    for(unsigned int i = 0; i < _size.size(); ++i)
    {
        saveResultToFile("Size", _size[i]*3);
        ui->textOutput->append("Size: " + QString::number(_size[i]));
        prepareArray(i, "s int");
        for(unsigned int j = 0; j < _sortInt.size(); ++j)
        {
            if(i < 6) {
                _sortInt[j]();
            }
            else
                if(i < 9 && j > 1)
                    _sortInt[j]();
                else
                    if(j > 4)
                        _sortInt[j]();
        }
    }
    hFile.close();
}

void MainWindow::sortIntReverse()
{
    QFile hFile("result.dat");
    if (!hFile.open(QIODevice::Append))
    {
        qDebug() << "Error in opening file arr.dat";
        return;
    }
    saveResultToFile("\n\n-->Reverse Sorted INT: ", 3);
    for(unsigned int i = 0; i < _size.size(); ++i)
    {
        saveResultToFile("Size", _size[i]*3);
        ui->textOutput->append("Size: " + QString::number(_size[i]));
        prepareArray(i, "r int");
        for(unsigned int j = 0; j < _sortInt.size(); ++j)
        {
            if(i < 6) {
                _sortInt[j]();
            }
            else
                if(i < 9 && j > 1)
                    _sortInt[j]();
                else
                    if(j > 4)
                        _sortInt[j]();
        }
    }
    hFile.close();
}

void MainWindow::sortDoubleRandom()
{
    QFile hFile("result.dat");
    if (!hFile.open(QIODevice::Append))
    {
        qDebug() << "Error in opening file arr.dat";
        return;
    }
    saveResultToFile("\n\n--> Random DOUBLE: ", 1);
    for(unsigned int i = 0; i < _size.size()-1; ++i)
    {
        saveResultToFile("Size", _size[i]*3);
        ui->textOutput->append("Size: " + QString::number(_size[i]));
        prepareArray(i, "double");
        for(unsigned int j = 0; j < _sortDouble.size(); ++j)
        {
            if(i < 6) {
                _sortDouble[j]();
            }
            else
                if(i < 9 && j > 1)
                    _sortDouble[j]();
                else
                    if(j > 4)
                        _sortDouble[j]();
        }
    }
    hFile.close();
}

void MainWindow::sortDoubleSorted()
{
    QFile hFile("result.dat");
    if (!hFile.open(QIODevice::Append))
    {
        qDebug() << "Error in opening file arr.dat";
        return;
    }
    saveResultToFile("\n\n-->Sorted DOUBLE: ", 2);
    for(unsigned int i = 0; i < _size.size()-1; ++i)
    {
        saveResultToFile("Size", _size[i]*3);
        ui->textOutput->append("Size: " + QString::number(_size[i]));
        prepareArray(i, "s double");
        for(unsigned int j = 0; j < _sortDouble.size(); ++j)
        {
            if(i < 6) {
                _sortDouble[j]();
            }
            else
                if(i < 9 && j > 1)
                    _sortDouble[j]();
                else
                    if(j > 4)
                        _sortDouble[j]();
        }
    }
    hFile.close();
}

void MainWindow::sortDoubleReverse()
{
    QFile hFile("result.dat");
    if (!hFile.open(QIODevice::Append))
    {
        qDebug() << "Error in opening file arr.dat";
        return;
    }
    saveResultToFile("\n\n-->Reverse Sorted DOUBLE: ", 3);
    for(unsigned int i = 0; i < _size.size()-1; ++i)
    {
        saveResultToFile("Size", _size[i]*3);
        ui->textOutput->append("Size: " + QString::number(_size[i]));
        prepareArray(i, "r double");
        for(unsigned int j = 0; j < _sortDouble.size(); ++j)
        {
            if(i < 6) {
                _sortDouble[j]();
            }
            else
                if(i < 9 && j > 1)
                    _sortDouble[j]();
                else
                    if(j > 4)
                        _sortDouble[j]();
        }
    }
    hFile.close();
}

void MainWindow::on_comboBoxSelectedSort_currentIndexChanged(int index)
{
    _currentSortIndex = index;
}

void MainWindow::on_pushButtonSort_clicked()
{
    if(_currentSizeIndex == 9 && _currentSortIndex > 2)
        return;
//    if(ui->checkBoxCounting->isChecked() && _currentSortIndex > 2)
//        return;
    if(_currentSortIndex == 0)
        prepareArray(_currentSizeIndex, "int");
    else
        if(_currentSortIndex == 1)
            prepareArray(_currentSizeIndex, "s int");
        else
            if(_currentSortIndex == 2)
                prepareArray(_currentSizeIndex, "r int");
            else
                if(_currentSortIndex == 3)
                    prepareArray(_currentSizeIndex, "double");
                else
                    if(_currentSortIndex == 4)
                        prepareArray(_currentSizeIndex, "s double");
                    else
                        if(_currentSortIndex == 5)
                            prepareArray(_currentSizeIndex, "r double");

    if(ui->checkBoxBubble->isChecked() == true)
    {
        if(_currentSortIndex < 3)
            _sortInt[0]();
        else
            _sortDouble[0]();
    }
    if(ui->checkBoxSelection->isChecked() == true)
    {
        if(_currentSortIndex < 3)
            _sortInt[1]();
        else
            _sortDouble[1]();
    }

    if(ui->checkBoxShell->isChecked() == true)
    {
        if(_currentSortIndex < 3)
        {
            _sortInt[2]();
            _sortInt[3]();
            _sortInt[4]();
        }
        else
        {
            _sortDouble[2]();
            _sortDouble[3]();
            _sortDouble[4]();
        }
    }

    if(ui->checkBoxMerge->isChecked())
    {
        if(_currentSortIndex < 3)
            _sortInt[5]();
        else
            _sortDouble[5]();
    }

    if(ui->checkBoxQuick->isChecked())
    {
        if(_currentSortIndex < 3)
            _sortInt[6]();
        else
            _sortDouble[6]();
    }

    if(ui->checkBoxCounting->isChecked())
    {
        if(_currentSortIndex < 3)
            _sortInt[7]();
        else
            return;
    }
}
