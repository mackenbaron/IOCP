#pragma once

#include <windows.h>
#include <malloc.h>

class CachedAlloc
{
public:
	CachedAlloc(size_t size)
        : m_size(max(size, sizeof(SLIST_ENTRY)))
	{
		m_pListHead = (PSLIST_HEADER)_aligned_malloc(sizeof(SLIST_HEADER),
												MEMORY_ALLOCATION_ALIGNMENT);
		InitializeSListHead(m_pListHead);
	}
	~CachedAlloc()
	{
		 _aligned_free(m_pListHead);
	}

	void put(void* pData)
	{
		InterlockedPushEntrySList(m_pListHead, (PSLIST_ENTRY) pData);
	}

	void* get()
	{
		void* result = InterlockedPopEntrySList(m_pListHead);
		if (NULL == result)
		{
			result = _aligned_malloc(m_size,
									MEMORY_ALLOCATION_ALIGNMENT);
		}

		return result;
	}

	size_t getSize() const
	{
		return m_size;
	}

private:
    CachedAlloc(const CachedAlloc&) = delete;
    CachedAlloc& operator = (const CachedAlloc&) = delete;

private:
	size_t m_size;
	PSLIST_HEADER m_pListHead;
};
