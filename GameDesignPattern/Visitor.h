#pragma once
#include <iostream>
#include <vector>

/*访问者模式
* 操作与数据结构分离
* 多个行为的集中化管理
* 对不同类型元素执行不同操作
* 
* 优点:
* 1.扩展新操作很方便
* 2.代码组织清晰
* 3.解耦数据结构与操作, 提高代码复用性
* 
* 缺点:
* 1.添加新的元素类麻烦
* 2.系统中类的数量增多
* 3.双重分派机制对初学者来说陌生
* 
* 适用场景
* 数据结构相对稳定, 对其操作偶尔有变化
* 对结构中的不同元素作不同操作
* 渲染, 碰撞检测, 保存序列化, ai逻辑更新
*/

class OwnerWarrior;
class Mage;

class IVisitor
{
public:
	virtual ~IVisitor() = default;
	virtual  void Visit(OwnerWarrior& warrior) = 0;
	virtual  void Visit(Mage& mage) = 0;
};

class ICharacter
{
public:
	virtual ~ICharacter() = default;
	virtual void Accept(IVisitor& visitor) = 0;
};

class OwnerWarrior : public ICharacter
{
public:
	void Attack() { std::cout << "Warrior attacks with sword!" << std::endl; }
	virtual void Accept(IVisitor& visitor) override
	{
		visitor.Visit(*this);
	}
};

class Mage : public ICharacter
{
public:
	void CastSpell() { std::cout << "Mage casts a fireball!" << std::endl; }
	virtual void Accept(IVisitor& visitor) override
	{
		visitor.Visit(*this);
	}
};

class RenderVisitor : public IVisitor
{
public:
	virtual  void Visit(OwnerWarrior& warrior)
	{
		std::cout << "[Render] Drawing Warrior model." << std::endl;
	}
	virtual  void Visit(Mage& mage)
	{
		std::cout << "[Render] Drawing mage model." << std::endl;
	}
};

class AIVisitor : public IVisitor
{
public:
	virtual  void Visit(OwnerWarrior& warrior)
	{
		std::cout << "[AI] Warrior choose melee attack." << std::endl;
	}
	virtual  void Visit(Mage& mage)
	{
		std::cout << "[AI] Mage choose a range spell." << std::endl;
	}
};

