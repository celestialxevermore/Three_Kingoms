/**
	거점 점령
	@param base	거점
	@param unit	공략한 부대
				건물이 건물을 공격해 점령시킨 경우도 확인하는 코드가 있는데
				그런 경우는 없으므로 부대로 고정시켰습니다.
				혹시 나중에 변경될 수도 있으니 참고하시기 바랍니다.
*/
void PK_흡수(Building base, Unit unit)
{
	Person leader;
	if (isalive(unit))
		leader = unit.주장;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/*
	int n = 5;
	if (isalive(leader))
		n = std::max(leader.매력 / 10, 5);
	*/
	int n = 70;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	base.setGold(base.금 * n / 100);
	base.setFood(base.병량 * n / 100);
	base.setTroops(base.병력 * n / 100);
	if (base.병력 == 0)
		base.setEnergy(0);
	for (int i = 0; i < 병기_끝; i++)
		base.setWeapons(i, base.병기[i] * n / 100);

	City city(base.toCity());
	if (!isalive(city))
		return;

	int city_force_id = city.getForceId();
	int city_id = city.getId();
	List<Building> gov;

	auto i = Scenario().건물.begin();
	for (auto j = i++; j; j = i ? i++ : i)
	{
		if (!isalive(j()))
			continue;

		// 내정시설
		if (j().isGovernmentFacility())
		{
			if (j().getAreaCityId() != city_id)
				continue;

			// 건설중이던 내정시설은 모두 파괴
			if (!j().건설완료)
			{
				// 동작대를 건설중이었다면 보물도 사라짐
				if (j().시설 == 시설_동작대)
				{
					Item item(보물_동작);
					if (isalive(item))
						item.mitoujou();
				}

				Scenario().removeBuilding(j());
			}
			else
			{
				if (j().시설 != 시설_동작대)
					gov.push_back(j());
			}
		}
		// 군사시설
		else if (j().isMilitaryFacility())
		{
			if (!세력Id_isValid(city_force_id) || city_force_id != j().getForceId() || j().getAreaCityId() != city_id)
				continue;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			int distance = Map().getDistance(city.getPos(), j().getPos());
			int n = 0;

			if (distance <= 4)
				n = 75;
			else if (distance <= 8)
				n = 50;
			else
				n = 30;

			if (randbool(n))
			{
				j().changeDistrict(unit.getDistrictId(), 0);
				continue;
			}
			else if (randbool(20))
			{
				continue;
			}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

			Scenario().removeBuilding(j());
		}
	}

	int charisma = 20;
	if (isalive(leader))
		charisma = leader.매력;

	n = gov.size() - std::min(charisma / 20, gov.size());

	// 도적이 점령했다면 모든 내정시설 파괴
	if (!일반세력Id_isValid(unit.세력))
		n = gov.size();

	gov.shuffle();
	for (int i = 0; i < n; i++)
		Scenario().removeBuilding(gov[i]);
}