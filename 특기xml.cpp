namespace u {

/** 특기 확인 */
bool hasSkill(const arrayptr<Person> &in member, int skill_id)
{
	for (int i = 0; i < 3; i++)
	{
		if (member[i] && member[i].hasSkill(skill_id))
			return true;
	}
	return false;
}

/** 특기 상수 최대 값 */
int getSkillInt(const arrayptr<Person> &in member, int skill_id, int n = 0)
{
	int value = 0;
	for (int i = 0; i < 3; i++)
	{
		if (member[i] && member[i].hasSkill(skill_id))
			value = std::max(value, 무장xml(member[i].getId()).getInt(skill_id, n));
	}
	return value;
}

/** 특기 상수 최대 값 */
int getSkillInt(Unit unit, int skill_id, int n = 0)
{
	int value = 0;
	for (int i = 0; i < 3; i++)
	{
		int person_id = unit.무장[i];
		Person person(person_id);
		if (isalive(person) && person.hasSkill(skill_id))
			value = std::max(value, 무장xml(person_id).getInt(skill_id, n));
	}
	return value;
}

/** 특기 상수 최대 값 */
float getSkillFloat(const arrayptr<Person> &in member, int skill_id, int n = 0)
{
	float value = 0;
	for (int i = 0; i < 3; i++)
	{
		if (member[i] && member[i].hasSkill(skill_id))
			value = std::max(value, 무장xml(member[i].getId()).getFloat(skill_id, n));
	}
	return value;
}

/** 특기 상수 최대 값 */
float getSkillFloat(Unit unit, int skill_id, int n = 0)
{
	float value = 0;
	for (int i = 0; i < 3; i++)
	{
		int person_id = unit.무장[i];
		Person person(person_id);
		if (isalive(person) && person.hasSkill(skill_id))
			value = std::max(value, 무장xml(person_id).getFloat(skill_id, n));
	}
	return value;
}

/** 불굴 조건 비교 */
bool test_fukutsu(Unit unit)
{
	int n = 0;
	int troops = unit.병력;
	for (int i = 0; i < 3; i++)
	{
		int person_id = unit.무장[i];
		Person person(person_id);
		if (isalive(person) && person.hasSkill(특기_불굴))
		{
			if (troops < 무장xml(person_id).getInt(특기_불굴, 0))
				n = std::max(n, 무장xml(person_id).getInt(특기_불굴, 1));
		}
	}
	return randbool(n);
}

/** 금강 조건 비교 */
bool test_kongou(Unit unit, int damage)
{
	int n = 0;
	for (int i = 0; i < 3; i++)
	{
		int person_id = unit.무장[i];
		Person person(person_id);
		if (isalive(person) && person.hasSkill(특기_금강))
		{
			if (damage < 무장xml(person_id).getInt(특기_금강, 0))
				n = std::max(n, 무장xml(person_id).getInt(특기_금강, 1));
		}
	}
	return randbool(n);
}

} // namespace u