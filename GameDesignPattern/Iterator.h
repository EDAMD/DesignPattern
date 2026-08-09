#pragma once

#include <iostream>
#include <vector>

/*迭代器模式
* 统一遍历接口
* 解耦遍历算法与容器本身
* 支持多种遍历方式
* 
* 优点:
* 1.遍历操作与容器类解耦, 可以独立变化
* 2.支持多种不同的容器和遍历方式
* 3.符合单一职责原则: 容器负责存储, 迭代器负责 遍历
* 
* 缺点:
* 1.对于简单遍历, 增加系统结构的复杂性
* 2.多个迭代器同事操作统一容器时, 需要注意同步问题
* 
* 适用场景
* 遍历对象列表时不想暴露他的内部
* 
* 
*/

template<typename T>
class IIterator
{
public:
	virtual ~IIterator() = default;
	virtual bool HasNext() = 0;
	virtual T Next() = 0;
};

template<typename T>
class IAggregate
{
public:
	virtual ~IAggregate() = default;
	virtual std::shared_ptr<IIterator<T>> CreateIterator() = 0;
};

class ItemCollection : public IAggregate<int>
{
public:
	void AddItem(int value)
	{
		items.push_back(value);
	}

	std::shared_ptr<IIterator<int>> CreateIterator() override;

	const std::vector<int>& GetItems() const { return items; }

private:
	std::vector<int> items;
};

class ItemIterator : public IIterator<int>
{
public:
	ItemIterator(const ItemCollection& collection)
		:collection(collection), index(0)
	{
	}

	virtual bool HasNext() override
	{
		return index < collection.GetItems().size();
	}

	virtual int Next() override
	{
		return collection.GetItems()[index++];
	}

private:
	const ItemCollection& collection;
	size_t index;
};