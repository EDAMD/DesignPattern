#pragma once
#include <iostream>

using namespace std;

/*模板模式
* 固定算法骨架, 约束子类执行步骤的顺序
* 把变化的部分(步骤)交给子类实现 --- 可扩展性, 而不改动高层的逻辑
* 避免子类改变流程结构, 保证流程一致性
* 
* 优点:
* 1.流程控制集中在父类, 便于维护
* 2.子类专注实现变化逻辑, 提高复用性
* 3.符合开闭原则, 新增流程变化只需添加子类
* 
* 缺点:
* 1.父类对子类有较强约束性, 灵活性较低 ---> 延迟渲染
* 2.对扩展流程结构的变化支持差(结构改要改父类)
* 
* 适用场景:
* 游戏生命周期的管理, 网络数据包的解析
* 
* UE:
* BeginPlay(), Tick(), EndPlay()
*/

class GameModeBase
{
public:
	virtual ~GameModeBase() = default;

	void StartGame()
	{
		LoadAssets();
		InitWorld();
		SpawnPlayer();
		BeginPlaye();

		cout << "Game Started !!!" << endl;
	}

protected:
	void LoadAssets()
	{
		cout << "Loading game assets..." << endl;
	}

	void InitWorld()
	{
		cout << "Initializing world..." << endl;
	}

protected:
	virtual void SpawnPlayer() = 0;
	virtual void BeginPlaye() = 0;

};

class ShooterGame : public GameModeBase
{
protected:	
	virtual void SpawnPlayer()override
	{
		cout << "Spawning shooter palyer with rifle..." << endl;
	}
	virtual void BeginPlaye() override
	{
		cout << "Shooter game started: Enemies are spawned..." << endl;
	}
};

class RacingGame : public GameModeBase
{
protected:
	virtual void SpawnPlayer()override
	{
		cout << "Spawning racer palyer with car..." << endl;
	}
	virtual void BeginPlaye() override
	{
		cout << "Racing game started: Countdown begins..." << endl;
	}
};
