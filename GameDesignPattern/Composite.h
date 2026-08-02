#pragma once
#include <iostream>
#include <vector>
#include <string>

/*组合模式
* 统一处理单个对象与对象集合
* 层次化结构管理复杂对象
* 可扩展性高
* 
* 优点:
* 1.客户端代码可以一致对待单个对象和组合对象
* 2.容易增加新类型的组件
* 3.简化了复杂结构的操作
* 
* 缺点:
* 1.使设计变得更加抽象, 节点访问具体类型时可能需要 RTTI 或 类型转换 cast
* 2.限制对于组件的特化操作(因为统一了接口)
* 
* 使用场景
* 1.需要表示 部分-整体 层次结构的场景
* 2.希望客户端对 单个对象和组合对象 的使用保持一致. 类似 Actor
* 3.需要构建树形结构并能透明地操作各层节点
*/

class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void ShowInfo(int depth = 0) = 0;

	virtual void Add(std::shared_ptr<GameObject> child) {}
	virtual void Remove(std::shared_ptr<GameObject> Child) {}
};

class Mesh : public GameObject
{
public:
	Mesh(std::string name) : Name(name) {}
	void ShowInfo(int depth = 0) override
	{
		std::cout << std::string(depth, '-') << "Mesh: " << Name << std::endl;
	}
private:
	std::string Name;
};

class Light : public GameObject
{
public:
	Light(std::string name) : Name(name) {}
	void ShowInfo(int depth = 0) override
	{
		std::cout << std::string(depth, '-') << "Light: " << Name << std::endl;
	}
private:
	std::string Name;
};

class SceneNode : public GameObject
{
public:
	SceneNode(std::string name) : Name(name) {}

	void Add(std::shared_ptr<GameObject> child) override
	{
		childern.push_back(child);
	}

	void Remove(std::shared_ptr<GameObject> child) override
	{
		childern.erase(std::remove(childern.begin(), childern.end(), child), childern.end());
	}

	void ShowInfo(int depth = 0) override
	{
		std::cout << std::string(depth, '-') << "Node: " << Name << std::endl;
		for (auto& child : childern)
		{
			child->ShowInfo(depth + 2);
		}
	}
private:
	std::string Name;
	std::vector<std::shared_ptr<GameObject>> childern;
};
