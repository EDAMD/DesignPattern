#include "Singleton.h"
#include "Factory.h"
#include "BuilderPattern.h"
#include "Prototype.h"
#include "Adapter.h"
#include "Bridge.h"
#include "Composite.h"
#include "Decorator.h"
#include "Flyweight.h"
#include "Proxy.h"
#include "ChainOfResponsibility.h"
#include "Command.h"
#include "Interpreter.h"
#include "Iterator.h"
#include "Mediator.h"

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

	// 适配器 - 将旧设备的接口转换为新设备可以使用的
	std::shared_ptr<OldInterface> oldObj = std::make_shared<OldInterface>();
	std::shared_ptr<ITarget> adapter = std::make_shared<Adapter>(oldObj);

	adapter->Request();

	// 桥接模式
	std::shared_ptr<Device> tv = std::make_shared<TV>();
	std::shared_ptr<Device> radio = std::make_shared<Radio>();

	RemoteControl Remote(tv);
	Remote.TurnOff();
	Remote.TurnOn();
	Remote.VolumeUp();

	AdvancedRemote advRemote(radio);
	advRemote.TurnOn();
	advRemote.Mute();
	advRemote.TurnOff();


	// 组合模式
	auto root = std::make_shared<SceneNode>("Root");
	auto house = std::make_shared<SceneNode>("House");

	auto lamp = std::make_shared<Light>("Lamp");
	auto WallMesh = std::make_shared<Mesh>("WallMesh");
	auto roofMesh = std::make_shared<Mesh>("RoofMesh");

	root->Add(house);
	house->Add(lamp);
	house->Add(WallMesh);
	house->Add(roofMesh);

	root->ShowInfo();

	// 装饰器模式
	std::shared_ptr<Character> warrior = std::make_shared<Warrior>();

	std::shared_ptr<Character> FireWarrior = std::make_shared<FireEnchantment>(warrior);
	FireWarrior->Attack();

	std::shared_ptr<Character> IceWarrior = std::make_shared<IceEnchantment>(FireWarrior);
	IceWarrior->Attack();

	// 享元模式
	TreeModelFactory Treefactory;
	auto oakModel = Treefactory.GetTreeModel("OakMesh", "OakTexture");

	Tree tree1 = { 10, 20, oakModel };
	Tree tree2 = { 30, 40, oakModel };
	Tree tree3 = { 50, 60, oakModel };

	tree1.Render();
	tree2.Render();
	tree3.Render();


	// 代理模式
	ProxyImage image("HighRes_texture.png");
	image.Display();
	image.Display();

	
	// 责任链模式
	auto handlerA = std::make_shared<ConcreteHandlerA>();
	auto handlerB = std::make_shared<ConcreteHandlerB>();

	handlerA->SetNext(handlerB);

	handlerA->HandleRequest("TypeA");
	handlerA->HandleRequest("TypeB");
	handlerA->HandleRequest("TypeC");


	// 命令模式
	LightElement livingRoomLight;
	auto lightOn = std::make_shared<LightOnCommand>(livingRoomLight);
	auto lightOff = std::make_shared<LightOffCommand>(livingRoomLight);

	RemoteControlElement remote;

	remote.SetCommand(lightOn);
	remote.PressButtom();

	remote.SetCommand(lightOff);
	remote.PressButtom();

	remote.PressUndo();


	// 解释器模式
	std::shared_ptr<Expression> expression = std::make_shared<SubExpression>(
		std::make_shared<AddExpression>(
			std::make_shared<VariableExpression>("x"),
			std::make_shared<ConstantExpression>(5)
		),
		std::make_shared<VariableExpression>("y")
	);

	std::map<std::string, int> context;
	context["x"] = 10;
	context["y"] = 3;

	std::cout << "Result: " << expression->Interpret(context) << std::endl; 


	// 迭代器模式
	ItemCollection collection;
	collection.AddItem(10);
	collection.AddItem(20);
	collection.AddItem(30);

	std::shared_ptr<IIterator<int>> it = collection.CreateIterator();

	while (it->HasNext())
	{
		std::cout << it->Next() << std::endl;
	}

	// 中介者模式
	GameMediator mediator;

	Player p1("Alice", mediator);
	Player p2("Bob", mediator);
	Player p3("Charlie", mediator);

	mediator.AddColleague(&p1);
	mediator.AddColleague(&p2);
	mediator.AddColleague(&p3);

	p1.SendMessage("Hello everyone !");
	p2.SendMessage("Hi Alice !");

	return 0;
}