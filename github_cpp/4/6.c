#include "towerofhanoi.h"
#include "ui_towerofhanoi.h"
#include "disk.h"
#include "pole.h"

float scale = 1.0;
Disk *moving = NULL;

TowerOfHanoi::TowerOfHanoi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TowerOfHanoi)
{
    ui->setupUi(this);

    value = ui->spinBox->value();
    poles[0] = new Pole(0, value, ui->pushButton);
    poles[1] = new Pole(1, 0, ui->pushButton_2);
    poles[2] = new Pole(2, 0, ui->pushButton_3);
    ui->spinBox->hide();
    ui->pushButton_4->hide(); 

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(delayedAction()));
    autoplay = false;
}

TowerOfHanoi::~TowerOfHanoi()
{
    delete ui;
    for(int i = 0; i<3; i++) {
        delete poles[i];
    }
    moving = NULL;
    undoStack.clear();
    schedule.clear();
}

void TowerOfHanoi::resizeEvent(QResizeEvent *) {
    scale = qMin(width()/(360.0), height()/(300.0));
    ui->pushButton->resize(scale * 120, scale * 300);
    ui->pushButton_2->resize(scale * 120, scale * 300);
    ui->pushButton_3->resize(scale * 120, scale * 300);

    ui->pushButton_2->move(scale * 120, 0);
    ui->pushButton_3->move(scale * 240, 0);
}

void TowerOfHanoi::CalculateSchedule(int count, int from, int to, int spare) {
    if(count<1) return;
    CalculateSchedule(count-1, from, spare, to);
    schedule.enqueue(Move(from,to));
    CalculateSchedule(count-1, spare, to, from);
}

void TowerOfHanoi::on_pushButton_clicked()
{
    pushButton_clicked(poles[0]);
}

void TowerOfHanoi::on_pushButton_2_clicked()
{
    pushButton_clicked(poles[1]);
}

void TowerOfHanoi::on_pushButton_3_clicked()
{
    pushButton_clicked(poles[2]);
}

void TowerOfHanoi::on_pushButton_4_clicked() 
{
    on_action_New_triggered();
}

void TowerOfHanoi::on_action_New_triggered()
{
    for(int i=0; i<3; i++) {
        delete poles[i];
    }
    if(moving) {
        delete moving;
    }
    moving = NULL;
    undoStack.clear();
    schedule.clear();

    poles[0] = new Pole(0, value, ui->pushButton);
    poles[1] = new Pole(1, 0, ui->pushButton_2);
    poles[2] = new Pole(2, 0, ui->pushButton_3);
    ui->spinBox->hide();
    ui->pushButton_4->hide();
}

void TowerOfHanoi::on_action_Set_Disks_triggered()
{
    ui->spinBox->show();
    ui->pushButton_4->show();
}

void TowerOfHanoi::on_action_Exit_triggered()
{
    close();
}

void TowerOfHanoi::on_action_Undo_triggered()
{
    if(!undoStack.empty()) {
        Move mUndo = undoStack.pop();
        Pole* to = NULL;
        Pole* from = NULL;
        to = poles[mUndo.To()];
        from = poles[mUndo.From()];
        if (moving) {
            moving->On()->put(moving);
            moving = NULL;
        }
        moving = to->take();
        from-> put(moving);
        moving = NULL;
    }
}

void TowerOfHanoi::on_action_Undo_All_triggered()
{
    timer->start(33);
}

void TowerOfHanoi::on_action_Autoplay_triggered()
{
    on_action_New_triggered();
    CalculateSchedule(poles[0]->getNumDisks(), 0, 2, 1);
    timer->start(500);
    autoplay = true;
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->action_Undo->setDisabled(true); 
}

void TowerOfHanoi::on_spinBox_valueChanged(int arg1)
{
    value = arg1;
}

void TowerOfHanoi::delayedAction() {
    if(autoplay) {
        if(!schedule.empty()) {
            Move autom = schedule.dequeue();
            moving = poles[autom.From()]->take();
            poles[autom.To()]->put(moving);
            moving = NULL;
            undoStack.push(autom);
        } else {
            autoplay = false;
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            ui->pushButton_3->setEnabled(true);
            ui->action_Undo->setEnabled(true);
            timer->stop();
        }
    } else {
        if(undoStack.empty()) {
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            ui->pushButton_3->setEnabled(true);
            ui->action_Undo->setEnabled(true);
            timer->stop();
        } else {
            on_action_Undo_triggered();
        }
    }
}

void TowerOfHanoi::pushButton_clicked(Pole *p) {
    if(!moving) {
        moving = p->take();
    } else {
        int from = moving->On()->getIndex();
        if(p->put(moving)) {
            Move mov(from, p->getIndex());
            undoStack.push(mov);
            moving = NULL;
        } else {
            moving->On()->put(moving);
            moving = NULL;
        }
    }
}


