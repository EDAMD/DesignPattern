#pragma once

#include "simple_library/public/simple_library.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

/*数据驱动模式
*
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
