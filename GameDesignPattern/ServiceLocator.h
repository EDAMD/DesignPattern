#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

/*服务定位模式
* 集中式服务访问
* 隐藏服务的具体实现
* 动态替换实现
* 
* 优点:
* 1.获取服务简单(类似单例), 全局都能访问
* 2.方便替换服务实现
* 3.某种程度上减少依赖注入的参数传递负担
* 
* 缺点:
* 1.会造成隐式依赖,不利于单元测试
* 2.滥用会导致代码结构不清晰
* 3.服务的生命周期管理需要小心
* 
* 适用场景:
* 游戏核心逻辑: 音频, 输入, 配置
* 切换实现的接口
* RHI
* 
* UE:
* GWorld, GEngine, GEditor, Subsystem, 模块管理
*/

class IAudioService
{
public:
	virtual ~IAudioService() = default;
	virtual void PlaySound(const std::string& name) = 0;
};

class SDLAudioServide : public IAudioService
{
public:
	virtual void PlaySound(const std::string& name) override
	{
		std::cout << "[SDL Aduio] Playing sound: " << name << std::endl;
	}
};

class NullAudioServide : public IAudioService
{
public:
	virtual void PlaySound(const std::string& name) override
	{
		std::cout << "[Null Aduio] (No sound)" << std::endl;
	}
};

class ServiceLocator
{
public:
	static void Provide(std::shared_ptr<IAudioService> service)
	{
		audioService = service;
	}

	static std::shared_ptr<IAudioService> GetAudio()
	{
		if (!audioService)
		{
			audioService = std::make_shared<NullAudioServide>();
		}
		return audioService;
	}


private:
	inline static std::shared_ptr<IAudioService> audioService = nullptr;
};