#pragma once
#include <iostream>

/*装饰器模式 - 动态扩展对象功能
* 灵活组合
* 遵循开闭原则 - 开放扩展, 关闭修改
* 
* 优点:
* 1.比继承更灵活, 可以在运行时觉得扩展哪些功能
* 2.多个装饰器可以累计叠加, 实现复杂功能
* 3.不会因为功能组合导致类爆炸(相比多宠继承/分支子类)
* 
* 缺点:
* 1.多层装饰器会增加系统复杂性及调试难度
* 2.调用栈较深时, 可能影响性能(递归调用)
* 
* 使用场景:
* 1.希望在运行时为对象添加工能, 而不是在编译期决定
* 2.不影响同类其他对象的情况下, 为单个对象定制功能
* 3.避免使用庞大的继承体系
* 
*/

class Character
{
public:
	virtual ~Character() = default;
	virtual void Attack() const = 0;
};

class Warrior : public Character
{
public:
	void Attack() const override
	{
		std::cout << "Warrior Attack with sword!" << std::endl;
	}
};

class CharacterDecorator : public Character
{
public:
	CharacterDecorator(std::shared_ptr<Character> chara) : character(chara) {}
protected:
	std::shared_ptr<Character> character;
};

class FireEnchantment : public CharacterDecorator
{
public:
	FireEnchantment(std::shared_ptr<Character> chara) : CharacterDecorator(chara) {}

	void Attack() const override
	{
		character->Attack();
		std::cout << "-> The attack is engulfed in flames !" << std::endl; 
	}
};

class IceEnchantment : public CharacterDecorator
{
public:
	IceEnchantment(std::shared_ptr<Character> chara) : CharacterDecorator(chara) {}

	void Attack() const override
	{
		character->Attack();
		std::cout << "-> The attack freezes the enemy !" << std::endl;
	}
};
