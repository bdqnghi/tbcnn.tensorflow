/*
 * File:
 *   intset.c
 * Author(s):
 *   Pascal Felber <pascal.felber@unine.ch>
 *   Aleksandar Dragojevic <aleksandar.dragojevic@epfl.ch> (added support for wlpdstm)
 * Description:
 *   Integer set stress test.
 *
 * Copyright (c) 2007-2008.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <assert.h>
#include <getopt.h>
#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include "timer.h"
#include "random.h"
#include <time.h>
#include <vector>

#include "tm.h"
#include "thread.h"

#define DEFAULT_DURATION                10000
#define DEFAULT_INITIAL                 256
#define DEFAULT_NB_THREADS              1
#define DEFAULT_RANGE                   0xFFFF
#define DEFAULT_SEED                    0
#define DEFAULT_UPDATE                  20
#define DEFAULT_REPEAT                  1
#define DEFAULT_ACCESSES_PER_OPERATION              1
#define DEFAULT_COMBINATION              0
#define DEFAULT_ALPHA 1.0

#define XSTR(s)                         STR(s)
#define STR(s)                          #s

#define  FALSE          0       // Boolean false
#define  TRUE           1       // Boolean true

#define CHANGINGWORKLOAD
#ifdef CHANGINGWORKLOAD
std::vector<double> combinations;
#endif

/* ################################################################### *
 * GLOBALS
 * ################################################################### */

static volatile int stop;

#include "rbtree.h"
#include "rbtree-htm.h"

typedef rbtree_t intset_t;

intset_t *set_new()
{
  return rbtree_htm::rbtree_alloc();
}

void set_delete(intset_t *set)
{
  rbtree_htm::rbtree_free(set);
}

int set_add_seq(intset_t *set, intptr_t val) {
    return !rbtree_htm::rbtree_insert(set, val, val);
}

int set_add(TM_ARGDECL  intset_t *set, intptr_t val)
{
    int res = 0;

    res = rbtree_htm::TMrbtree_insert(TM_ARG set, val, val);

    return res;
}

int set_remove(TM_ARGDECL intset_t *set, intptr_t val)
{
    int res = 0;

    res = rbtree_htm::TMrbtree_delete(TM_ARG set, val);

    return res;
}

int set_contains(TM_ARGDECL  intset_t *set, intptr_t val)
{
    int res = 0;

    res = rbtree_htm::TMrbtree_contains(TM_ARG set, val);

    return res;
}

/* ################################################################### *
 * STRESS TEST
 * ################################################################### */

  int range;
  int update;
  unsigned long nb_add;
  unsigned long nb_remove;
  unsigned long nb_contains;
  unsigned long nb_found;
  unsigned long nb_aborts;
  unsigned int nb_threads;
  int diff;
  unsigned int seed;
  unsigned int operations;
  unsigned int accessesPerOperations;
  unsigned int combinationsValue;
  double alpha_value;
  intset_t *set;



void test(void *data)
{
  int val;

  TM_THREAD_ENTER();

  unsigned int mySeed = seed;
  int myDiff = diff;
  random_t* randomPtr = random_alloc();

  long myOps = operations / nb_threads;

  int transactionsLeft = -1;

  while (myOps > 0) {


      long pruned_range = ((long)(range*alpha_value));

      int ro = 0;
      int access;
      for (access = 0; access < accessesPerOperations; access++) {
          val = random_generate(randomPtr) % 100;
          if (val < update) {
              if (val < update / 2) {
                  /* Add random value */
                  val = (random_generate(randomPtr) % pruned_range) + 1;
		  ro = 0;
		  TM_BEGIN(0);
                  set_add(TM_ARG set, val);
		  TM_END();;
              } else {
                  /* Remove random value */
                  val = (random_generate(randomPtr) % pruned_range) + 1;
		  ro = 0;
                  TM_BEGIN(1);
                  set_remove(TM_ARG set, val);
		  TM_END();
              }
          } else {
              /* Look for random value */
              long tmp = (random_generate(randomPtr) % pruned_range) + 1;
	      ro = 1;
	      TM_BEGIN_EXT(2,1);
              set_contains(TM_ARG set, tmp);
	      TM_END();
          }

      }
      myOps -= accessesPerOperations;

  }

  TM_THREAD_EXIT();

}


# define no_argument        0
# define required_argument  1
# define optional_argument  2

MAIN(argc, argv) {
    TIMER_T start;
    TIMER_T stop;

    SETUP_NUMBER_TASKS(3);

  struct option long_options[] = {
    // These options don't set a flag
    {"help",                      no_argument,       NULL, 'h'},
    {"duration",                  required_argument, NULL, 'd'},
    {"initial-size",              required_argument, NULL, 'i'},
    {"num-threads",               required_argument, NULL, 'n'},
    {"range",                     required_argument, NULL, 'r'},
    {"seed",                      required_argument, NULL, 's'},
    {"update-rate",               required_argument, NULL, 'u'},
    {"attempts-before-fallback",  optional_argument, NULL, 'f'},
    {"attempts-apriori-locks",    optional_argument, NULL, 'p'},
    {"repeats",                   optional_argument, NULL, 'a'},
    {"zipfian-alpha-param",       optional_argument, NULL, 'z'},
    {"accesses-per-op",           optional_argument, NULL, 'o'},
    {NULL, 0, NULL, 0}
  };

  int i, c, val;
  operations = DEFAULT_DURATION;
  unsigned int initial = DEFAULT_INITIAL;
  nb_threads = DEFAULT_NB_THREADS;
  range = DEFAULT_RANGE;
  update = DEFAULT_UPDATE;
  int attempts = DEFAULT_REPEAT;
  accessesPerOperations = DEFAULT_ACCESSES_PER_OPERATION;
  alpha_value = DEFAULT_ALPHA;

  SETUP_NUMBER_THREADS(nb_threads);

  while(1) {
    i = 0;
    c = getopt_long(argc, argv, "hd:i:n:r:s:u:f:p:a:o:c:z:", long_options, &i);

    if(c == -1)
      break;

    if(c == 0 && long_options[i].flag == 0)
      c = long_options[i].val;

    switch(c) {
     case 0:
       /* Flag is automatically set */
       break;
     case 'h':
       printf("intset -- STM stress test "
              "(red-black tree)\n"
              "\n"
              "Usage:\n"
              "  intset [options...]\n"
              "\n"
              "Options:\n"
              "  -h, --help\n"
              "        Print this message\n"
              "  -d, --duration <int>\n"
              "        Test duration in milliseconds (0=infinite, default=" XSTR(DEFAULT_DURATION) ")\n"
              "  -i, --initial-size <int>\n"
              "        Number of elements to insert before test (default=" XSTR(DEFAULT_INITIAL) ")\n"
              "  -n, --num-threads <int>\n"
              "        Number of threads (default=" XSTR(DEFAULT_NB_THREADS) ")\n"
              "  -r, --range <int>\n"
              "        Range of integer values inserted in set (default=" XSTR(DEFAULT_RANGE) ")\n"
              "  -s, --seed <int>\n"
              "        RNG seed (0=time-based, default=" XSTR(DEFAULT_SEED) ")\n"
              "  -u, --update-rate <int>\n"
              "        Percentage of update transactions (default=" XSTR(DEFAULT_UPDATE) ")\n"
         );
       exit(0);
     case 'a':
       attempts = atoi(optarg);
       break;
     case 'd':
       operations = atoi(optarg);
       break;
     case 'i':
       initial = atoi(optarg);
       break;
     case 'n':
       nb_threads = atoi(optarg);
       break;
     case 'r':
       range = atoi(optarg);
       break;
     case 's':
       seed = atoi(optarg);
       break;
     case 'z':
       alpha_value = atof(optarg);
       break;
     case 'u':
       update = atoi(optarg);
       break;
     case 'o':
       accessesPerOperations = atoi(optarg);
       break;
     case '?':
       printf("Use -h or --help for help\n");
       exit(0);
     default:
       exit(1);
    }
  }

  if (seed == 0)
    srand((int)time(0));
  else
    srand(seed);

printf("range after alpha: %ld\n", (long)(range*alpha_value));

  /* Init STM */
  SIM_GET_NUM_CPU(nb_threads);
  TM_STARTUP(nb_threads, RBT_ID);
  P_MEMORY_STARTUP(nb_threads);
  thread_startup(nb_threads);

double time_total = 0.0;
double energy_total = 0.0;
for (; attempts > 0; --attempts) {

  set = set_new();

  /* Populate set */
  for (i = 0; i < initial; i++) {
    val = (rand() % range) + 1;
    set_add_seq(set, val);
  }

  diff = 0;
  seed = rand();
  TIMER_READ(start);
  GOTO_SIM();

  thread_start(test, NULL);

  GOTO_REAL();
  TIMER_READ(stop);
double time_tmp = TIMER_DIFF_SECONDS(start, stop);
PRINT_STATS();
time_total += time_tmp;

}

  printf("Time = %0.6lf\n", time_total);

  TM_SHUTDOWN();
  P_MEMORY_SHUTDOWN();
  GOTO_SIM();
  thread_shutdown();
  MAIN_RETURN(0);

}
