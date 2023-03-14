#include "ncrt_memory.h"

#include <Windows.h>
#include <intrin.h>

extern "C"
{
#pragma function(memset)
	void* __cdecl memset(void* dest, int value, size_t num)
	{
#ifdef __clang__
		size_t len = num;
		unsigned char* p = (unsigned char*)dest;
		while (len--)
		{
			*p++ = (unsigned char)value;
		}
#else
		__stosb(static_cast<unsigned char*>(dest),
			static_cast<unsigned char>(value), num);
#endif
		return dest;
	}

#pragma function(memcpy)
	void* __cdecl memcpy(void* dest, const void* src, size_t num)
	{
		__movsb(static_cast<unsigned char*>(dest),
			static_cast<const unsigned char*>(src), num);
		return dest;
	}
}

void* operator new(size_t n)
{
	return HeapAlloc(GetProcessHeap(), NULL, n);
}

void* operator new[](size_t n)
{
	return HeapAlloc(GetProcessHeap(), NULL, n);
}

void operator delete(void* p)
{
	HeapFree(GetProcessHeap(), NULL, p);
}

void operator delete[](void* p)
{
	HeapFree(GetProcessHeap(), NULL, p);
}