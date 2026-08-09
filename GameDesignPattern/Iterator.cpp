#include "Iterator.h"

std::shared_ptr<IIterator<int>> ItemCollection::CreateIterator()
{
	return std::make_shared<ItemIterator>(*this);
}
