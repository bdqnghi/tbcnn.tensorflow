#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>
#include "LRUCache.h"
#include <vector>


#define HANDLE_ERROR(msg) \
do{ fprintf(stderr, "%s fail.\n", msg); exit(-1); } while (0)


#define LRUCACHE_PUTDATA(cache,data) \
do {\
if (0 != LRUCacheSet(cache, data, data)) \
	fprintf(stderr, "put(%c,%c) to cache fail.\n", data, data);\
} while (0)

#define LRUCACHE_GETDATA(cache, key) \
do{\
	char data = LRUCacheGet(cache, key);\
	if ('\0' == data)\
	fprintf(stderr, "get data (Key:%c) from cache fail.\n", key);\
} while (0)


void testcase1(void) {
	fprintf(stdout, "===============================\n");
	fprintf(stdout, "In testcase1....\n");
	fprintf(stdout, "================================\n");
	void *lruCache;
	if (0 != LRUCacheCreate(5, &lruCache))
		HANDLE_ERROR("LARUCacheCreate");
	
	LRUCACHE_PUTDATA(lruCache, 'A');
	LRUCACHE_GETDATA(lruCache, 'A');
	LRUCACHE_PUTDATA(lruCache, 'B');
	LRUCACHE_GETDATA(lruCache, 'B');
	LRUCACHE_PUTDATA(lruCache, 'C');
	LRUCACHE_GETDATA(lruCache, 'C');
	LRUCachePrint(lruCache);

	
	LRUCACHE_PUTDATA(lruCache, 'D');
	LRUCACHE_GETDATA(lruCache, 'D');
	LRUCACHE_PUTDATA(lruCache, 'E');
	LRUCACHE_GETDATA(lruCache, 'E');
	LRUCACHE_PUTDATA(lruCache, 'A');
	LRUCACHE_GETDATA(lruCache, 'A');
	LRUCACHE_PUTDATA(lruCache, 'F');
	LRUCACHE_GETDATA(lruCache, 'F');
	LRUCachePrint(lruCache); 

	
	LRUCACHE_PUTDATA(lruCache, 'B');
	LRUCACHE_GETDATA(lruCache, 'B');
	LRUCachePrint(lruCache); 

	if (0 != LRUCacheDestroy(lruCache))
		HANDLE_ERROR("LRUCacheDestroy");
	fprintf(stdout, "\n\ntestcase1 finished\n");
	fprintf(stdout, "==========================\n\n");
}


void testcase2(void) {
	fprintf(stdout, "=========================\n");
	fprintf(stdout, "In testcase2....\n");
	fprintf(stdout, "=========================\n");
	void *lruCache;
	if (0 != LRUCacheCreate(3, &lruCache))
		HANDLE_ERROR("LRUCacheCreate");

	
	LRUCACHE_PUTDATA(lruCache, 'W');
	LRUCACHE_PUTDATA(lruCache, 'X');
	LRUCACHE_PUTDATA(lruCache, 'W');
	LRUCACHE_PUTDATA(lruCache, 'Y');
	LRUCACHE_PUTDATA(lruCache, 'Z');
	LRUCachePrint(lruCache);

	LRUCACHE_GETDATA(lruCache, 'Z');
	LRUCACHE_GETDATA(lruCache, 'Y');
	LRUCACHE_GETDATA(lruCache, 'W');
	LRUCACHE_GETDATA(lruCache, 'X');
	LRUCACHE_GETDATA(lruCache, 'W');
	LRUCachePrint(lruCache);

	
	LRUCACHE_PUTDATA(lruCache, 'Y');
	LRUCACHE_PUTDATA(lruCache, 'Z');
	LRUCACHE_PUTDATA(lruCache, 'W');
	LRUCACHE_PUTDATA(lruCache, 'Y');
	LRUCACHE_PUTDATA(lruCache, 'X');
	LRUCachePrint(lruCache); 


	LRUCACHE_GETDATA(lruCache, 'X');
	LRUCACHE_GETDATA(lruCache, 'Y');
	LRUCACHE_GETDATA(lruCache, 'W');
	LRUCACHE_GETDATA(lruCache, 'Z');
	LRUCACHE_GETDATA(lruCache, 'Y');
	LRUCachePrint(lruCache); 

	
	LRUCACHE_PUTDATA(lruCache, 'X');
	LRUCACHE_PUTDATA(lruCache, 'Y');
	LRUCACHE_PUTDATA(lruCache, 'X');
	LRUCACHE_PUTDATA(lruCache, 'Y');
	LRUCachePrint(lruCache);

	LRUCACHE_GETDATA(lruCache, 'Y');
	LRUCACHE_GETDATA(lruCache, 'X');
	LRUCACHE_GETDATA(lruCache, 'Y');
	LRUCACHE_GETDATA(lruCache, 'X');
	LRUCachePrint(lruCache); 

	if (0 != LRUCacheDestroy(lruCache))
		HANDLE_ERROR("LRUCacheDestory");
	fprintf(stdout, "\n\ntestcase2 finished\n");
	fprintf(stdout, "=========================\n\n");
}


void testcase3(void)
{
	fprintf(stdout, "=========================\n");
	fprintf(stdout, "In testcase3....\n");
	fprintf(stdout, "=========================\n");

	void *lruCache;
	if (0 != LRUCacheCreate(5, &lruCache))
		HANDLE_ERROR("LRUCacheCreate");

	
	LRUCACHE_PUTDATA(lruCache, 'E');
	LRUCACHE_PUTDATA(lruCache, 'I');
	LRUCACHE_PUTDATA(lruCache, 'E');
	LRUCACHE_PUTDATA(lruCache, 'I');
	LRUCACHE_PUTDATA(lruCache, 'O');
	LRUCachePrint(lruCache);


	LRUCACHE_GETDATA(lruCache, 'A');
	LRUCACHE_GETDATA(lruCache, 'I');
	LRUCACHE_GETDATA(lruCache, 'B');
	LRUCACHE_GETDATA(lruCache, 'O');
	LRUCACHE_GETDATA(lruCache, 'C');
	LRUCACHE_PUTDATA(lruCache, 'E');
	LRUCachePrint(lruCache); 

	if (0 != LRUCacheDestroy(lruCache))
		HANDLE_ERROR("LRUCacheDestory");
	fprintf(stdout, "\n\ntestcase3 finished\n");
	fprintf(stdout, "=========================\n\n");
}

static int a = 0;
HANDLE  mMutex = NULL;

unsigned __stdcall func1(void *pArgument) {
	while (true) {
		WaitForSingleObject(mMutex, INFINITE);
		printf("in func1 now\n");
		a = 2;
		printf("now a is: %d\n", a);
		Sleep(1000);
		ReleaseMutex(mMutex);
	}
	return 0;
}

void testFunc(int m[4]) {
	printf("%d\n", m[0]);
	printf("%d\n", m[1]);
	printf("%d\n", m[2]);
	printf("%d\n", m[3]);
}

int main(int argc, char* argv[]) {
	std::vector<char> a;
	printf("%d", sizeof(a));
	system("pause");
	return 0;
}

