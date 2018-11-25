


#include <gecode/support.hh>

#ifdef GECODE_HAS_THREADS

#include <gecode/search/parallel/dfs.hh>

namespace Gecode { namespace Search { namespace Parallel {

  
  Statistics 
  DFS::statistics(void) const {
    Statistics s;
    for (unsigned int i=0; i<workers(); i++)
      s += worker(i)->statistics();
    return s;
  }


  
  void
  DFS::Worker::run(void) {
    
    if (this != engine().worker(0))
      Support::Thread::sleep(Config::initial_delay);
    
    while (true) {
      switch (engine().cmd()) {
      case C_WAIT:
        
        engine().wait();
        break;
      case C_TERMINATE:
        
        engine().ack_terminate();
        
        engine().wait_terminate();
        
        engine().terminated();
        return;
      case C_RESET:
        
        engine().ack_reset_start();
        
        engine().wait_reset();
        
        engine().ack_reset_stop();
        break;
      case C_WORK:
        
        {
          m.acquire();
          if (idle) {
            m.release();
            
            find();
          } else if (cur != NULL) {
            start();
            if (stop(engine().opt(),path.size())) {
              
              m.release();
              engine().stop();
            } else {
              node++;
              switch (cur->status(*this)) {
              case SS_FAILED:
                fail++;
                delete cur;
                cur = NULL;
                Worker::current(NULL);
                m.release();
                break;
              case SS_SOLVED:
                {
                  
                  (void) cur->choice();
                  Space* s = cur->clone(false);
                  delete cur;
                  cur = NULL;
                  Worker::current(NULL);
                  m.release();
                  engine().solution(s);
                }
                break;
              case SS_BRANCH:
                {
                  Space* c;
                  if ((d == 0) || (d >= engine().opt().c_d)) {
                    c = cur->clone();
                    d = 1;
                  } else {
                    c = NULL;
                    d++;
                  }
                  const Choice* ch = path.push(*this,cur,c);
                  Worker::push(c,ch);
                  cur->commit(*ch,0);
                  m.release();
                }
                break;
              default:
                GECODE_NEVER;
              }
            }
          } else if (path.next(*this)) {
            cur = path.recompute(d,engine().opt().a_d,*this);
            Worker::current(cur);
            m.release();
          } else {
            idle = true;
            m.release();
            
            engine().idle();
          }
        }
        break;
      default:
        GECODE_NEVER;
      }
    }
  }


  
  DFS::~DFS(void) {
    terminate();
    heap.rfree(_worker);
  }

}}}

#endif


