#pragma once

#include "../core.h"
#include "../utils/utils.h"
#include "GameObject.h"

#define INVALID_COMPONENT_ID (2111111111)

namespace core { namespace ecs {
	
	using ComponentId = u32;
	struct IComponent
	{
		bool isActive;
		ComponentId Id;
		GameObjectId ownerId;

		virtual TypeId GetTypeId() = 0;
		inline GameObjectId getOwnerId() { return this->ownerId; }
	};

	template<class T>
	struct Component : public IComponent
	{
	public:
		static const TypeId STATIC_COMPONENT_TYPE_ID;

		TypeId GetTypeId() override
		{
			return STATIC_COMPONENT_TYPE_ID;
		}
	};

	template<class T>
	const TypeId Component<T>::STATIC_COMPONENT_TYPE_ID = core::util::FamilyTypeID<IComponent>::Get<T>();
} }