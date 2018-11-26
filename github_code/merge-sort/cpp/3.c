// Dylan McKinney
// 8-26-2018
#include "datasort.h"
#include "ui_datasort.h"

// Initialize main window
DataSort::DataSort(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DataSort)
{
    ui->setupUi(this);

    // Hide table, sort status elements, and profiling results until they are needed
    ui->dataTable->setVisible(false);
    setSortStatusVisibility(false);
    ui->result1->setVisible(false);
    ui->result2->setVisible(false);
    ui->result3->setVisible(false);

    // Receive signal when a table header is clicked to trigger sorting by that column
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

// Called when a table header is clicked to sort data by that column
void DataSort::headerClicked(int index){
    if(index == sortColumn){
        ascending = !ascending;
    } else {
        ascending = true;
        sortColumn = index;
    }
    sort();
}

// Designate a sort procedure as fastest, second, or slowest
// Precondition: sorting procedures have all finished
QString DataSort::compareTime(double timeA, double timeB, double timeC) {
    if (timeA < timeB && timeA < timeC) {
        return " seconds (fastest), ";
    } else if (timeA > timeB && timeA > timeC) {
        return " seconds (slowest), ";
    } else {
        return " seconds (second), ";
    }
}

// Generate results for sort procedures
// Precondition: sorting procedures have all finished
void DataSort::profilingResults(){
    // Collect time data from all procedures
    double quickSortTime = quickSort->getDuration();
    double mergeSortTime = mergeSort->getDuration();
    double selectionSortTime = selectionSort->getDuration();

    // Create QStrings to display on UI using labels
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

// Called when a Sort procedure completes execution
// Precondition: a sorting procedure using the Sort class has been started
// Postcondition: One or more algorithms have finished completion
void DataSort::onSortingDone(int algorithm){
    // Set progress value to 100 and completion bool to true for respective algorithm
    if(algorithm == Sort::QUICK_SORT) {
        quickSortDone = true;
        ui->quickSortProgress->setValue(100);
    } else if(algorithm == Sort::MERGE_SORT) {
        mergeSortDone = true;
        ui->mergeSortProgress->setValue(100);
    } else if(algorithm == Sort::SELECTION_SORT) {
        selectionSortDone = true;
        ui->selectionSortProgress->setValue(100);
    // Handle cancel signal by setting bool cancelled to true and hiding sort status elements
    } else if(algorithm == Sort::CANCELLED) {
        cancelled = true;
        setSortStatusVisibility(false);
    }
    // Check if all three procedures have completed
    if (quickSortDone && mergeSortDone && selectionSortDone) {
        setSortStatusVisibility(false);
        // If sorting wasn't cancelled, gather sorted data and profiling results
        if (!cancelled) {
            arr = quickSort->getSortedArray();
            profilingResults();
        }
        // Create a new TableManager to process the data and present results in the table
        if (tableManager != nullptr) {
            disconnect(tableManager, SIGNAL(done()), this, SLOT(onTableDone()));
            delete tableManager;
        }
        tableManager = new TableManager(this, arr, ui->dataTable);
        // Listen for table generation completion and start the thread.
        connect(tableManager, SIGNAL(done()), this, SLOT(onTableDone()));
        tableManager->run();
    }
}

// Called once the TableManager completes table construction following a sort
// Precondition: a TableManager has been created and started
// Postcondition: QTableWidget generation completed
void DataSort::onTableDone() {
    // Will show the table once data is sorted, if hidden initially
    ui->dataTable->setVisible(true);
}

// Will create 3 Sort objects using different sorting algorithms and run them on independent threads
// Precondition: data has been loaded from a file to be sorted
// Postcondition: sorting procedures have all been started
void DataSort::sort(){
    // Set progress bars for each sort to 0
    ui->quickSortProgress->setValue(0);
    ui->mergeSortProgress->setValue(0);
    ui->selectionSortProgress->setValue(0);
    // Show sort status labels and progress bars during sort
    setSortStatusVisibility(true);
    // Hide profiling results until sorting is completed
    ui->result1->setVisible(false);
    ui->result2->setVisible(false);
    ui->result3->setVisible(false);

    // Ensure new sorting procedures are generated and old references are deleted
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
    // Reset bools for sort status and cancellation to false
    quickSortDone = false;
    mergeSortDone = false;
    selectionSortDone = false;
    cancelled = false;

    // Create and start Quick Sort
    quickSort = new Sort(this, Sort::QUICK_SORT, arr, sortColumn, ascending);
    connect(quickSort, SIGNAL(done(int)), this, SLOT(onSortingDone(int)));
    connect(quickSort, SIGNAL(progress(int, int)), this, SLOT(onProgress(int, int)));
    quickSort->setComparisonPenalty(comparisonPenalty);
    quickSort->start();

    // Create and start Merge Sort
    mergeSort = new Sort(this, Sort::MERGE_SORT, arr, sortColumn, ascending);
    connect(mergeSort, SIGNAL(done(int)), this, SLOT(onSortingDone(int)));
    connect(mergeSort, SIGNAL(progress(int, int)), this, SLOT(onProgress(int, int)));
    mergeSort->setComparisonPenalty(comparisonPenalty);
    mergeSort->start();

    // Create and start Selection Sort
    selectionSort = new Sort(this, Sort::SELECTION_SORT, arr, sortColumn, ascending);
    connect(selectionSort, SIGNAL(done(int)), this, SLOT(onSortingDone(int)));
    connect(selectionSort, SIGNAL(progress(int, int)), this, SLOT(onProgress(int, int)));
    selectionSort->setComparisonPenalty(comparisonPenalty);
    selectionSort->start();
}

// Hide or show all labels and progress bars for sorting procedures
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

// Called when File->Open is pressed in the menu bar
void DataSort::on_actionOpen_triggered()
{
    // Reset sorting details for the new data set
    sortColumn = 0;
    ascending = true;
    // Get the file name of the data set the user wishes to process
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file");
    // Create the file object
    QFile file(fileName);
    // Check for errors
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    // Process file data and store in JSON format for processing
    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    // Ensure that the file meets the requirements for processing. Needs to be an array of JSON objects
    if(doc.isArray()){
        arr = doc.array();
        // Hide the label shown when no file is open
        ui->infoLabel->setVisible(false);
        // Automatically begin processing the data
        sort();
    } else {
        QMessageBox::warning(this, "Warning", "JSON Document expected. Contents should be an array of objects.");
    }
    file.close();
}

// Called when the Cancel Sorting button is pressed during sorting
void DataSort::on_cancelButton_clicked()
{
    quickSort->stop();
    mergeSort->stop();
    selectionSort->stop();
}

// Called when File->Exit is pressed in the menu bar
void DataSort::on_actionExit_triggered()
{
    QApplication::quit();
}

// Called whenever a Sort procedure emits a progress signal
void DataSort::onProgress(int algorithm, int progress)
{
    // Cap progress at 99% unless the algorithm is done
    if (progress > 99) {
        progress = 99;
    } else if (progress < 0) {
        progress = 0;
    }
    // Map progress to the appropriate progress bar
    if (algorithm == Sort::SELECTION_SORT) {
        ui->selectionSortProgress->setValue(progress);
    } else if (algorithm == Sort::QUICK_SORT) {
        ui->quickSortProgress->setValue(progress);
    } else if (algorithm == Sort::MERGE_SORT) {
        ui->mergeSortProgress->setValue(progress);
    }
}

// Called whenever the comparison penalty spinbox value is changed
void DataSort::on_spinBox_valueChanged(int value)
{
    comparisonPenalty = static_cast<unsigned long>(value);
}

// Called when File->Save as is pressed in the menu bar
void DataSort::on_actionSave_as_triggered()
{
    // Select a file to which the data will be saved
    QString fileName = QFileDialog::getSaveFileName(this, "Save as...");
    QFile file(fileName);
    // Check for errors
    if(!file.open(QFile::WriteOnly)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    // Write the current JSON data to the file
    QJsonDocument toSave(arr);
    file.write(toSave.toJson());
    file.close();
}
