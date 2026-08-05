#pragma once
#include <iostream>

/*责任链设计模式 
* 解耦请求发送者与处理者
* 动态组合处理链
* 避免大量 if-else / switch-case
* 
* 优点:
* 1.请求发送者与处理者解耦
* 2.处理者可以灵活扩展与替换
* 3.链结构可以动态变化
* 
* 缺点:
* 1.链太长可能影响性能
* 2.如果没有处理者能处理, 默认丢弃(除非记录日志)
* 3.排查问题可能相对困难
* 
* 适用场景(客户端向服务器发送请求, 服务器寻找空闲线程处理)
* 1.多个对象可以处理一个请求, 且处理者运行时动态确定
* 2.需要在不同处理者之间转发请求
* 3.替代大量if-else分支结构
* 
* 游戏输入处理, UI消息传递, 游戏逻辑事件派发
* 
* UE: Input Procession 行为树
*
*/

class Handler
{
public:
	virtual ~Handler() = default;

	void SetNext(std::shared_ptr<Handler> nextHandler)
	{
		next = nextHandler;
	}

	void HandleRequest(const std::string& request)
	{
		if (CanHandle(request))
		{
			Process(request);
		}
		else if (next)
		{
			next->HandleRequest(request);
		}
		else
		{
			std::cout << "[Handler] No one could handle: " << request << std::endl;
		}
	}

protected:
	virtual bool CanHandle(const std::string& request) = 0;
	virtual void Process(const std::string& request) = 0;

	std::shared_ptr<Handler> next;
};

class ConcreteHandlerA : public Handler
{
protected:
	virtual bool CanHandle(const std::string& request)
	{
		return request == "TypeA";
	}
	virtual void Process(const std::string& request)
	{
		std::cout << "[HandlerA] Handling request: " << request << std::endl;
	}
};

class ConcreteHandlerB : public Handler
{
protected:
	virtual bool CanHandle(const std::string& request)
	{
		return request == "TypeB";
	}
	virtual void Process(const std::string& request)
	{
		std::cout << "[HandlerB] Handling request: " << request << std::endl;
	}
};
