/**
	병기 생산량을 계산합니다.
	@param city 도시
	@param actors 실행 무장
	@param weapon_id #병기Id
*/
int PK_병기생산(City city, const arrayptr<Person> &in actors, int weapon_id)
{
	if (!병기Id_isValid(weapon_id))
		return 0;

	if (weapon_id >= 병기_충차)
		return 1;

	int skill_id = -1;
	if (weapon_id <= 병기_노)
		skill_id = 기타xml().병기생산대장간특기;
	else if (weapon_id == 병기_군마)
		skill_id = 기타xml().병기생산마구간특기;

	int sum = 0, max = std::INT32_MIN;
	bool has_skill = false;

	for (int i = 0; i < 3; i++)
	{
		if (!isalive(actors[i]))
			continue;

		int n = actors[i].능력[기타xml().병기생산능력];

		sum += n;
		max = std::max(max, n);

		if (actors[i].hasSkill(skill_id))
			has_skill = true;
	}

	int result = sum + max + 200;
	result *= 5;
	if (has_skill)
		result *= 2;
	result *= func_5c7040(city, weapon_id);

	if (Scenario().난이도 == 난이도_특급 && !city.isPlayer())
		result *= 2;

	return result;
}

float func_5c7040(City city, int weapon_id)
{
	int lv1 = 0, lv2 = 0;

	switch (weapon_id)
	{
	case 병기_창:
	case 병기_극:
	case 병기_노:
		for (int i = 0; i < city.개발지수; i++)
		{
			Building building = city.개발지[i].건물;
			if (!isalive(building))
				continue;

			switch (building.시설)
			{
			case 시설_대장간: if (building.건설완료) lv1++; else 1; break;
			case 시설_대장간2단: if (building.건설완료) lv2++; else lv1++; break;
			case 시설_대장간3단: if (building.건설완료) 1; else lv2++; break;
			}
		}
		if (city.무기생산가능카운트 > lv1 + lv2)
			return 1.5f;
		else if (city.무기생산가능카운트 > lv1)
			return 1.2f;
		break;

	case 병기_군마:
		for (int i = 0; i < city.개발지수; i++)
		{
			Building building = city.개발지[i].건물;
			if (!isalive(building))
				continue;

			switch (building.시설)
			{
			case 시설_마구간: if (building.건설완료) lv1++; else 1; break;
			case 시설_마구간2단: if (building.건설완료) lv2++; else lv1++; break;
			case 시설_마구간3단: if (building.건설완료) 1; else lv2++; break;
			}
		}
		if (city.군마생산가능카운트 > lv1 + lv2)
			return 1.5f;
		else if (city.군마생산가능카운트 > lv1)
			return 1.2f;
		break;
	}
	return 1.0f;
}