#pragma once

#include <iostream>
#include <string>

/*MVC架构
* 解耦
* 可维护性高
* 可扩展
* 可测试
* 
* 优点:
* 1.清晰的分层结构
* 2.UI 数据 逻辑 完全分离
* 3.易于多人协作
* 
* 缺点:
* 1.对小项目可能增加代码量
* 2.三者交互需要一定的设计约定
* 
*/

class CounterModel
{
public:
	void SetValue(int val) { value = val; }
	int GetValue() { return value; }
	void Increment() { ++value; }

public:
	int value = 0;
};

class CounterView
{
public:
	void Show(int value)
	{
		std::cout << "[View] Counter value: " << value << std::endl;
	}
};

class CounterController
{
public:
	CounterController(CounterModel& m, CounterView& v) : model(m), view(v) {}

	void OnUserInput(std::string& input)
	{
		if (input == "inc")
		{
			model.Increment();
			view.Show(model.GetValue());
		}
		else if (input == "set")
		{
			int val;
			std::cout << "Enter Value: ";
			std::cin >> val;
			model.SetValue(val);
			view.Show(model.GetValue());
		}
		else
		{
			std::cout << "Unknow Command." << std::endl;
		}
	}

private:
	CounterModel& model;
	CounterView& view;
};
