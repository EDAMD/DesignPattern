#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

/*行为树模式
* 模块化 AI 逻辑
* 可视化编辑
* 易于扩展
* 
* 优点:
* 1.解耦逻辑与执行流程
* 2.清晰的层级与执行规则
* 3.更好的可维护性, 尤其适合 复杂决策
* 
* 缺点:
* 1.对小型项目显得复杂
* 2.如果树过大, 调试成本上升
* 
* UE:
* 行为树
*/

enum class NodeState {Success, Failure, Running};

class BTNode
{
public:
	virtual ~BTNode() = default;
	virtual NodeState Tick() = 0;
};

class SequeueceNode : public BTNode
{
public:
	void AddChild(std::shared_ptr<BTNode> child)
	{
		children.push_back(child);
	}
	
	virtual NodeState Tick() override
	{
		for (auto& child : children)
		{
			NodeState status = child->Tick();
			if (status != NodeState::Success)
			{
				return status;
			}
		}
		return NodeState::Success;
	}
private:
	std::vector<std::shared_ptr<BTNode>> children;
};

class SelectorNode : public BTNode
{
public:
	void AddChild(std::shared_ptr<BTNode> child)
	{
		children.push_back(child);
	}

	virtual NodeState Tick() override
	{
		for (auto& child : children)
		{
			NodeState status = child->Tick();
			if (status == NodeState::Success)
			{
				return NodeState::Success;
			}
		}
		return NodeState::Failure;
	}
private:
	std::vector<std::shared_ptr<BTNode>> children;
};

class ActionNode : public BTNode
{
public:
	ActionNode(std::string name, bool succeed) : actionName(name), succeed(succeed) {}

	virtual NodeState Tick() override
	{
		std::cout << "[执行动作]: " << actionName << std::endl;
		return succeed ? NodeState::Success : NodeState::Failure;
	}

public:
	std::string actionName;
	bool succeed;
};