#pragma once

/* 
	TODO: Need use other allocator
	ALSO - 
		Need write "garbage collector"
*/

#include <map>

#include "../GameObject.h"
#include "../IComponent.h"

#include "ComponentContainer.h"

#include "../../../core/core.h"
#include "../../../core/memory/LinearAllocator.h"

#define MAX_GAME_OBJECTS 100
#define MAX_CONTAINERS_COMPONENTS 300

namespace core { namespace ecs {

	class ComponentManager
	{
	private:
		using MapTypeComponent = std::map<TypeId, IComponentContainer*>;
		using GameObjectComponents = std::vector<std::vector<ComponentId>>;

		memory::IAllocator* MemoryAllocator;

		MapTypeComponent TypesComponents;
		GameObjectComponents GameObjectComponentsMatrix;

		std::vector<IComponent*> ComponentTable;
		bool BitsetComponent[MAX_CONTAINERS_COMPONENTS];

		ComponentId AqcuireComponent(IComponent* Component);
		void MapGameObjectComponent(GameObjectId OwnerId, ComponentId ComponentId, TypeId ComponentType);

	public:

		ComponentManager(core::memory::IAllocator* Allocator);

		~ComponentManager();

		void DeactivateCompoenents(GameObjectId);

		template<class TComponent, class ...ARGS>
		TComponent* AddComponent(GameObjectId OwnerId, ARGS&&... Args)
		{
			//TODO(important): Check on exist component for OwnerID !!!
			ComponentsContainer<TComponent>* Container = GetComponentsContainer<TComponent>();
			TComponent* Result = Container->CreateComponent(std::forward<ARGS>(Args)...);

			Result->Id = AqcuireComponent(Result);
			Result->ownerId = OwnerId;
			Result->isActive = true;

			MapGameObjectComponent(OwnerId, Result->Id, Result->GetTypeId());

			return Result;
		}

		template<class T>
		T* GetComponent(GameObjectId id)
		{
			TypeId ComponentTypeID = T::STATIC_COMPONENT_TYPE_ID;

			Assert(GameObjectComponentsMatrix.size() <= id);
			Assert(GameObjectComponentsMatrix[id].size() <= ComponentTypeID);

			ComponentId CID = GameObjectComponentsMatrix[id][ComponentTypeID];
			if (CID == INVALID_COMPONENT_ID)
			{
				return nullptr;
			}
			
			T* Result = (T*)ComponentTable[CID];
			return Result;
		}

		void DisableGameObject(GameObjectId id)
		{

		}

		template<class T>
		ComponentsContainer<T>* GetComponentsContainer()
		{
			TypeId ComponentTypeId = T::STATIC_COMPONENT_TYPE_ID;
			ComponentsContainer<T>* Result = nullptr;

			if (!BitsetComponent[ComponentTypeId])
			{
				BitsetComponent[ComponentTypeId] = true;

				u32 ConteinerSize = sizeof(ComponentsContainer<T>);				
				void* AllocatedForCreateContainer = MemoryAllocator->Allocate(ConteinerSize, alignof(ComponentsContainer<T>));
				u64 SizeDataForContainer = sizeof(T) * MAX_CONTAINERS_COMPONENTS;
				void* StartContainerData = MemoryAllocator->Allocate(SizeDataForContainer, alignof(T));

				Assert(AllocatedForCreateContainer == nullptr);
				Assert(StartContainerData == nullptr);

				Result = new (AllocatedForCreateContainer) ComponentsContainer<T>(StartContainerData, SizeDataForContainer);
				TypesComponents.emplace(ComponentTypeId, Result);
			}
			else
			{
				Result = (ComponentsContainer<T>*)TypesComponents[ComponentTypeId];
			}

			return Result;
		}
	};

} }