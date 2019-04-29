#pragma once

#include "../core/core.h"
#include "../core/math/vec2.h"
#include "../core/input/gamecontroller.h"
#include "../core/utils/utils.h"
#include "./systems/physics_system.h"

#include <vector>

using namespace core;

namespace game {

	//class CollisionDetecter 
	//{
	//private: 
	//	CollisionDetecter()
	//	{

	//	}

	//	void 
	//};

	//class PhysicManager 
	//{
	//private:
	//	float speed;

	//public:
	//	PhysicManager(float speed) :
	//		speed(speed)
	//	{
	//	}

	//	void move(math::vec2& source, math::vec2& dv, float dt)
	//	{
	//		auto v = dv * dt * speed;
	//		source += dv;
	//	}
	//};

	class HandleGameInput
	{
	private:
		PhysicManager _physic;
		std::vector<physics::entity*> entities;

	public:

		HandleGameInput(PhysicManager physic) : _physic(physic)
		{

		}

		void Handle(controller::game_input* input)
		{
			for (int controllerIndex = 0;
				controllerIndex < ArrayCount(input->Controllers);
				++controllerIndex)
			{
				core::controller::game_controller_input* controller = core::controller::GetController(input, controllerIndex);

				if (!controller->IsConnected)
				{
					continue;
				}

				if (controller->IsAnalog)
				{
					if (controller->ActionRight.EndedDown)
					{

						

						entity.pos = core::math::vec2(200, 300);
						continue;
					}

					float xStick = controller->StickAverageX;
					float yStick = controller->StickAverageY;

					core::math::vec2& pos = entity.pos;
					pos.x += xStick * speed * dt;
					pos.y += yStick * speed * dt;
				}
				else
				{
					float dx = 0.0f;
					float dy = 0.0f;
					if (controller->MoveLeft.EndedDown)
					{
						dx = -1.0f;
					}

					if (controller->MoveRight.EndedDown)
					{
						dx = 1.0f;
					}

					if (controller->MoveUp.EndedDown)
					{
						dy = -1.0f;
					}

					if (controller->MoveDown.EndedDown)
					{
						dy = 1.0f;
					}

					dx *= speed;
					dy *= speed;

					core::math::vec2& pos = entity.pos;

					pos.x += dx * dt;
					pos.y += dy * dt;
				}
			}
		}
	};


	//class EntityManager 
	//{
	//	//class IEntityContainer 
	//	//{
	//	//public:
	//	//	virtual ~IEntityContainer() {}
	//	//	virtual const char* GetEntityContainerTypeName() = 0;
	//	//	virtual void DestroyEntity(IEntity* object) = 0;
	//	//};


	//	//template<class T>
	//	//class EntityContainer : public IEntityContainer
	//	//{
	//	//	const char* GetEntityContaieTypeName() override
	//	//	{
	//	//		static const char* ENTITY_TYPE_NAME{ typeid(T).name() };
	//	//		return ENTITY_TYPE_NAME;
	//	//	}

	//	//	void DestroyEntitity(IEntity* object) override
	//	//	{
	//	//		object->~IEntity();
	//	//	}
	//	//};

	//	//template<class T>
	//	//private EntityContainer<T>* GetEntityContainer()
	//	//{
	//	//	EntityTypeId eid = T::STATIC_ENTITY_ID;
	//	//	return NULL;
	//	//}

	//public: 
	//	template<class T, class... ARGS>
	//	virtual EntityId CreateEntity()
	//	{

	//	}

	//	virtual IEntity* GetEntity(EntityId id) 
	//	{

	//		return NULL;
	//	}

	//	virtual void DestroyEntity(EntityId id)
	//	{

	//	}
	//};

	class IEntity
	{
	private:		
		EntityId entity_id;
		bool m_Active;

	public:

		IEntity();
		virtual ~IEntity();

		virtual EntityTypeId GetEntityTypeId() = 0;
		inline EntityId GetEntityId() { return entity_id; }

		inline bool IsActive() { return this->m_Active; }
		inline void IsActive(bool state) { this->m_Active = state; }

	};

	template<class T>
	class Entity : public IEntity
	{
	private:
		static const EntityTypeId STATIC_ENTITY_TYPE_ID;

		void operator delete(void*) = delete;
		void operator delete[](void*) = delete;

	public:
		Entity() {};
		virtual ~Entity() {};

		virtual EntityTypeId GetEntityTypeId() override { return STATIC_ENTITY_TYPE_ID; }
	};

	//template<class E>
	//const EntityTypeId Entity<E>::STATIC_ENTITY_TYPE_ID = util::Internal::FamilyTypeID<IEntity>::Get<E>();

	//using ComponentId = size_t;
	//using ComponentTypeId = size_t;
	//static const ComponentId INVALID_COMPONENT_ID = INVALID_OBJECT_ID;

	//class IComponent 
	//{
	//protected:
	//	ComponentId hashValue;
	//	ComponentId componentId;
	//	EntityId owner;

	//	bool enabled;

	//public: 
	//	IComponent();
	//	virtual ~IComponent();

	//	inline ComponentId GetComponentId() { return componentId; }
	//	inline EntityId GetOwner() { return owner; }
	//	
	//	inline void SetActive(bool state) { this->enabled = state; }
	//	inline bool IsActive() { return this->enabled; }

	//};
	
}

namespace ecs
{

	
}