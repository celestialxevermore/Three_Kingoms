/**
	본거지가 발생할 확률을 계산합니다.
	@param city 도시
*/
int PK_본거지발생확률(City city) {
	// 1월부터 6월까지 발생 금지
	if (Scenario().getElapsedMonths() <= 6)
		return 0;

	// 중복 발생 금지
	int city_id = city.getId();
	for (auto i = Scenario().건물.begin(); i; i++) {
		Building building = i();
		if (isalive(building) && (building.시설 == 시설_본거지1 || building.시설 == 시설_본거지2) && building.getAreaCityId() == city_id)
			return 0;
	}

	// 치안이 기준치를 넘을 경우 발생하지 않음.
	if (city.치안 >= 80 + (city.toBuilding().hasSkill(특기_위압) ? -20 : 0))
		return 0;

	// 기준치를 넘지 못할 경우 발생 확률.
	return (100 - city.치안) / 3;
}