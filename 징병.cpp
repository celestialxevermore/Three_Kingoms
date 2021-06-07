/**
	징병 후 병력 증감값을 계산합니다.
	@param building 거점
	@param actors 실행 무장
*/
int PK_징병_병력증감(Building building, const arrayptr<Person> &in actors)
{
	if (!isalive(building) || !isalive(actors[0]))
		return 0;

	City city = building.toCity();
	if (!isalive(city))
		return 0;

	int sum = 0, mul = 10;
	for (int i = 0; i < 3; i++)
	{
		if (isalive(actors[i]))
		{
			sum += actors[i].능력[기타xml().징병능력];
			if (actors[i].hasSkill(특기_명성))
				mul = 15;
		}
	}

	int result = city.치안 + 20;
	result *= sum;
	result *= 5;
	result /= 100;
	result += 1000;
	result *= mul;
	result /= 10;
	result *= func_5c4600(city);

	if (Scenario().난이도 == 난이도_특급 && !city.isPlayer())
		result *= 2;

	if (building.hasEnemy())
		result /= 2;

	return result;
}

float func_5c4600(City city)
{
	int lv1 = 0, lv2 = 0;

	for (int i = 0; i < city.개발지수; i++)
	{
		Building building = city.개발지[i].건물;
		if (!isalive(building))
			continue;

		switch (building.시설)
		{
		case 시설_병영: if (building.건설완료) lv1++; else 1; break;
		case 시설_병영2단: if (building.건설완료) lv2++; else lv1++; break;
		case 시설_병영3단: if (building.건설완료) 1; else lv2++; break;
		}
	}

	if (city.징병가능카운트 > lv1 + lv2)
		return 1.5f;
	else if (city.징병가능카운트 > lv1)
		return 1.2f;
	return 1.0f;
}

/**
	징병 후 도시의 치안 증감값을 계산합니다.
	@param city 도시
	@param actors 실행 무장
	@param troops 징병된 병사 수(PK_병력증감 반환 값)
*/
int PK_징병_치안증감(City city, const arrayptr<Person> &in actors, int troops)
{
	int sum = 0;
	for (int i = 0; i < 3; i++)
	{
		if (isalive(actors[i]))
			sum += actors[i].능력[기타xml().징병능력];
	}
	return -(troops / (sum + 100));
}