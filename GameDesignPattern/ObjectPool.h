#pragma once
#include <iostream>
#include <vector>

/*对象池模式
* 减少频繁创建和销毁的开销
* 管理对象复用
* 稳定性能
* 
* 优点:
* 1.提高性能, 减少内存分配次数
* 2.对象复用, 减少碎片化
* 3.在高频率对象使用场景中表现优秀 (如数千个粒子对象)
* 
* 缺点:
* 1.占用额外内存(提前分配)
* 2.池的大小要合理设置, 否则可能溢出或浪费
* 3.逻辑稍复杂(对象生命周期的管理)
* 
* 适用场景:
* 穿件成本高的资源: 渲染资源, 数据库资源, IO, 游戏中高频出现的对象
* 网络池链接, 线程池
*/

class Bullet
{
public:
	void fire(float x, float y)
	{
		active = true;
		posX = x;
		posY = y;
		std::cout << "[Bullet] Fired at (" << posX << ", " << posY << ")" << std::endl;
	}

	void Update()
	{
		if (active)
		{
			posY += 1.0f;
			std::cout << "[Bullet] Moving at (" << posX << ", " << posY << ")" << std::endl;
		}
	}

	void Deactivate() { active = false; }
	bool IsActive() { return active; }
private:
	bool active = false;
	float posX = 0, posY = 0;
};

template<typename T>
class ObjectPool
{
public:
	ObjectPool(size_t size)
	{
		pool.reserve(size);
		for (size_t i = 0; i < size; i++)
		{
			pool.push_back(std::make_shared<T>());
		}
	}

	T* AcquireObject()
	{
		for (auto& obj : pool)
		{
			if (!obj->IsActive())
			{
				return obj.get();
			}
		}
		pool.push_back(std::make_shared<T>());
		return pool.back().get();
	}

	void ResetAll()
	{
		for (auto& obj : pool)
		{
			obj->Deactivate();
		}
	}

private:
	std::vector<std::shared_ptr<T>> pool;
};