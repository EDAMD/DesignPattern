#pragma once
#include <iostream>
#include <vector>
#include <stack>

 /*备忘录模式
 * 保存对象状态
 * 随后恢复状态
 * 实现撤销/重做功能
 * 
 * 优点:
 * 1.保持封装性, 不暴露对象的内部实现
 * 2.可以很容易地实现多次撤销与重做
 * 3.使得 "发起人" 的代码与状态历史管理解耦
 * 
 * 缺点:
 * 1.存储历史状态可能消耗大量内存
 * 2.保存和恢复状态 存在一定性能开销
 * 
 * 适用场景:
 * 游戏存档读档, 编译器撤销功能
 * 场景快照, 回滚
 */

class Memento
{
public:
	Memento(const std::string& state) : state(state) {}
	std::string GetState() { return state; }

private:
	std::string state;
};

class  TextEditor
{
public:

	void SetText(const std::string& text)
	{
		this->text = text;
	}

	std::string GetText()
	{
		return text;
	}

	std::shared_ptr<Memento> Save() const
	{
		return std::make_shared<Memento>(text);
	}

	void Restore(std::shared_ptr<Memento> memento)
	{
		if (memento)
		{
			this->text = memento->GetState();
		}
	}
private:
	std::string text;
};

class History
{
public:
	void Push(std::shared_ptr<Memento> memento)
	{
		history.push(memento);
	}

	std::shared_ptr<Memento> Pop()
	{
		if (history.empty()) return nullptr;
		
		auto tmp = history.top();
		history.pop();
		return tmp;
	}

private:
	std::stack<std::shared_ptr<Memento>> history;
};