#pragma once
#include <iostream>

/* 桥接模式 - 将抽象部分与实现部分分离, 使他们可以独立变化. 通过组合关系, 将抽象接口与具体实现解耦
* 1.分离抽象与实现, 使两部分可以独立扩展
* 2.用组合替代继承, 减少类之间的强耦合
* 3.适用于需要在多个维度上扩展的系统
* 
* 优点:
* 1.抽象和实现可以独立变化, 减少类爆炸问题.
* 2.系统扩展性强, 可以任意组合实现层与抽象层
* 3.避免了多层继承带来的问题
* 
* 缺点:
* 1.引入额外的抽象层结构, 理解和实现成本略高
* 
* 使用场景:
* 1.多维度变化的类结构
* 2.运行时切换实现
* 3.希望解耦抽象接口与实际实现
* 
*/


// 抽象层接口
class Device
{
public:
	virtual ~Device() = default;

	virtual void On() = 0;
	virtual void Off() = 0;
	virtual void SetVolume(int percent) = 0;
};

//
class TV : public Device
{
public:
	virtual void On() override { std::cout << "TV is On" << std::endl; }
	virtual void Off() override { std::cout << "TV is Off" << std::endl; }

	virtual void SetVolume(int percent) override { std::cout << "TV Volume: " << percent << std::endl; }	
};

class Radio : public Device
{
public:
	virtual void On() override { std::cout << "TV is On" << std::endl; }
	virtual void Off() override { std::cout << "TV is Off" << std::endl; }

	virtual void SetVolume(int percent) override { std::cout << "Radio Volume: " << percent << std::endl; }
};


// 抽象控制
// 控制逻辑 - 使用组合方式而非继承, 灵活性更高
class RemoteControl
{
public:
	RemoteControl(std::shared_ptr<Device> dev) : device(dev) {}
	virtual ~RemoteControl() = default;

	virtual void TurnOn() { device->On(); }
	virtual void TurnOff() { device->Off(); }

	virtual void VolumeUp() { device->SetVolume(50); }

protected:
	std::shared_ptr<Device> device;
};

class AdvancedRemote : public RemoteControl
{
public:
	AdvancedRemote(std::shared_ptr<Device> dev) : RemoteControl(dev) {}
	
	void Mute() 
	{ 
		std::cout << "[AdvancedRemote] Muting" << std::endl;
		device->SetVolume(0); 
	}
};












