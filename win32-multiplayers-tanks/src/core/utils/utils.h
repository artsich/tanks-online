#pragma once

#include "../core.h"

namespace core { namespace util {
	
	template<class T>
	class FamilyTypeID
	{
	private:
		static TypeID count;
	public:

		template<class U>
		static const TypeID Get()
		{
			static const TypeID STATIC_TYPE_ID { count++ };
			return STATIC_TYPE_ID;
		}
	};

	unsigned int reverse(register unsigned int x);

}}