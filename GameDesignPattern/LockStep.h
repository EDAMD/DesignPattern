#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <map>
#include <thread>

/*帧同步模式
* 状态一致
* 减少带宽
* 防止状态漂移
* 
* 优点:
* 1.带宽占用及低
* 2.逻辑帧完全对齐, 一致性强
* 
* 缺点:
* 1.需要严格的确定性逻辑
* 2.网络延迟会直接影响帧进度
* 3.状态回滚机制变成复杂
* 
* 适用场景:
* RTS游戏, 格斗类, mmo, moba, 回合制
* 模拟器联机
* 低宽带竞技对战
* 
* UE:
* 服务器收集所有输入 -> 广播输入到所有客户端 -> 所有客户端以固定时间步计算
*/ 

struct PlayerCommand
{
	int playerId;
	std::string action;
};

struct GameState
{
	int frameNumber = 0;
	std::map<int, std::string> playerState;

	void ApplyCommand(const std::vector<PlayerCommand> commands)
	{
		for (auto& com : commands)
		{
			playerState[com.playerId] = com.action;
		}
	}

	void PrintState()
	{
		std::cout << "Frame: " << frameNumber << std::endl;
		for (auto& key : playerState)
		{
			std::cout << "Player [" << key.first << "]: " << key.second << std::endl;
		}
	}
};

