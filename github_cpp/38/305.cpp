#include <assert.h>
#include "queue.h"
#include <Windows.h>

namespace zedu {

	class PlainQueue : public IQueue
	{
	private:
		IQueueAllocator* m_pAllocator;
		byte* m_pData;
		uint32 m_size;
		uint32 m_length;

	public:
		PlainQueue( IQueueAllocator* pAllocator, uint32 length=8192 )
		{
			m_pAllocator = pAllocator;
			m_pData = static_cast<byte*>( m_pAllocator->Alloc( length ) );
			if( !m_pData )
			{
				// TODO+ Error!
			}
			m_length = length;
			m_size = 0;
		}

		virtual ~PlainQueue()
		{
		}

		virtual uint32 Write( const void* pData, uint32 size )
		{
			if( size == 0 ) return 0;

			assert( size != 0 && pData != NULL );

			if( m_length - m_size < size )
			{
				if( !IncreaseBuffer( size + m_length ) )
					return 0;
			}

			if( FreeSize() < size )
				IncreaseBuffer( size - FreeSize() + m_length );

			memcpy( &m_pData[m_size], pData, size );

			m_size += size;
			return size;
		}

		virtual uint32 Read( void* pBuf, uint32 size )
		{
			assert( size && Size() > 0 );

			uint32 readSize = min( size, Size() );

			if( pBuf ) 
				memcpy( pBuf, m_pData, readSize );

			if( Size() - readSize )
			{
				memmove( m_pData, m_pData + readSize, Size() - readSize );
			}

			m_size = Size() - readSize;
			return readSize;
		}
		

		virtual uint32 Peek( void* pBuf, uint32 size )
		{
			uint32 readSize = min( size, Size() );
			memcpy( pBuf, m_pData, readSize );
			return readSize;
		}
		
		virtual bool Clear()
		{
			m_size = 0;
			return true;
		}

		virtual uint32 Size()	{ return m_size; }
		virtual uint32 Count()	{ return 1; }
		byte* GetBuf()			{ return m_pData; }

		bool IncreaseBuffer( uint32 size )
		{
			byte* pNewData = static_cast<byte*>( m_pAllocator->Realloc( m_pData, m_length + size ) );

			if( pNewData )
			{
				m_pData = pNewData;
			}
			else
			{
				m_pData = pNewData;
			}

			m_length += size;

			return true;
		}

		uint32 FreeSize()
		{
			return m_length - m_size;
		}

		virtual bool Reserve( uint32 size )	
		{ 
			uint32 increaseSize = size - FreeSize();
			return IncreaseBuffer( increaseSize ); 
		}

		virtual bool Resize( uint32 size )
		{ 
			if( m_length < size )
				return false;

			m_size = size;
			return true;
		}

		virtual uint32 GetReservedSize()
		{
			return m_length;
		}
	};

	IQueue* IQueue::CreateQueue( uint32 defaultSize )
	{
		static IQueueAllocator defaultAllocator;
		IQueue* pQueue = NULL;

		pQueue = new PlainQueue( &defaultAllocator, defaultSize );

		return pQueue;
	}
}