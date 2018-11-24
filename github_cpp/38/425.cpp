#include "stdafx.h"
#include "Queue.h"

CQueue::CQueue() {
	InitializeCriticalSection(&m_csQueue);
	m_hSemophore = CreateSemaphore(NULL, 5, 5, "QueueSemaphore");
}

CQueue::~CQueue() {
	DeleteCriticalSection(&m_csQueue);
	CloseHandle(m_hEvent);
};

void CQueue::PushData( void * queueData )
{
	EnterCriticalSection(&m_csQueue);
	m_objectQueue.push(queueData);
	SetEvent(m_hEvent);
	LeaveCriticalSection(&m_csQueue);
}

void * CQueue::PopData( void )
{
	EnterCriticalSection(&m_csQueue);
	void * popData = m_objectQueue.front();
	m_objectQueue.pop();
	if(!m_objectQueue.size())
		ResetEvent(m_hEvent);

	LeaveCriticalSection(&m_csQueue);
	return popData;
}

HANDLE CQueue::GetEvent( void )
{
		return m_hEvent;
}

DWORD CQueue::GetQueueSize( void )
{
	DWORD dwQueueSize = 0;
	EnterCriticalSection(&m_csQueue);
	dwQueueSize = (DWORD)m_objectQueue.size();
	LeaveCriticalSection(&m_csQueue);

	return dwQueueSize;
}

void CQueue::ClearQueue( void )
{

}
