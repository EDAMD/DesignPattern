#pragma once

#include <iostream>
#include <thread>
#include <chrono>

/*游戏循环模式
* 统一控制游戏节奏
* 保证实时交互
* 跨平台一致
* 帧率与时间控制
* 
* 优点:
* 1.可控的游戏进程
* 2.易于管理个系统顺序
* 3.帧率控制方便
* 
* 缺点:
* 1.难以与操作系统 GUI 或 事件驱动架构直接混用
* 2.需要额外处理变帧率造成的物理计算不稳定问题
* 
* 适用场景
*/

class Game
{
public:
	void ProcessInput()
	{
		std::cout << "[Input] Processing palyer input..." << std::endl;
	}

	void Update(float deltaTime)
	{
		std::cout << "[Update] Updating game wordl dt = " << deltaTime << "seconds" << std::endl;
	}

	void Render()
	{
		std::cout << "[Render] Drawing frame to screen" << std::endl;
	}
};
