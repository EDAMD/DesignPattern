#pragma once
#include <iostream>
#include <map>
#include <string>

/*解释器设计模式
* 将语法规则用类封装
* 易于扩展新的语法
* 支持运行时动态解析与执行
* 
* 优点:
* 1.语法规则添加修改方便
* 2.代码风格与业务规则高度一致, 可读性好
* 3.灵活支持不同类型的语法结构
* 
* 缺点:
* 1.对于复杂语法, 类数量会急剧增加
* 2.大型语言解释效率低
* 3.不太适合复杂的文法
* 
* 适用场景:
* 游戏 AI 脚本 MassAI
* UI布局规则解释
* 游戏策划配置公式解析
*/


class Expression
{
public:
	virtual ~Expression() = default;
	virtual int Interpret(std::map<std::string, int>& context) = 0;
};

class VariableExpression : public Expression
{
public:
	VariableExpression(const std::string& name) : name(name) {}

	virtual int Interpret(std::map<std::string, int>& context) override
	{
		return context[name];
	}

private:
	std::string name;
};

class ConstantExpression : public Expression
{
public:
	ConstantExpression(int value) : value(value) {}

	virtual int Interpret(std::map<std::string, int>& context) override
	{
		return value;
	}

private:
	int value;
};

class AddExpression : public Expression
{
public:
	AddExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
		: left(left), right(right) { }

	virtual int Interpret(std::map<std::string, int>& context) override
	{
		return left->Interpret(context) + right->Interpret(context);
	}

private:
	std::shared_ptr<Expression> left, right;
};

class SubExpression : public Expression
{
public:
	SubExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
		: left(left), right(right) {}

	virtual int Interpret(std::map<std::string, int>& context) override
	{
		return left->Interpret(context) - right->Interpret(context);
	}

private:
	std::shared_ptr<Expression> left, right;
};