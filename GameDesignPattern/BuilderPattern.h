#pragma once
#include <iostream>
#include <string>

/* 构建者模式 
* 1.将复杂对象的构造过程与表示分离, 相同的构建过程可以创建不同的表示
* 2.避免构造函数参数过多的问题, 是构建过程更可读, 更灵活
* 3.客户端不用关系具体的构建细节, 只需关注成品
* 
* 使用场景
* 1.对象构建步骤固定, 但部件不同
* 2.避免复杂构造函数
* 3.需要创建不同风格的复杂对象
* 
* 应用方向:
* 不同武器建造, 不同人物建造, 不同房屋建造
* 
* UE:
* FMenuBuilder, FArchive
*/

class Weapon
{
public:
	void SetName(const std::string& name) { this->name = name; }
	void SetDamage(int dmg) { this->damage = dmg; }
	void SetRange(float rng) { this->range = rng; }

	void Show()
	{
		std::cout << "Weapon: " << name << ", Damage: " << damage << ", Range: " << range << std::endl;
	}

private:
	std::string name;
	int damage = 0;
	float range = 0.f;
};

class WeaponBuilder
{
public:
	virtual ~WeaponBuilder() = default;

	virtual void BuildName() = 0;
	virtual void BuildDamage() = 0;
	virtual void BuildRange() = 0;

	virtual std::unique_ptr<Weapon> GetResult() = 0;
};

class SwordBuilder : public WeaponBuilder
{
public:
	SwordBuilder() { weapon = std::make_unique<Weapon>(); }

	void BuildName() override { weapon->SetName("Excalibur Sword"); }
	void BuildDamage() override { weapon->SetDamage(100); }
	void BuildRange() override { weapon->SetRange(1.5f); }

	std::unique_ptr<Weapon> GetResult() override { return std::move(weapon); }

private:
	std::unique_ptr<Weapon> weapon;
};

class BowBuilder : public WeaponBuilder
{
public:
	BowBuilder() { weapon = std::make_unique<Weapon>(); }

	void BuildName() override { weapon->SetName("Longbow"); }
	void BuildDamage() override { weapon->SetDamage(60); }
	void BuildRange() override { weapon->SetRange(30.f); }

	std::unique_ptr<Weapon> GetResult() override { return std::move(weapon); }

private:
	std::unique_ptr<Weapon> weapon;
};

// 指挥者
class WeaponDirector
{
public:
	void Construct(WeaponBuilder& Builder)
	{
		Builder.BuildName();
		Builder.BuildDamage();
		Builder.BuildRange();
	}
};