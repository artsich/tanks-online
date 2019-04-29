#pragma once

#include "../../core/core.h"
#include "../../core/utils/utils.h"
#include "Components.h"
#include <vector>

using namespace core;

namespace game { namespace ecs {

	class IEntity
	{
	private:
		EntityId entity_id;

	public:
		IEntity();
		virtual ~IEntity();

		inline EntityId GetEntityId() { return entity_id; }
	};

	template<class T>
	class Entity : public IEntity
	{
	private:
		static const EntityTypeId STATIC_ENTITY_TYPE_ID;
		std::vector<Component>

	public:
		Entity() {};
		virtual ~Entity() {};

		virtual EntityTypeId GetEntityTypeId() override { return STATIC_ENTITY_TYPE_ID; }
	};

	template<class T>
	const EntityTypeId Entity<T>::STATIC_ENTITY_TYPE_ID = util::FamilyTypeID<T>::Get();

}}