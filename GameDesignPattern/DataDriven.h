#pragma once

#include "simple_library/public/simple_library.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

/*数据驱动模式
* 将逻辑与数据分离
* 内容可配置
* 快速迭代
* 跨平台复用
* 
* 优点:
* 1.非程序人员可参与修改
* 2.系统通用性高, 易于扩展
* 3.方便做热更新 
* 
* 缺点:
* 1.数据解析需要额外成本
* 2.数据错误容易导致运行时 bug
* 3.逻辑通用化可能会牺牲性能
* 4.很多参数暴露, 没有安全感
* 
* 适用场景:
* 游戏角色, 敌人, 武器配置
* ai行为树, 状态机
* ui样式, 布局
*/

using json = nlohmann::json;

struct SkillData
{
	std::string Name;
	int Damage;
	float Cooldown;
};

std::vector<SkillData> LoadSkillsFromJson(const std::string& fileName)
{
	std::vector<SkillData> skills;

	char buf[1024 * 10] = { 0 };
	if (load_data_from_disk(fileName.c_str(), buf))
	{
		json Data = json::parse(buf);

		for (auto& item : Data)
		{
			SkillData skill;
			skill.Name = item["Name"];
			skill.Damage = item["Damage"];
			skill.Cooldown = item["Cooldown"];
			skills.push_back(skill);
		}
	}
	return skills;
}

class SkillSystem
{
public:
	void Load(const std::string fileName)
	{
		skills = LoadSkillsFromJson(fileName);
	}

	void UseSkill(size_t index)
	{
		const SkillData& skill = skills[index];

		std::cout << "[Use Skill]" << skill.Name << "-> Damage: " << skill.Damage << " Cooldown: " << skill.Cooldown << std::endl;
	}

private:
	std::vector<SkillData> skills;
};
