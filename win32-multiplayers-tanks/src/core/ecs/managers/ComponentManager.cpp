#include "ComponentManager.h"

namespace core { namespace ecs {

	ComponentManager::ComponentManager(core::memory::IAllocator* Allocator) :
		MemoryAllocator(Allocator)
	{
	}

	ComponentManager::~ComponentManager()
	{
		//TODO: clear memory
	}

	ComponentId ComponentManager::AqcuireComponent(IComponent* component)
	{
		Assert(!component);

		u32 OldSize = ComponentTable.size();

		for (u32 i = 0; i < OldSize; ++i)
		{
			if (ComponentTable[i] == nullptr)
			{
				ComponentTable[i] = component;
				return i;
			}
		}

		u32 NewSize = OldSize + 10;
		ComponentTable.resize(NewSize, nullptr);
		ComponentTable[OldSize] = component;

		return OldSize;
	}

	//TODO: Write UnmapComponent
	void ComponentManager::MapGameObjectComponent(GameObjectId OwnerId, ComponentId ComponentId, TypeId ComponentType)
	{
		static const u32 NUM_OF_COMPONENTS = util::FamilyTypeID<IComponent>::Get();

		if((GameObjectComponentsMatrix.size()) <= OwnerId)
		{
			u32 OldSize = GameObjectComponentsMatrix.size();
			u32 NewSize = OldSize + 10;

			GameObjectComponentsMatrix.resize(NewSize);
			
			for (u32 i = OldSize; i < NewSize; ++i)
			{
				GameObjectComponentsMatrix[i].resize(NUM_OF_COMPONENTS, INVALID_COMPONENT_ID);
			}
		}

		GameObjectComponentsMatrix[OwnerId][ComponentType] = ComponentId;
	}

	void ComponentManager::DeactivateCompoenents(GameObjectId Id)
	{
		for (u32 i = 0; i < GameObjectComponentsMatrix[Id].size(); ++i)
		{
			ComponentId DeletingId = GameObjectComponentsMatrix[Id][i];
			if (DeletingId != INVALID_COMPONENT_ID)
			{
				ComponentTable[DeletingId]->isActive = false;
			}
		}
	}
} }