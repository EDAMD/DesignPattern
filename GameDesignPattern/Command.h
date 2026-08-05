#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>

/*命令模式
* 解耦调用者与执行者
* 支持操作撤销/重做
* 请求持久化/排队执行
* 可组合复杂命令(宏命令)
* 
* 优点:
* 1.封装请求, 方便保存, 传输和重用
* 2.灵活添加新命令而不影响现有代码
* 3.很适合做撤销, 重做, 宏操作, 历史记录
* 
* 缺点:
* 1.可能会增加系统的类数量
* 2.对于非常简单的操作, 命令模式稍显笨重
* 
* 适用场景:
* 1.编辑器的撤销 / 重做功能
* 2.游戏角色技能系统
* 3.键盘/输入映射
* 4.宏录制, 批量执行一系列操作
* 5.任务队列的异步执行
* 
* UE: FScopedTransaction-> 修改值, 调用 modify()函数记录修改, 然后就可以撤销
* 行为树
* RPC
* 时间轴
* 
*/

class ICommand
{
public:
	virtual ~ICommand() = default;

	virtual void Execute() = 0;
	virtual void Undo() = 0;
};

class LightElement
{
public:
	void On() { std::cout << "[Light] Turned On" << std::endl; }
	void Off() { std::cout << "[Light] Turned Off" << std::endl; }
};

class LightOnCommand : public ICommand
{
public:
	LightOnCommand(LightElement& light) : m_Light(light) {}

	virtual void Execute() override { m_Light.On(); }
	virtual void Undo() override { m_Light.Off(); }

private:
	LightElement& m_Light;
};

class LightOffCommand : public ICommand
{
public:
	LightOffCommand(LightElement& light) : m_Light(light) {}

	virtual void Execute() override { m_Light.Off(); }
	virtual void Undo() override { m_Light.On(); }

private:
	LightElement& m_Light;
};

class RemoteControlElement
{
public:
	void SetCommand(std::shared_ptr<ICommand> command)
	{
		m_command = command;
	}

	void PressButtom()
	{
		if (m_command)
		{
			m_command->Execute();
			history.push(m_command);
		}
	}

	void PressUndo()
	{
		if (!history.empty())
		{
			history.top()->Undo();
			history.pop();
		}
	}

private:
	std::shared_ptr<ICommand> m_command;
	std::stack<std::shared_ptr<ICommand>> history;
};