#include "skipList.hpp"

skipList::skipList() {
  this->prob = 0.5;
  this->maxLevel = 16;
  int key = std::numeric_limits<int>::min();
  head = new Node(key, "head", maxLevel);

  key = std::numeric_limits<int>::max();
  NIL = new Node(key, "NIL", maxLevel);

  for(unsigned int i = 0; i < maxLevel; i++) {
    head->_next[i] = NIL;
  }
  //std::cout << "Created" << std::endl;
  _height = 0;
  _lastFind = 0;
  _totalSearchCost = 0;
}

skipList::skipList(double probability) {
  this->prob = probability;
  this->maxLevel = 16;
  int key = std::numeric_limits<int>::min();
  head = new Node(key, "head", maxLevel);

  key = std::numeric_limits<int>::max();
  NIL = new Node(key, "NIL", maxLevel);

  for(unsigned int i = 0; i < maxLevel; i++) {
    head->_next[i] = NIL;
  }
  //std::cout << "Created" << std::endl;
  _height = 0;
  _lastFind = 0;
  _totalSearchCost = 0;
}

Node::Node(int k, const std::string& v, int level) {
  key = k;
  value = v;
  for(unsigned int i = 0; i< level; ++i)
    _next.emplace_back(nullptr);
}

skipList::~skipList() {
  //MEMORY IS FREE! :D
  //But leakage problem is real :(
}


int skipList::getLevel( std::vector<Node*>& x ) {
  int aux = 0;
  int max = std::numeric_limits<int>::max();

  //We are in NIL status
  if (x[0]->key == max) {
    return aux;
  }

  int result;
  for (unsigned int i = 0; i < x.size(); ++i) {
    if (x[i] != nullptr && x[i]->key != max){
      ++aux;
    }else{
      break;
    }
  }
  return aux;
}

void skipList::print() {
  std::cout << "==========" << std::endl;
  std::cout << "Printing information about skip list" << std::endl;
  std::cout << "Probability: " << this->prob << " Max Level: " \
    << this->maxLevel << std::endl;


  Node* list = head;

  std::cout << "HEAD address: " << &head << std::endl;
  std::cout << "NIL address: " << &NIL << std::endl;


  std::cout << "===HEAD INFORMATION===" << std::endl;
  for(unsigned int i = 0; i < maxLevel; i++) {
    //std::cout << "Address: " << &head->_next[i] << std::endl;
    //std::cout << "Position: " << i << std::endl;
    if ( head->_next[i] != nullptr && head->_next[i]->key != std::numeric_limits<int>::max() ) {
      std::cout << "Key: " << head->_next[i]->key \
        << " value: " << head->_next[i]->value \
        << " level: " << i \
        << std::endl;
        //<< " level: " << getLevel(head->_next)
    }
  }


  //std::cout << "===SECOND INFORMATION===" << std::endl;

  //Node* aux = head->_next[0];
  //for(unsigned int i = 0; i < maxLevel; i++) {
    //std::cout << "Position: " << i << std::endl;
    //std::cout << "Address: " << &aux->_next[i] << std::endl;
    //if ( aux->_next[i] != nullptr ) {
      //std::cout << "Key: " << aux->_next[i]->key \
        //<< " value: " << aux->_next[i]->value \
        //<< " level: " << getLevel(aux->_next) \
        //<< std::endl;
    //}
  //}

  std::cout << "===PRINT AS A VECTOR===" << std::endl;
  while (list->_next[0] != nullptr) {
    std::cout << "Address: " << &list->_next[0] << std::endl;
    std::cout << "Key: " << list->_next[0]->key \
      << " value: " << list->_next[0]->value \
      << " level: " << getLevel(list->_next) \
      << std::endl;

    list = list->_next[0];

  }





  std::cout << "==========" << std::endl;

}


void skipList::insert (int key, std::string v) {
  //std::cout << "Inserting Key: " << key << " with value: " << v << std::endl;
  int actualLevel = getLevel(head->_next);
  std::vector<Node*> to_update(head->_next);

  Node* x = head;

  //for (int i = actualLevel; i > 0; i--) {
    //while( x->_next[i] != nullptr && x->_next[i]->key < key) {
      //x = x->_next[i];
    //}
    //to_update[i] = x;
  //}
  //x = x->_next[0];

  //if (x->_next[0] == nullptr || x->_next[0]->key != key) {
    ////Create node
    //int newLevel = randomLevel();
    //int height = getLevel(to_update);
    //if ( newLevel > height ) {
      //for( int i = height+1; i <= newLevel; ++i) {
        //to_update[i] = head;
      //}
    //}
    //x = new Node(key,v,newLevel);
    //for ( int i = 0; i < newLevel; ++i) {
      //x->_next[i] = to_update[i]->_next[i];
      //to_update[i]->_next[i] = x;
    //}
  //} else {
    //x->_next[0]->value = v;
  //}


  int l = actualLevel;
  while ( l>=0 ){
    if (x->_next[l] == nullptr || key <= x->_next[l]->key){
      to_update[l] = x;
      --l;
    }
    else {
      x = x->_next[l];
    }
  }

  if ( x->_next[0] == nullptr || x->_next[0]->key != key) {
   int level = randomLevel();
   int height = getLevel(to_update);
   if ( level > height ) {
     for (unsigned int i = height; i < level - 1; ++i) {
      to_update[i] = head;
     }
   }
   x = new Node(key, v, level);

    for (unsigned i = 0; i < level; ++i) {
      x->_next[i] = to_update[i]->_next[i];
      to_update[i]->_next[i] = x;
    }
  }
  else {
    x->_next[0]->value = v;
  }

  return;
}

void skipList::remove (int key) {
  //std::cout << "Removing Key: " << key << std::endl;
  int actualLevel = getLevel(head->_next);
  std::vector<Node*> to_update(head->_next);

  Node* x = head;

  int l = actualLevel;
  while ( l>=0 ){
    if (x->_next[l] == nullptr || key <= x->_next[l]->key){
      to_update[l] = x;
      --l;
    }
    else {
      x = x->_next[l];
    }
  }
  x = x->_next[0];

  if ( x == nullptr) {
    //we did something wrong
    std::cout << "Removing a nullptr" << std::endl;
    return; //we like return in voids
  }

  if (x->key == key) {
    int height = getLevel(x->_next);
    for (int i = 0; i <= to_update.size(); i++) {
      if( to_update[i]->_next[i] != x)
        break;

      to_update[i]->_next[i] = x->_next[i];
    }
    delete x;

  }

}

std::string skipList::find(int key) {
  //timespec start,end;
  timeval start,end;
  gettimeofday(&start,NULL);
  //clock_gettime(CLOCK_REALTIME, &start);
  //std::cout << "Searching Key: " << key << std::endl;
  int actualLevel = getLevel(head->_next);
  std::vector<Node*> to_update(head->_next);

  Node* x = head;

  int l = actualLevel;
  while ( l>=0 ){
    if (x->_next[l] == nullptr || key <= x->_next[l]->key){
      to_update[l] = x;
      --l;
    }
    else {
      x = x->_next[l];
    }
  }
  x = x->_next[0];



  std::string result;
  if ( x == nullptr) {
    //we did something wrong
    std::cout << "Searching in a nullptr :D" << std::endl;
    result = "";
  }

  if (x->key == key) {
    result = x->value;
  } else {
    result = "";
  }

  gettimeofday(&end,NULL);
  this->_lastFind = (end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec);
  //printf("%lld.%.9ld\n", (long long)start.tv_sec, start.tv_usec);
  //printf("%lld.%.9ld\n", (long long)end.tv_sec, end.tv_usec);
  this->_totalSearchCost += this->_lastFind;

  return result;
}

bool skipList::contains (int key) {
  //std::cout << "Searching Key: " << key << std::endl;
  int actualLevel = getLevel(head->_next);
  std::vector<Node*> to_update(head->_next);

  Node* x = head;

  int l = actualLevel;
  while ( l>=0 ){
    if (x->_next[l] == nullptr || key <= x->_next[l]->key){
      to_update[l] = x;
      --l;
    }
    else {
      x = x->_next[l];
    }
  }
  x = x->_next[0];

  if ( x == nullptr) {
    //we did something wrong
    std::cout << "Searching in a nullptr :D" << std::endl;
    return false;
  }

  if (x->key == key) {
    return true;
  } else {
    return false;
  }
  return true;
}

int skipList::number_pointers() {
  Node* list = head;
  //std::cout << "Counting pointers" << std::endl;

  //Initialize to 1 because of the HEAD pointer needed to have referenced
  // the skip list, even empty, we need it
  int total_pointers = 1;
  while (list->_next[0] != nullptr) {
    total_pointers += getLevel(list->_next);

    list = list->_next[0];
  }
  return total_pointers;

}

long long skipList::total_search_cost(){
  return this->_totalSearchCost;
}

//PRIVATE
int skipList::randomLevel() {
  //std::cout << "randomLevel generator" << std::endl;
  //int aux = 1;
  //srand ((unsigned)time(NULL));
  //bool cond = ((double)std::rand() / RAND_MAX) < this->prob;
  ////while (cond || (aux < maxLevel - 1) ) {
    ////++aux;
    ////cond = ((double) std::rand() / RAND_MAX) < this->prob;
  ////}
  //while ((((double)std::rand() / RAND_MAX)) < prob && std::abs(aux) < maxLevel)
    //++aux;

  int aux = 1;
  std::random_device rd;
  std::default_random_engine rng(rd());
  std::uniform_real_distribution<float> uniform_dist(0,1);
  float random = uniform_dist(rng);
  bool cond = random < this->prob;
  while ( cond && std::abs(aux) < maxLevel ) {
    random = uniform_dist(rng);
    cond = random < this->prob;
    ++aux;
  }
  //std::cout << "RANDOM LEVEL: " << aux << std::endl;
  return aux;
}

