#pragma once

#include "../../core/core.h"

using namespace core;

namespace game { namespace ecs {

	static const ComponentId INVALID_COMPONENT_ID = INVALID_OBJECT_ID;

	class IComponent
	{
	protected:
		ComponentId componentId;
		EntityId owner;

		bool enabled;

		IComponent();

	public:
		virtual ~IComponent();

		inline ComponentId GetComponentId() { return componentId; }
		inline EntityId GetOwner() { return owner; }

		inline void SetActive(bool state) { this->enabled = state; }
		inline bool IsActive() { return this->enabled; }
	};

	template<class T>
	class Component : public IComponent
	{
	private:
		static const ComponentTypeId STATIC_COMPONENT_TYPE_ID;

	public:
		Component();
		virtual ~IComponent();
	};

	template<class T>
	const ComponentTypeId Component<T>::STATIC_COMPONENT_TYPE_ID = util::FamilyTypeID<T>::Get();

} }