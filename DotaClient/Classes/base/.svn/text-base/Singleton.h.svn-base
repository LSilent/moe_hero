
#ifndef _SINGLETON_H__
#define _SINGLETON_H__

#include "./base/Global.h"

template <typename T> class Singleton
{
public:
	static T* sm_Singleton;

public:
	Singleton()
	{
		if(sm_Singleton != NULL) return;
		 	 
		#if defined( _MSC_VER ) && _MSC_VER < 1200	 
			int offset = (int)(T*)1 - (int)(UBI_Singleton <T>*)(T*)1;
			sm_Singleton = (T*)((int)this + offset);
		#else
			sm_Singleton = static_cast< T* >( this );

		#endif

	}
	virtual ~Singleton()
	{ 
		sm_Singleton = 0; 
	}
	static T* GetSingleton()
	{ 
		return sm_Singleton; 
	}
};

#define DECLARE_SINGLETON(className) \
public: \
static className* GetSingleton(); \

#define IMPLEMENT_SINGLETON(className) \
template<> className* Singleton<className>::sm_Singleton = 0; \
className* className::GetSingleton() { return sm_Singleton; } \

#endif