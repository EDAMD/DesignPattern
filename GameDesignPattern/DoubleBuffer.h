#pragma once

#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>

/*双缓冲区模式
* 避免读写冲突
* 减少数据拷贝
* 提高实时性
* 
* 优点:
* 1.保证读写数据互不干扰
* 2.减少同步等待时间
* 3.实现简单
* 
* 缺点:
* 1.需要额外内存
* 2.切换时需要同步处理
* 3.数据延迟一个缓冲 周期
* 
* 适用场景:
* 
*/

template<typename T>
class DoubleBuffer
{
public:
	DoubleBuffer() : writeIndex(0), readIndex(1) {}

	void Write(const T& value)
	{
		std::lock_guard<std::mutex> lock(mtx);
		buffers[writeIndex].push_back(value);
	}

	void Swap()
	{
		std::lock_guard<std::mutex> lock(mtx);
		std::swap(writeIndex, readIndex);
		buffers[writeIndex].clear();
	}

	std::vector<T> Read()
	{
		std::lock_guard<std::mutex> lock(mtx);
		return buffers[readIndex];
	}

private:
	std::vector<T> buffers[2];
	int writeIndex;
	int readIndex;
	std::mutex mtx;
};
