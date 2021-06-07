/**
	건물의 공격(반격) 시 병력 대미지를 계산합니다.
	@param[out] damage	대미지 정보
	@param building		건물
	@param target		목표
*/
void PK_건물공격대미지(__damage damage, Building building, HexObject target)
{
	// 사용하지 않음
	if (target.isInstance(kTypeIdBuilding))
		assert(false);

	Unit unit(target);
	int troops_damage = 0;
	int atk;
	int def;
	int a3;
	int troops;

	switch (building.시설)
	{
	case 시설_도시:
	case 시설_관문:
	case 시설_항구:
		func_5af0e0(atk, troops, a3, def, building);

		troops_damage = int(func_5aee60(atk, troops, a3, 0, unit.방어, func_5aee10(unit)) * 0.8);

		// 활공격일 경우 공성병기 부대에게 0.8배
		if (병기Id_to병종Id(unit.무기) == 병종_병기)
			troops_damage = int(troops_damage * 0.8);
		break;

	case 시설_진:
	case 시설_요새:
	case 시설_성채:
	case 시설_궁노:
	case 시설_연노로:
	case 시설_투석대:
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	default:
		// 자동공격 대미지
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		troops_damage = func_5af370(building, unit);

		if (building.시설 == 시설_투석대)
			break;

		// 활공격일 경우 공성병기 부대에게 0.8배
		if (병기Id_to병종Id(unit.무기) == 병종_병기)
			troops_damage = int(troops_damage * 0.8);
		break;
	}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/*
	// 특급일 경우 플레이어의 공격력 0.75배
	if (Scenario().난이도 == 난이도_특급 && building.isPlayer())
		troops_damage = troops_damage * 3 / 4;
	*/
	if (building.isPlayer())
		troops_damage = int(troops_damage * 기타xml().대미지패널티[Scenario().난이도]);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		// 방어강화 성, 관문, 항구, 진, 요새, 성채의 공격력 2배
	if (building.hasTech(기교_방어강화) && building.시설 >= 시설_도시 && building.시설 <= 시설_성채)
		troops_damage *= 2;

	damage.병력피해량 = troops_damage;
}

// 군사시설의 부대 공격 피해량 계산
int func_5af370(Building building, Unit unit)
{
	int atk = 0;
	int bonus = 0;

	switch (building.시설)
	{
	case 시설_진:
		atk = 400;
		bonus = 300;
		break;

	case 시설_요새:
		atk = 600;
		bonus = 300;
		break;

	case 시설_성채:
		atk = 800;
		bonus = 300;
		break;

	case 시설_궁노:
		atk = 300;
		bonus = 300;
		break;

	case 시설_연노로:
		atk = 500;
		bonus = 400;
		break;

	case 시설_투석대:
		atk = 900;
		bonus = 600;
		break;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	default:
		// 자동공격 대미지
		atk = 300;
		bonus = 300;
		break;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	}

	int max_hp = std::max(building.최대내구, 1);
	int cur_hp = std::max(building.내구, max_hp / 2);

	float result = float(cur_hp) / max_hp;
	result *= 152 - unit.방어;
	result *= atk;
	result /= 132.f; // *= 0.7575758
	result += rand(bonus);

	return int(result);
}