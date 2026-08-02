#pragma once
#include <iostream>

/* 适配器模式 - 将一个类的接口转换成客户端期望的另一个接口, 使得原本由于接口不兼容而不能一起工作的类可以协同工作
* 1.接口转换
* 2.复用现有代码
* 3.解耦
*
* 优点:
* 1.对已有代码零修改(封闭修改, 开放扩展)
* 2.保持系统稳定性
* 3.方便系统间协作
* 
* 缺点:
* 1.可能增加调用层次, 带来额外开销
* 2.复杂结构下可能使代码可读性降低 RHI
* 
* 使用场景:
* 1.老接口与新需求不兼容, 不想/不能修改老接口
* 2.系统需要使用某些已有的类, 但他们接口不符合系统的需要
* 3.第三方库的接口与系统接口格式不同, 需要做适配
*/

class OldInterface
{
public:
	void OldRequest()
	{
		std::cout << "Call Old Request" << std::endl;
	}
};

class ITarget
{
public:
	virtual ~ITarget() = default;
	virtual void Request() = 0;
};

class Adapter : public ITarget
{
public:
	Adapter(std::shared_ptr<OldInterface> oldObj) : OldObject(oldObj) {}

	virtual void Request() override
	{
		std::cout << "[Adapter] Translating Request -> OldRequest" << std::endl;
		OldObject->OldRequest();
	}
	
private:
	std::shared_ptr<OldInterface> OldObject;
};
