#include "simple_library/public/simple_library.h"
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
#include "Memento.h"
#include "Observer.h"
#include "State.h"
#include "Strategy.h"
#include "TemplateMode.h"
#include "Visitor.h"
#include "ObjectPool.h"
#include "ServiceLocator.h"
#include "Component.h"
#include "DataDriven.h"
#include "Blackboard.h"
#include "DoubleBuffer.h"
#include "GameLoop.h"
#include "LockStep.h"
#include "EventQueue.h"
#include "ServiceProvider.h"
#include "MVC.h"
#include "MVP.h"
#include "ECS.h"
#include "FSM.h"
#include "HFSM.h"

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

	p1.Sendmsg("Hello everyone !");
	p2.Sendmsg("Hi Alice !");


	// 备忘录模式
	TextEditor editor;
	History history;

	editor.SetText("Hello");
	history.Push(editor.Save());

	editor.SetText("Hello World");
	history.Push(editor.Save());

	editor.SetText("Hello Unreal");
	std::cout << "Current: " << editor.GetText() << std::endl;

	editor.Restore(history.Pop());
	std::cout << "Undo 1: " << editor.GetText() << std::endl;

	editor.Restore(history.Pop());
	std::cout << "Undo 2: " << editor.GetText() << std::endl;

	// 区别:
	// 命令模式:		请求封装为对象, 可撤销/重做
	// 备忘录模式:	保存并恢复对象状态, 不破坏封装

	// 总结比较
	// 比较项				命令模式Command										备忘录模式
	// 核心关注点			封装"行为" / "操作"									保存和恢复状态
	// 保存的内容			执行逻辑 + 可能恢复的信息(旧状态)						对象的完整内部状态
	// 是否关系状态细节		通常只保存必要的旧值以支持撤销							保存完整状态, 不关系执行过程
	// 撤销方式				通过反向执行(利用保存的旧值)							通过恢复状态快照
	// UE 示例				FUICommandList, 蓝图任务节点, Ability					调用 UObject::Modify() USaveGame, 事务快照
	// 关系					可结合适用:命令中调用备忘录的保存状态					备忘录可以作为命令撤销的底层实现机制


	// 观察者模式 
	Subject bossEvent;

	auto ui = std::make_shared<PlayerUI>();
	auto audio = std::make_shared<AudioSystem>();

	bossEvent.AddObserver(ui);
	bossEvent.AddObserver(audio);

	bossEvent.Notify("Boss Appeared");

	bossEvent.RemoveObserver(ui);
	bossEvent.Notify("Boss is Attacking");


	// 状态模式
	CharacterState PlayerState;

	PlayerState.SetState(make_shared<StateIdle>());
	PlayerState.Update();

	PlayerState.SetState(make_shared<StateRun>());
	PlayerState.Update();


	// 策略模式
	PaymentContext Paycontext;

	Paycontext.SetStrategy(make_shared<PayByCreditCard>());
	Paycontext.Checkout(100);

	Paycontext.SetStrategy(make_shared<PayByPayPal>());
	Paycontext.Checkout(200);



	// 模板模式
	GameModeBase* game1 = new ShooterGame();
	game1->StartGame();
	cout << "-------------------------------------" << endl;
	GameModeBase* game2 = new RacingGame();
	game2->StartGame();

	delete game1;
	delete game2;


	// 访问者模式
	vector<shared_ptr<ICharacter>> characters;
	characters.push_back(make_shared<OwnerWarrior>());
	characters.push_back(make_shared<Mage>());

	RenderVisitor render;
	AIVisitor ai;


	cout << "-------------------- Render Phase --------------------" << endl;
	for (auto& character : characters)
	{
		character->Accept(render);
	}
	cout << "-------------------- AI Phase --------------------" << endl;
	for (auto& character : characters)
	{
		character->Accept(ai);
	}


	// 对象池模式
	ObjectPool<Bullet> bulletPool(3);
	Bullet* b1 = bulletPool.AcquireObject();
	b1->fire(1, 1);

	Bullet* b2 = bulletPool.AcquireObject();
	b1->fire(2, 2);

	Bullet* b3 = bulletPool.AcquireObject();
	b1->fire(3, 3);

	Bullet* b4 = bulletPool.AcquireObject();
	b1->fire(4, 4);

	b1->Update();
	b2->Update();
	b3->Update();
	b4->Update();

	bulletPool.ResetAll();


	// 服务定位模式
	ServiceLocator::GetAudio()->PlaySound("gunshot");
	ServiceLocator::Provide(std::make_shared<SDLAudioServide>());
	ServiceLocator::GetAudio()->PlaySound("explosion");


	// 组件模式
	Entity Actor;
	auto* comp = Actor.AddComponent<MovementComponent>();
	comp->SetSpeed(10.f);

	Actor.AddComponent<RenderComponent>();

	for (int i = 0; i < 3; i++)
	{
		cout << "---------------" << "Frame: " << i << "---------------" << endl;
		Actor.Update(0.016f);
	}


	// 数据驱动模式
	SkillSystem skillSystem;
	skillSystem.Load("skills.json");

	skillSystem.UseSkill(0);
	skillSystem.UseSkill(1);


	// 黑板模式
	std::shared_ptr<Blackboard> bb = make_shared<Blackboard>();

	PerceptionSystem perception(bb);
	AttackSystem attack(bb);

	perception.Tick();
	attack.Tick();


	// 双重缓冲区
	DoubleBuffer<int> db;

	std::thread write([&]()
	{
		for (int i = 0; i < 5; i++)
		{
			db.Write(i);
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	});
	
	std::thread read([&]()
	{
		for (int f = 0; f < 5; f++)
		{
			db.Swap();
			auto data = db.Read();
			cout << "[Frame: " << f << "] Read buffer: ";
			for (auto& d : data) cout << d << " " << endl;
			cout << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	});

	write.join();
	read.join();


	
	// 游戏循环模式
	Game game;

	bool isRunning = true;
	const float targetFrameTime = 1.f / 60.f;
	auto lastTime = std::chrono::high_resolution_clock::now();

	while (isRunning)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> elapsed = currentTime - lastTime;
		float deltaTime = elapsed.count();
		lastTime = currentTime;

		game.ProcessInput();

		game.Update(deltaTime);

		game.Render();

		static int frameCount = 0;
		if (++frameCount > 3)
		{
			isRunning = false;
		}

		// 固定帧率
		auto frameEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> frameDuration = frameEnd - currentTime;
		if (frameDuration.count() < targetFrameTime)
		{
			std::this_thread::sleep_for(
				std::chrono::duration<float>(targetFrameTime - frameDuration.count())
			);
		}

	}


	// 帧同步
	GameState gameState;
	const int totalFrame = 5;
	const int players = 2;

	// <每一帧, 对应的动作>
	std::map<int, std::vector<PlayerCommand>> CommandBuffer;

	for (int frame = 1; frame <= totalFrame; frame++)
	{
		// 当前帧所有动作
		std::vector<PlayerCommand> currentFrameCommands;

		// 模拟网络操作中已经收集到每个晚间当前帧的输入
		for (int p = 0; p < players; p++)
		{
			PlayerCommand cmd{ p, "Move_" + std::to_string(frame) };
			currentFrameCommands.push_back(cmd);
		}


		CommandBuffer[frame] = currentFrameCommands;

		gameState.frameNumber = frame;
		gameState.ApplyCommand(CommandBuffer[frame]);
		gameState.PrintState();

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}


	// 事件队列
	EventQueue eq;

	std::thread producer([&]()
		{
		for (int i = 0; i < 5; i++)
		{
			eq.Push({ i, "Data" + std::to_string(i) });
			std::cout << "[Producer] Event " << i << "pushed" << std::endl;

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	});

	std::thread consumer([&]()
	{
		for (int i = 0; i < 5; i++)
		{
			Event e;
			while (!eq.Pop(e))
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			cout << "[Consumer] Handling event_" << e.id << " --> " << e.payload << std::endl;
		};
	});


	producer.join();
	consumer.join();


	// 服务提供者模式
	ServiceProvider provider;

	provider.Register<ILogger>("Console", []()
	{
		return std::make_shared<ConsoleLogger>();
	});

	provider.Register<ILogger>("File", []()
	{
		return std::make_shared<FileLogger>();
	});

	auto logger1 = provider.Get<ILogger>("Console");
	logger1->Log("Log from ConsoleLogger");

	auto logger2 = provider.Get<ILogger>("File");
	logger2->Log("Log from FileLogger");


	// 并发与多线程设计模式






	// End



	// MVC 设计模式
	if (false)
	{
		CounterModel model;
		CounterView view;
		CounterController controller(model, view);

		view.Show(model.GetValue());

		string  cmd;

		while (true)
		{
			std::cout << "Command (inc/set/quit): " << std::endl;
			cin >> cmd;

			if (cmd == "quit")
			{
				break;
			}

			controller.OnUserInput(cmd);

		}
	}


	// MVP
	if (false)
	{
		UserModel _model;

		ConsoleLoginView _view(nullptr);
		LoginPresenter _presenter(_view, _model);
		_view = ConsoleLoginView(&_presenter);

		ConsoleLoginView realView(&_presenter);
		realView.Show();
	}





	// ECS 
	ECS::ComponentManager cm;
	ECS::Entity e1 = 1;
	ECS::Entity e2 = 2;

	cm.addPosition(e1, 0, 0);
	cm.addVelocity(e1, 1, 1);

	cm.addPosition(e2, 10, 10);
	cm.addVelocity(e2, -1, 0);

	ECS::MovementSystem movementSysytem;
	
	movementSysytem.Update(cm, 1.f);
	movementSysytem.Update(cm, 1.f);



	// FSM

	FSM::FSM fsm;
	auto idle = std::make_shared<FSM::IdleState>();
	auto walking = std::make_shared<FSM::WalkingState>();

	fsm.changeState(idle);
	fsm.Update();

	fsm.changeState(walking);
	fsm.Update();

	fsm.changeState(idle);
	fsm.Update();


	// HFSM
	auto parent = std::make_shared<HFSM::ParentState>();
	auto child = std::make_shared<HFSM::ChildState>();

	parent->addChild(child);

	parent->enter();
	parent->execute();
	parent->exit();




	return 0;
}