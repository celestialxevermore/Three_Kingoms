/**
	지원공격 피해량을 계산합니다.
	@param[out] damage	대미지 정보
	@param unit			부대
	@param target_pos	목표 좌표
*/
void PK_지원공격대미지(__damage damage, Unit unit, Point target_pos)
{
	Force force(unit.getForceId());
	HexObject target_object(target_pos);

	int atk = unit.공격;
	Unit target_unit;
	Building target_base;

	if (target_object.isInstance(kTypeIdUnit))
		target_unit = target_object;
	else if (Building(target_object).isBase())
		target_base = target_object;
	
	// 목표 오브젝트가 인접한경우 10
	int _60 = 0;
	if (Map().isNeighbor(unit.getPos(), target_pos))
		_60 = 10;

	// 태고대 버프 받는 경우 1
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/*
	int _6c = 0;
	__func_5aed80 func_5aed80;
	func_5aed80.force_id = force.getId();
	if (Map().range(unit.getPos(), 0, 4, func_5aed80))
	{
		_6c = 1;
		damage.공격력상승 = true;
	}
	*/

	int _6c = 0;
	__func_5aed80 func_5aed80;
	func_5aed80.force_id = force.getId();
	func_5aed80.pos = unit.getPos();
	// 11인 이유는 시설.xml에서 설정할 수 있는 범위 최대 값이 10이기 때문임.
	// 기존에는 태고대 하나만 확인하면 됐지만 이제는 모든 시설이 공격력 상승 효과를 가질 수 있기 때문에 최대 범위 안에 있는 모든 시설을 확인해야함.
	if (Map().range(unit.getPos(), 0, 11, RingCallbackType(func_5aed80.callback)))
	{
		_6c = 1;
		damage.공격력상승 = true;
	}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	if (target_unit)
	{
		Force target_force(target_unit.getForceId());
		int facility_id = 시설_진;
		if (target_force.hasTech(기교_시설강화))
			facility_id = 시설_요새;
		if (target_force.hasTech(기교_성벽강화))
			facility_id = 시설_성채;
		__func_5aedc0 func_5aedc0;
		func_5aedc0.force_id = target_force.getId();
		if (Map().range(target_unit.getPos(), 0, Facility(facility_id).피해량감소범위 + 1, RingCallbackType(func_5aedc0.callback)))
			damage.관련시설 = facility_id;
	}

	int troops = func_5aee10(unit);

	damage.치명타 = false;

	if (target_unit)
	{
		int target_def = target_unit.방어;
		int target_troops = func_5aee10(target_unit);
		float troops_damage = func_5aee60(atk, troops, _60, _6c, target_def, target_troops);

		switch (unit.무기)
		{
		case 병기_창:
			if (force.hasTech(기교_정예창병))
				troops_damage *= 1.15;
			else if (force.hasTech(기교_창병단련))
				troops_damage *= 1.10;
			break;

		case 병기_극:
			if (force.hasTech(기교_정예극병))
				troops_damage *= 1.15;
			else if (force.hasTech(기교_극병단련))
				troops_damage *= 1.10;
			break;

		case 병기_노:
			if (force.hasTech(기교_정예노병))
				troops_damage *= 1.15;
			else if (force.hasTech(기교_노병단련))
				troops_damage *= 1.10;
			break;

		case 병기_군마:
			if (force.hasTech(기교_정예기병))
				troops_damage *= 1.15;
			else if (force.hasTech(기교_기병단련))
				troops_damage *= 1.10;
			break;
		}

		damage.병력피해량 = int(troops_damage);

		// 방어 특기, 기교
		if (func_5af230(damage, unit, target_unit, -1))
			damage.병력피해량 = 0;
		
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		// 기력 대미지
		/*
		if (unit.hasSkill(특기_소탕))
			damage.기력피해량 = 5;
		if (unit.hasSkill(특기_위풍))
			damage.기력피해량 = 20;
		*/
		if (unit.hasSkill(특기_소탕))
			damage.기력피해량 = u::getSkillInt(unit, 특기_소탕);
		if (unit.hasSkill(특기_위풍))
			damage.기력피해량 = u::getSkillInt(unit, 특기_위풍);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		// 병량획득
		damage.병량획득 = damage.병량피해량 = func_5aecc0(unit, target_unit);

		// 특급 난이도일 경우 75%로 감소
		if (Scenario().난이도 == 난이도_특급 && unit.isPlayer())
			damage.병력피해량 = damage.병력피해량 * 3 / 4;

		// 목표부대가 등갑 특기를 보유한 경우 50%로 감소
		if (target_unit.hasSkill(특기_등갑))
			damage.병력피해량 = damage.병력피해량 / 2;

		// 시설 별 대미지 감소
		switch (damage.관련시설)
		{
		case 시설_진:
			damage.병력피해량 = damage.병력피해량 * 0.85; break;
		case 시설_요새:
			damage.병력피해량 = damage.병력피해량 * 0.75; break;
		case 시설_성채:
			damage.병력피해량 = damage.병력피해량 * 0.65; break;
		}
	}
	else if (target_base)
	{
		assert(false);
	}

	if (target_object.isInstance(kTypeIdBuilding))
	{
		assert(false);
	}

	// 최소 병력 대미지
	if (damage.병력피해량 != 0)
		damage.병력피해량 = std::max(damage.병력피해량 / 2, rand(100) + 200);

	// 최소 내구 대미지
	if (damage.내구피해량 != 0)
		damage.내구피해량 = std::max(damage.내구피해량 / 2, rand(10) + 20);
}