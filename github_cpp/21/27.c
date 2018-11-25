

#include "datasort.h"
#include "ui_datasort.h"


DataSort::DataSort(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DataSort)
{
    ui->setupUi(this);

    
    ui->dataTable->setVisible(false);
    setSortStatusVisibility(false);
    ui->result1->setVisible(false);
    ui->result2->setVisible(false);
    ui->result3->setVisible(false);

    
    connect(ui->dataTable->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(headerClicked(int)));
}

DataSort::~DataSort()
{
    if (quickSort != nullptr) {
        disconnect(quickSort, SIGNAL(done(int)), this, SLOT(onSortingDone(int)));
        disconnect(quickSort, SIGNAL(progress(int, int)), this, SLOT(onProgress(int, int)));
        delete quickSort;
    }
    if (mergeSort != nullptr) {
        disconnect(mergeSort, SIGNAL(done(int)), this, SLOT(onSortingDone(int)));
        disconnect(mergeSort, SIGNAL(progress(int, int)), this, SLOT(onProgress(int, int)));
        delete mergeSort;
    }
    if (selectionSort != nullptr) {
        disconnect(selectionSort, SIGNAL(done(int)), this, SLOT(onSortingDone(int)));
        disconnect(selectionSort, SIGNAL(progress(int, int)), this, SLOT(onProgress(int, int)));
        delete selectionSort;
    }
    delete ui;
}


void DataSort::headerClicked(int index){
    if(index == sortColumn){
        ascending = !ascending;
    } else {
        ascending = true;
        sortColumn = index;
    }
    sort();
}



QString DataSort::compareTime(double timeA, double timeB, double timeC) {
    if (timeA < timeB && timeA < timeC) {
        return " seconds (fastest), ";
    } else if (timeA > timeB && timeA > timeC) {
        return " seconds (slowest), ";
    } else {
        return " seconds (second), ";
    }
}



void DataSort::profilingResults(){
    
    double quickSortTime = quickSort->getDuration();
    double mergeSortTime = mergeSort->getDuration();
    double selectionSortTime = selectionSort->getDuration();

    
    QString quickSortResult, mergeSortResult, selectionSortResult;
    quickSortResult = "Quick Sort: duration: ";
    quickSortResult += QString::number(quickSortTime);
    quickSortResult += compareTime(quickSortTime, mergeSortTime, selectionSortTime);
    quickSortResult += " comparisons made: ";
    quickSortResult += QString::number(quickSort->getComparisons());
    ui->result1->setText(quickSortResult);
    ui->result1->setVisible(true);

    mergeSortResult = "Merge Sort: duration: ";
    mergeSortResult += QString::number(mergeSortTime);
    mergeSortResult += compareTime(mergeSortTime, quickSortTime, selectionSortTime);
    mergeSortResult += " comparisons made: ";
    mergeSortResult += QString::number(mergeSort->getComparisons());
    ui->result2->setText(mergeSortResult);
    ui->result2->setVisible(true);

    selectionSortResult = "Selection Sort: duration: ";
    selectionSortResult += QString::number(selectionSortTime);
    selectionSortResult += compareTime(selectionSortTime, quickSortTime, mergeSortTime);
    selectionSortResult += " comparisons made: ";
    selectionSortResult += QString::number(selectionSort->getComparisons());
    ui->result3->setText(selectionSortResult);
    ui->result3->setVisible(true);
}




void DataSort::onSortingDone(int algorithm){
    
    if(algorithm == Sort::QUICK_SORT) {
        quickSortDone = true;
        ui->quickSortProgress->setValue(100);
    } else if(algorithm == Sort::MERGE_SORT) {
        mergeSortDone = true;
        ui->mergeSortProgress->setValue(100);
    } else if(algorithm == Sort::SELECTION_SORT) {
        selectionSortDone = true;
        ui->selectionSortProgress->setValue(100);
    
    } else if(algorithm == Sort::CANCELLED) {
        cancelled = true;
        setSortStatusVisibility(false);
    }
    
    if (quickSortDone && mergeSortDone && selectionSortDone) {
        setSortStatusVisibility(false);
        
        if (!cancelled) {
            arr = quickSort->getSortedArray();
            profilingResults();
        }
        
        if (tableManager != nullptr) {
            disconnect(tableManager, SIGNAL(done()), this, SLOT(onTableDone()));
            delete tableManager;
        }
        tableManager = new TableManager(this, arr, ui->dataTable);
        
        connect(tableManager, SIGNAL(done()), this, SLOT(onTableDone()));
        tableManager->run();
    }
}




void DataSort::onTableDone() {
    
    ui->dataTable->setVisible(true);
}




void DataSort::sort(){
    
    ui->quickSortProgress->setValue(0);
    ui->mergeSortProgress->setValue(0);
    ui->selectionSortProgress->setValue(0);
    
    setSortStatusVisibility(true);
    
    ui->result1->setVisible(false);
    ui->result2->setVisible(false);
    ui->result3->setVisible(false);

    
    if (quickSort != nullptr) {
        disconnect(quickSort, SIGNAL(done(int)), this, SLOT(onSortingDone(int)));
        disconnect(quickSort, SIGNAL(progress(int, int)), this, SLOT(onProgress(int, int)));
        delete quickSort;
    }
    if (mergeSort != nullptr) {
        disconnect(mergeSort, SIGNAL(done(int)), this, SLOT(onSortingDone(int)));
        disconnect(mergeSort, SIGNAL(progress(int, int)), this, SLOT(onProgress(int, int)));
        delete mergeSort;
    }
    if (selectionSort != nullptr) {
        disconnect(selectionSort, SIGNAL(done(int)), this, SLOT(onSortingDone(int)));
        disconnect(selectionSort, SIGNAL(progress(int, int)), this, SLOT(onProgress(int, int)));
        delete selectionSort;
    }
    
    quickSortDone = false;
    mergeSortDone = false;
    selectionSortDone = false;
    cancelled = false;

    
    quickSort = new Sort(this, Sort::QUICK_SORT, arr, sortColumn, ascending);
    connect(quickSort, SIGNAL(done(int)), this, SLOT(onSortingDone(int)));
    connect(quickSort, SIGNAL(progress(int, int)), this, SLOT(onProgress(int, int)));
    quickSort->setComparisonPenalty(comparisonPenalty);
    quickSort->start();

    
    mergeSort = new Sort(this, Sort::MERGE_SORT, arr, sortColumn, ascending);
    connect(mergeSort, SIGNAL(done(int)), this, SLOT(onSortingDone(int)));
    connect(mergeSort, SIGNAL(progress(int, int)), this, SLOT(onProgress(int, int)));
    mergeSort->setComparisonPenalty(comparisonPenalty);
    mergeSort->start();

    
    selectionSort = new Sort(this, Sort::SELECTION_SORT, arr, sortColumn, ascending);
    connect(selectionSort, SIGNAL(done(int)), this, SLOT(onSortingDone(int)));
    connect(selectionSort, SIGNAL(progress(int, int)), this, SLOT(onProgress(int, int)));
    selectionSort->setComparisonPenalty(comparisonPenalty);
    selectionSort->start();
}


void DataSort::setSortStatusVisibility(bool visible)
{
    ui->cancelButton->setVisible(visible);
    ui->quickSortLabel->setVisible(visible);
    ui->quickSortProgress->setVisible(visible);
    ui->mergeSortLabel->setVisible(visible);
    ui->mergeSortProgress->setVisible(visible);
    ui->selectionSortLabel->setVisible(visible);
    ui->selectionSortProgress->setVisible(visible);
}


void DataSort::on_actionOpen_triggered()
{
    
    sortColumn = 0;
    ascending = true;
    
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file");
    
    QFile file(fileName);
    
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    
    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    
    if(doc.isArray()){
        arr = doc.array();
        
        ui->infoLabel->setVisible(false);
        
        sort();
    } else {
        QMessageBox::warning(this, "Warning", "JSON Document expected. Contents should be an array of objects.");
    }
    file.close();
}


void DataSort::on_cancelButton_clicked()
{
    quickSort->stop();
    mergeSort->stop();
    selectionSort->stop();
}


void DataSort::on_actionExit_triggered()
{
    QApplication::quit();
}


void DataSort::onProgress(int algorithm, int progress)
{
    
    if (progress > 99) {
        progress = 99;
    } else if (progress < 0) {
        progress = 0;
    }
    
    if (algorithm == Sort::SELECTION_SORT) {
        ui->selectionSortProgress->setValue(progress);
    } else if (algorithm == Sort::QUICK_SORT) {
        ui->quickSortProgress->setValue(progress);
    } else if (algorithm == Sort::MERGE_SORT) {
        ui->mergeSortProgress->setValue(progress);
    }
}


void DataSort::on_spinBox_valueChanged(int value)
{
    comparisonPenalty = static_cast<unsigned long>(value);
}


void DataSort::on_actionSave_as_triggered()
{
    
    QString fileName = QFileDialog::getSaveFileName(this, "Save as...");
    QFile file(fileName);
    
    if(!file.open(QFile::WriteOnly)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    
    QJsonDocument toSave(arr);
    file.write(toSave.toJson());
    file.close();
}
