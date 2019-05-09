#pragma once

#include "../core.h"

namespace core { namespace util {
	
	template<class T>
	class FamilyTypeID
	{
	private:
		static TypeId count;
	public:

		template<class U>
		static const TypeId Get()
		{
			static const TypeId STATIC_TYPE_ID { count++ };
			return STATIC_TYPE_ID;
		}

		static const TypeId Get()
		{
			return count;
		}		
	};
	
	template<class T>
	TypeId FamilyTypeID<T>::count = 0;


}}