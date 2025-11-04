#pragma once

#include <iostream>

/* 原型设计模式 - 用原型实例指定创建对象的种类, 并且通过拷贝这些原型创建新的对象
 * 1.避免重复创建消耗大的对象(尤其对象初始化成本高时)
 * 2.绕过构造函数的复杂性, 直接复制已有对象
 * 3.运行时确定对象类型, 不用在编译器确定具体类
 * 4.可以在运行时动态注册, 替换原型
 * 5.扩展性好, 新增类型只需要实现 Clone() 方法
 * [缺点]: 对象内部包含复杂引用时, 深拷贝实现较复杂
 * 
 * 使用场景:
 * 1.对象创建开销大(例如, 包含复杂数据初始化)
 * 2.希望动态复制对象, 并在复制后独立修改
 * 3.游戏对象模板克隆(敌人, NPC, 武器等)
 * 4.关卡元素批量实例化(用一个原型快速生产)
 * 5.缓存对象(加载一次, 后续全部克隆副本)
 * 
 * UE:
 * DuplicatedObject(), StaticDuplicatedObject(), FObjectInitializer
 * 
*/

class Prototype
{
public:
	virtual ~Prototype() = default;
	virtual std::unique_ptr<Prototype> Clone() const = 0;
	virtual void ShowInfo() const = 0;
};

class Enemy : public Prototype
{
public:
	Enemy(std::string name, int hp) : Name(name), Health(hp) {}

	std::unique_ptr<Prototype> Clone() const override
	{
		return std::make_unique<Enemy>(*this);
	}

	void ShowInfo() const override
	{
		std::cout << "Enemy: " << Name << ", HP: " << Health << std::endl;
	}

private:
	std::string Name;
	int Health;
};
