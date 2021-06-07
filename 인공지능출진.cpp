/**
	출진 가능한 병력수를 계산합니다.
	@details	반환값보다 많은 병력을 가진 거점은 공격하지 않습니다.
				원본을 보시면 알겠지만 군주의 성격이 대담해질수록 과장됩니다.(무모해집니다.)
	@param building	거점
	@param troops	출진 가능한 최대 병력수(구역 내 부대 병력 합 + max(거점 소속 무장 지휘 합, 거점 병력))
*/
int PK_가용병력(Building building, int troops)
{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/*
	// 플레이어 위임 군단의 경우 항상 냉정
	if (building.isPlayer())
		character = 성격_냉정;
	return troops * (Person(Force(building.getForceId()).군주).성격 + 3);
	*/

	return troops * 125 / 100;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}

/**
	출진할 병력수를 계산합니다.
	@details	인접 거점에서 같이 출진하는 병력 수도 포함됩니다.
				아래 표를 보시면 알겠지만 원본 공식으로는 병력이 아무리 많아도 목표 거점 병력 수의 2배 까지만 출진합니다.

				적병력수 1000 기준
				세력순위백분율(강함 <-> 약함)\n성격|100\n\n|80\n\n|60\n\n|40\n\n|20\n\n|2(최소)\n\n
				-|-|-|-|-|-|-
				소심|1950|1850|1750|1650|1550|1460
				냉정|1800|1700|1600|1500|1400|1310
				대담|1650|1550|1450|1350|1250|1160
				저돌|1500|1400|1300|1200|1100|1010
				그리고 세력이 약하고 군주 성격이 대담해질수록 출진하는 병력 수가 줄어듭니다.(무모해집니다.)
	@param src			출진 거점
	@param src_rank		출진 거점 세력 백분율 순위
	@param dst			목표 거점
	@param dst_troops	목표 거점 예상 병력 수(구역 내 부대 병력 합 + max(거점 소속 무장 지휘 합, 거점 병력))
*/
int PK_출진병력(Building src, int src_rank, Building dst, int dst_troops)
{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/*
	int a = Person(Force(src.getForceId()).군주).성격;
	int b = (3 - a) * 15;
	int c = src_rank / 2;
	int result = dst_troops + (dst_troops * (b + c) / 100);
	return std::max(result, 5000);
	*/

	// 빈 거점
	if (dst.getForceId() == -1)
	{
		// 관문이나 항구일 경우 1/5
		if (dst.toGate().p != 0 || dst.toPort().p != 0)
			return dst.최대병력 / 5;

		// 도시일 경우 이웃 도시에 적 세력이 존재한다면 1/2
		Force force(src.getForceId());
		City city(dst.toCity());
		for (int i = 0; i < 6; i++)
		{
			if (city.이웃[i] != -1 && force.isEnemy(City(city.이웃[i]).getForceId()))
				return dst.최대병력 / 2;
		}

		// 안전한 도시일 경우 1/4
		return dst.최대병력 / 4;
	}

	// 병력 수 재계산(다른 세력 부대 병력 수까지 포함)
	int src_force_id = src.getForceId();
	int dst_building_id = dst.getId();
	dst_troops = dst.병력;
	for (auto i = Scenario().부대.begin(); i; i++)
	{
		if (i().getAreaBuildingId() == dst_building_id && i().getForceId() != src_force_id)
			dst_troops += i().병력;
	}

	if (dst_troops > dst.최대병력)
		return dst_troops + dst_troops / 4;

	if (dst_troops * 2 > dst.최대병력)
		return dst.최대병력 + dst.최대병력 / 4;

	return std::max(dst_troops, dst.최대병력 / 4) * 3;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}