#include "utils.h"

namespace core { namespace util {

	unsigned int reverse(unsigned int x)
	{
		x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
		x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
		x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
		x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
		return((x >> 16) | (x << 16));
	}

	//template<class T>
	//template<class U>
	//inline const TypeId FamilyTypeID<T>::Get()
	//{
	//	static const TypeId STATIC_TYPE_ID { FamilyTypeID<U>::count++ };
	//	return STATIC_TYPE_ID;
	//}

	//template<class T>
	//const TypeId FamilyTypeID<T>::Get()
	//{ 
	//	return count; 
	//}

}}