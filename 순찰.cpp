/**
	순찰 후 치안 증감값을 계산합니다.
	@param building 거점
	@param actors 실행 무장
*/
int PK_순찰_치안증감(Building building, const arrayptr<Person> &in actors)
{
	if (!isalive(building) || !isalive(actors[0]))
		return 0;

	City city = building.toCity();
	if (!isalive(city))
		return 0;

	int n = 0;
	for (int i = 0; i < 3; i++)
	{
		if (isalive(actors[i]))
			n += actors[i].능력[기타xml().순찰능력];
	}
	n = n / 28 + 2;
	if (building.hasEnemy())
		n /= 2;
	return n;
}