#include "Singleton.h"
#include "Factory.h"
#include "BuilderPattern.h"
#include "Prototype.h"

int main()
{
	// 单例
	Singleton::GetInstance().DoSomething();

	// 工厂
	std::unique_ptr<Factory> factory = std::make_unique<FactoryA>();
	auto Product1 = factory->CreateProduct();
	Product1->Use();

	factory = std::make_unique<FactoryB>();
	auto Product2 = factory->CreateProduct();
	Product2->Use();

	// 建造者 - 通过构造器(Builder)创建不同对象
	WeaponDirector director;

	SwordBuilder swordBuilder;
	director.Construct(swordBuilder);
	auto sword = swordBuilder.GetResult();
	sword->Show();

	BowBuilder bowBuilder;
	director.Construct(bowBuilder);
	auto bow = bowBuilder.GetResult();
	bow->Show();

	// 原型 - 通过一个对象克隆生成其他相同对象
	std::unique_ptr<Enemy> goblinPrototype = std::make_unique<Enemy>("Goblin", 100);

	auto goblin1 = goblinPrototype->Clone();
	auto goblin2 = goblinPrototype->Clone();

	goblin1->ShowInfo();
	goblin2->ShowInfo();


	return 0;
}