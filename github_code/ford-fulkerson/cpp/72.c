#include "fordfulkersonrunner.h"
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <QCoreApplication>
#define INFINITE 99999
#define BLANK -INFINITE
#define TIME_TO_SLEEP 1
FordFulkersonRunner::FordFulkersonRunner(GraphView *view, INFGraph *graph) : QThread()
{
    this->semaphore=new sem_t();
    this->queue=new QSet<Vertex*>();
    this->view=view;
    this->graph=graph;
    sem_init(semaphore, 1, 0);
    this->running=false;
    QObject::connect(this, SIGNAL(ended(double)), this->view, SLOT(endedFlowComputation(double)));
    QObject::connect(this, SIGNAL(repaint()), this->view, SLOT(repaintRequested()));
}
void FordFulkersonRunner::suspend(){
    sem_wait(this->semaphore);
}

bool FordFulkersonRunner::isRunning(){
    return this->running;
}
void FordFulkersonRunner::setGraph(INFGraph *newGraph){
    free(this->graph);
    this->graph=newGraph;

}

void FordFulkersonRunner::step(){
    cout<<"STEP\n\n\n\n\n\n\n\n\n\n"<<endl;
    if(runWhole){
        if(!this->view->fastPlay()){
            emit repaint();
            sleep(TIME_TO_SLEEP);
        }
    }
    else {
        emit repaint();
        sem_wait(this->semaphore);
    }
}
void FordFulkersonRunner::nextStep(){
    cout<<"BEFORE STEP"<<endl;
    sem_post(this->semaphore);
    cout<<"AFTER STEP"<<endl;
}
void FordFulkersonRunner::increaseLabels(GraphElement *elem){
    elem->setLevelLabel(++level_labeling);

}
void FordFulkersonRunner::run(){
    this->runAlgorithm();
    //pthread_t* thread;
    //pthread_create(thread, NULL, FordFulkersonRunner::pthreadRunAlgorithm, this);
}
void * FordFulkersonRunner::pthreadRunAlgorithm(void *param){
    FordFulkersonRunner* instance=(FordFulkersonRunner*)param;
    assert(instance);
    return instance->runAlgorithm();
}

void *FordFulkersonRunner::runAlgorithm(){
    if(FordFulkersonRunner::running){
        cerr<<"AN INSTANCE OF FORD FULKERSON IS ALEADY RUNNING! MULTIPLE INSTANCES ARE NOT ALLOWED!"<<endl;
        throw new exception();
    }
    else {
        running=true; //do not accept other instances
        int pred[this->graph->vertexes.size()];
        double epsilon[this->graph->vertexes.size()];
        double delta=0;
        double flow=0;
        Edge* edge;
        for(unsigned int i=0; i< graph->edges.size(); i++){//initial flow is 0
            edge=graph->edges.at(i);
            edge->tmpLabel->tmpFlow=0;
        }
        do{//main cycle
            cout<<"REFRESHING PRECEDENCE LIST"<<endl;
            for(int i=0; i<graph->vertexes.size(); i++){
                if(i!=graph->source->index){
                    pred[i]=BLANK;
                }
            }
            epsilon[this->graph->source->index]=INFINITE;
            //pred[this->graph->source->index]=this->graph->source->index;
            this->queue->clear();
            this->queue->insert(this->graph->source);
            while(!this->queue->isEmpty() && pred[this->graph->sink->index]==BLANK){
                int selectedIndex=-1;
                for(unsigned int i=0; i<this->graph->vertexes.size(); i++){
                    //if(i!=this->graph->source->index){
                    if(this->queue->contains(this->graph->vertexes.at(i))){
                        selectedIndex=i;
                        if(selectedIndex!=this->graph->sink->index){
                            break;
                        }
                    }
                    //}
                }// selected index is the least index of the vertexes in the queue
                Vertex* selectedVertex=this->graph->vertexes.at(selectedIndex);
                increaseLabels(selectedVertex);
                this->queue->remove(selectedVertex);
                //step();
                Edge* edge;
                for(int i=0; i<selectedVertex->toVertexes.size(); i++){
                    int toIndex=selectedVertex->toVertexes.at(i)->index;
                    edge=this->graph->edges.at(this->graph->edgeIndex(selectedVertex, selectedVertex->toVertexes.at(i)));
                    if(edge->tmpLabel->tmpFlow<edge->tmpLabel->capacity){
                        if(pred[toIndex]==BLANK){
                            epsilon[toIndex]=min(epsilon[selectedIndex], edge->tmpLabel->capacity-edge->tmpLabel->tmpFlow);
                            pred[toIndex]=selectedIndex;
                            this->queue->insert(selectedVertex->toVertexes.at(i));
                            //selectedVertex->toVertexes.at(i)->setLevelLabel(level_labeling);
                            //increaseLabels(edge);
                            //edge->from->setLevelLabel(level_labeling);
                            //edge->to->setLevelLabel(level_labeling);
                            // step();
                        }
                    }
                }
                for(int i=0; i<selectedVertex->fromVertexes.size(); i++){
                    int fromIndex=selectedVertex->fromVertexes.at(i)->index;
                    edge=this->graph->edges.at(this->graph->edgeIndex(selectedVertex->fromVertexes.at(i), selectedVertex));
                    if(edge->tmpLabel->tmpFlow>0){
                        if(pred[fromIndex]==BLANK){
                            epsilon[fromIndex]=min(epsilon[selectedIndex], edge->tmpLabel->tmpFlow);
                            pred[fromIndex]=-selectedIndex;
                            this->queue->insert(selectedVertex->fromVertexes.at(i));
                            //increaseLabels(edge);
                            //edge->from->setLevelLabel(level_labeling);
                            //edge->to->setLevelLabel(level_labeling);
                            // step();
                        }
                    }
                }
            }
            if(pred[this->graph->sink->index]!=BLANK){// found growing path
                cout<<"Precedence Vector: "<<endl;
                for(unsigned int i=0; i<this->graph->vertexes.size(); i++){
                    if(abs(pred[i])>=this->graph->vertexes.size()){
                        cout<<"__";
                    }
                    else {
                        if(pred[i]<0){
                            cout<<"-";
                        }
                        cout<<this->graph->vertexes.at(abs(pred[i]))->name<<", ";
                    }
                }
                cout<<endl;
                delta=epsilon[this->graph->sink->index];
                cout<<"DELTA IS: "<<delta<<endl;
                flow+=delta;
                int predPath=this->graph->sink->index;
                increaseLabels(this->graph->sink);
                int y=0;
                while(predPath!=this->graph->source->index){//updating labels
                    cout<<y++<<endl;
                    cout<<"!!!!! "<<predPath<<": "<<this->graph->vertexes.at(predPath)->name<<" =====> "<<endl;
                    int tmp=pred[predPath];
                    if(tmp>=0){
                        Edge* edge=this->graph->edges.at(this->graph->edgeIndex(this->graph->vertexes.at(tmp), this->graph->vertexes.at(predPath)));
                        edge->tmpLabel->tmpFlow+=delta;
                        edge->setLevelLabel(level_labeling);
                        edge->from->setLevelLabel(level_labeling);
                        edge->to->setLevelLabel(level_labeling);
                    }
                    else {
                        Edge* edge=this->graph->edges.at(this->graph->edgeIndex(this->graph->vertexes.at(predPath), this->graph->vertexes.at(-tmp)));
                        edge->tmpLabel->tmpFlow-=delta;
                        edge->setLevelLabel(level_labeling);
                        edge->from->setLevelLabel(level_labeling);
                        edge->to->setLevelLabel(level_labeling);
                    }
                    predPath=abs(tmp);
                    cout<<"!!!!! ======> "<<predPath<<endl;
                }
                step();
            }
        }
        while(pred[graph->sink->index]!=BLANK);
        //step();
        cout<<"ENDED ALGORITHM"<<endl;
        this->running=false;
        level_labeling=-1;
        for(uint i=0; i<graph->vertexes.size(); i++){
            graph->vertexes.at(i)->setLevelLabel(0);
        }
        for(uint i=0; i<graph->edges.size(); i++){
            graph->edges.at(i)->setLevelLabel(0);
        }
        emit repaint();
        emit ended(flow);
    }
}
void FordFulkersonRunner::setRunWhole(bool whole){
    this->runWhole=whole;
}
