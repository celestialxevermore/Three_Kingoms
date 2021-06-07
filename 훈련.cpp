/**
	훈련 후 기력 증감값을 계산합니다.
	@param building 거점
	@param actors 실행 무장
*/
int PK_훈련_기력증감(Building building, const arrayptr<Person> &in actors)
{
	if (!isalive(building) || !isalive(actors[0]))
		return 0;

	int sum = 0, max = std::INT32_MIN;
	for (int i = 0; i < 3; i++)
	{
		if (!isalive(actors[i]))
			continue;

		int n = actors[i].능력[기타xml().훈련능력];

		sum += n;
		max = std::max(max, n);
	}

	int result = sum + max;
	result /= std::min(building.병력 / 2000 + 20, 100);
	result += 3;

	// 연병소가 있다면 1.5배
	if (building.시설 == 시설_도시 && building.toCity().hasFacility(시설_연병소))
		result = result * 3 / 2;

	return result;
}