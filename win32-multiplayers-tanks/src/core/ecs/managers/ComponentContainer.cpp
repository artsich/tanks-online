#include "ComponentContainer.h"

namespace core { namespace ecs {
	
	//ComponentsContainer<Type>::ComponentsContainer(memory::IAllocator* Allocator) :
	//	Allocator(Allocator)
	//{
	//}
	//ComponentsContainer::

	//template<class ...ARGS>
	//Type* ComponentsContainer<Type>::CreateComponent(ARGS&&... Args)
	//{
	//	void* AllocatedMemory = Allocator.Allocate(sizeof(Type));
	//	Type* Result = new (AllocatedMemory) Type(std::forward<ARGS>(Args)...);
	//	Components.push_back(Result);
	//	return Result;
	//}

}}