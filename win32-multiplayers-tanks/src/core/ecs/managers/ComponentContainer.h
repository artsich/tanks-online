#pragma once 

#include <vector>

#include "../IComponent.h"
#include "../../core.h"
#include "../../../core/memory/LinearAllocator.h"

#define MAX_GAME_OBJECTS 100
#define MAX_COMPONENTS 16

namespace core { namespace ecs {

	class IComponentContainer {};

	template<class Type>
	class ComponentsContainer : public IComponentContainer
	{
	private:
		memory::IAllocator* Allocator;

	public:
		ComponentsContainer(void* StartMemory, u64 MemorySize)
		{
			//TODO: Change on StackAllocator
			Allocator = new memory::LinearAllocator(StartMemory, MemorySize);

			//TODO: Component check this resize !!
			Components.resize(1);
		}

		~ComponentsContainer()
		{
			//TODO: Clear ??
			delete Allocator;
		}

		template<class... ARGS>
		Type* CreateComponent(ARGS&&... Args)
		{
			void* AllocatedMemory = Allocator->Allocate(sizeof(Type), DEFAULT_ALIGNMENT_OF_MEMORY);

			Assert(AllocatedMemory == nullptr);

			Type* Result = new (AllocatedMemory) Type(std::forward<ARGS>(Args)...);
			Components.push_back(Result);
			return Result;
		}
		
		void DestroyComponent(ComponentId id)
		{
			/*
			TODO: Destroy component if isActice == false!!
	
			for (u32 i = 0; i < Components.size(); ++i)
			{
				if (!Components[i]->isActive)
				{
				}
			}*/
		}

		//Bagfix: why don't work??
		Type* operator[] (u32 Index)
		{
			Assert(Components.size() <= Index);
			return Components[Index];
		}

		inline u32 GetSize() { return Components.size(); }
		std::vector<Type*> Components;
	};
}}