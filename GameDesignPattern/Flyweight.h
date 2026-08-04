#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

/*享元设计模式
* 节省内存
* 提高性能
* 解耦外部状态
* 
* 优点:
* 1.显著减少内存占用(特别是大规模对象场景)
* 2.内部状态共享后, 数据在缓存中的命中率提升
* 
* 缺点:
* 1.系统变得复杂(需要区分内部/外部状态)
* 2.外部状态管理成本提高
* 
* 适用场景:
* 1.需要大量重复对象
* 2.对象数量庞大
* 3.频繁创建销毁对象性能开销大
* 
* UE中:
* UStaticMeshComponent(StaticMesh) MaterialInstance Niagara ParticleSystem SoundCue SoundWave
* 
*/

class TreeModel
{
public:
	TreeModel(const std::string& mesh, const std::string& texture)
		:meshData(mesh), textureData(texture)
	{}

	void Render(int x, int y)
	{
		std::cout << "Render Tree Mesh: " << meshData
			<< ", Texture: " << textureData
			<< " at: (" << x << ", " << y << ")" << std::endl;
	}
	
private:
	std::string meshData;
	std::string textureData;
};

class TreeModelFactory
{
public:
	std::shared_ptr<TreeModel> GetTreeModel(const std::string& mesh, const std::string& texture)
	{
		const std::string key = mesh + "|" + texture;
		auto it = models.find(key);
		if (it != models.end())
		{
			return it->second;
		}

		auto model = std::make_shared<TreeModel>(mesh, texture);
		models[key] = model;
		return model;
	}

private:
	std::unordered_map<std::string, std::shared_ptr<TreeModel>> models;
};

struct Tree
{
	int x, y;
	std::shared_ptr<TreeModel> model;

	void Render()
	{
		model->Render(x, y);
	}
};