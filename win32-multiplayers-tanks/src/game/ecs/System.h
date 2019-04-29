#pragma once

#include "../../core/core.h"
#include "../../core/utils/utils.h"
using namespace core;

namespace game { namespace ecs {

	class ISystem
	{
	public: 
		virtual void startup() = 0;
		virtual void shutdown() = 0;

		virtual void update(float dt) = 0;
		virtual SystemTypeId GetEntityTypeId() = 0;
	};

	template<class T>
	class System : public ISystem
	{
		static const SystemTypeId STATIC_SYSTEM_TYPE_ID;

	public:
		virtual SystemTypeId GetSystemTypeId()
		{
			return STATIC_SYSTE_TYPE_ID;
		}
	};

	template<class T>
	const SystemTypeId System<T>::STATIC_SYSTEM_TYPE_ID = util::FamilyTypeID<T>::Get();

} }