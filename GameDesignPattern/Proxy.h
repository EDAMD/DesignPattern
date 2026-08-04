#pragma once
#include <iostream>

/*代理模式
* 控制访问, 延迟加载, 远程代理, 保护代理, 智能引用
* 
* 优点:
* 1.解耦客户端与真实对象的生命周期管理
* 2.可添加额外功能(缓存, 日志, 安全认证等)
* 3.避免不必要的资源消耗(延迟实例化)
* 
* 缺点:
* 1.多了一层间接访问, 略微影响性能
* 2.逻辑复杂度可能提高
* 
* 适用场景:
* 1.延迟加载大资源
* 2.访问控制
* 3.远程调用
* 4.资源管理
* 5.虚拟代理
* 
* UE:
* TSoftObjectPtr, TSoftClassPtr LoadSynchronous BTTask BTService RPC
* 
*/

class IImage
{
public:
	virtual ~IImage() = default;
	virtual void Display() = 0;
};

class RealImage : IImage
{
public:
	RealImage(const std::string& filename) : m_filename(filename)
	{
		LoadFromDisk();
	}

	virtual void Display() override
	{
		std::cout << "[RealImage] Displaying " << m_filename << std::endl;
	}

private:
	void LoadFromDisk()
	{
		std::cout << "[RealImage] loading " << m_filename << "from disk..." << std::endl;
	}

	std::string m_filename;
};

class ProxyImage : IImage
{
public:
	ProxyImage(const std::string& filename) : m_filename(filename) {}

	void Display() override
	{
		if (!realImage)
		{
			realImage = std::make_unique<RealImage>(m_filename);
			realImage->Display();
		}

		realImage->Display();
	}

private:
	std::string m_filename;
	std::unique_ptr<RealImage> realImage;
};
