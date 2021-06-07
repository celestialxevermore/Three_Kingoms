/**
	공격 피해량을 계산합니다.
	@param[out] damage	대미지 정보
	@param unit			부대
	@param tactics_id	#전법Id
	@param target_pos	목표 좌표
	@param type			0 공격, 1 반격, 2 반격
	@param critical		0 치명타 확률 계산, 1 치명타 성공 강제, 2 치명타 실패 강제
	@param ambush		0 통상, 1 복병
*/
void PK_공격대미지(__damage damage, Unit unit, int tactics_id, Point target_pos, int type, int critical, bool ambush)
{
	Force force(unit.getForceId());
	HexObject target_object(target_pos);

	int atk;
	Unit target_unit;
	Building target_base;

	if (ambush)
		atk = std::max(unit.지력 - 5, 1);
	else
		atk = unit.공격;

	if (target_object.isInstance(kTypeIdUnit))
		target_unit = target_object;
	else if (Building(target_object).isBase())
		target_base = target_object;

	int _f4 = 0;
	if (전법Id_isValid(tactics_id))
	{
		_f4 = Tactics(tactics_id).부대공격력;
		damage.전법성공 = randbool(PK_전법성공확률(unit, unit.getPos(), target_object, tactics_id));
	}
	// 목표 오브젝트가 인접한경우 10
	else if (Map().isNeighbor(unit.getPos(), target_pos))
	{
		_f4 = 10;
	}

	// 태고대 버프 받는 경우 1
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/*
	int _00 = 0;
	__func_5aed80 func_5aed80;
	func_5aed80.force_id = force.getId();
	if (Map().range(unit.getPos(), 0, 4, func_5aed80))
	{
		_00 = 1;
		damage.공격력상승 = true;
	}
	*/

	int _00 = 0;
	__func_5aed80 func_5aed80;
	func_5aed80.force_id = force.getId();
	func_5aed80.pos = unit.getPos();
	// 11인 이유는 시설.xml에서 설정할 수 있는 범위 최대 값이 10이기 때문임.
	// 기존에는 태고대 하나만 확인하면 됐지만 이제는 모든 시설이 공격력 상승 효과를 가질 수 있기 때문에 최대 범위 안에 있는 모든 시설을 확인해야함.
	if (Map().range(unit.getPos(), 0, 11, RingCallbackType(func_5aed80.callback)))
	{
		_00 = 1;
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
		if (Map().range(target_unit.getPos(), 0, Facility(facility_id).최대범위 + 1, RingCallbackType(func_5aedc0.callback)))
			damage.관련시설 = facility_id;
	}

	int troops = func_5aee10(unit);

	switch (critical)
	{
	case 0:
		// 전법 실패
		if (전법Id_isValid(tactics_id) && !damage.전법성공)
		{
			damage.치명타 = false;
			break;
		}
		// 반격
		if (type != 0)
		{
			damage.치명타 = false;
			break;
		}
		damage.치명타 = PK_공격_크리티컬(unit, target_object, tactics_id, !Map().isNeighbor(unit.getPos(), target_pos));
		break;
	case 2:
		damage.치명타 = false;
		break;
	case 1:
		damage.치명타 = true;
		break;
	}

	if (target_unit)
	{
		int target_def = target_unit.방어;
		int target_troops = func_5aee10(target_unit);
		damage.적병력 = target_unit.병력;
		float troops_damage = func_5aee60(atk, troops, _f4, _00, target_def, target_troops);

		switch (unit.무기)
		{
		case 병기_창:
			if (전법Id_isValid(tactics_id))
			{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				/*
				if (target_unit.무기 == 병기_극)
					troops_damage *= 0.85f;
				else if (target_unit.무기 == 병기_군마)
					troops_damage *= 1.15f;
				*/
				if (target_unit.무기 == 병기_극)
					troops_damage *= 기타xml().상성_약;
				else if (target_unit.무기 == 병기_군마)
					troops_damage *= 기타xml().상성_강;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			}

			if (force.hasTech(기교_정예창병))
				troops_damage *= 1.15;
			else if (force.hasTech(기교_창병단련))
				troops_damage *= 1.10;
			break;

		case 병기_극:
			if (전법Id_isValid(tactics_id))
			{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				/*
				if (target_unit.무기 == 병기_창)
					troops_damage *= 1.15f;
				else if (target_unit.무기 == 병기_군마)
					troops_damage *= 0.85f;
				*/
				if (target_unit.무기 == 병기_창)
					troops_damage *= 기타xml().상성_강;
				else if (target_unit.무기 == 병기_군마)
					troops_damage *= 기타xml().상성_약;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			}

			if (force.hasTech(기교_정예극병))
				troops_damage *= 1.15;
			else if (force.hasTech(기교_극병단련))
				troops_damage *= 1.10;
			break;

		case 병기_노:
			if (전법Id_isValid(tactics_id))
			{
				if (병기Id_to병종Id(target_unit.무기) == 병종_병기)
					troops_damage *= 0.85f;
			}

			if (force.hasTech(기교_정예노병))
				troops_damage *= 1.15;
			else if (force.hasTech(기교_노병단련))
				troops_damage *= 1.10;
			break;

		case 병기_군마:
			if (전법Id_isValid(tactics_id))
			{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				/*
				if (target_unit.무기 == 병기_창)
					troops_damage *= 0.85f;
				else if (target_unit.무기 == 병기_극)
					troops_damage *= 1.15f;
				*/
				if (target_unit.무기 == 병기_창)
					troops_damage *= 기타xml().상성_약;
				else if (target_unit.무기 == 병기_극)
					troops_damage *= 기타xml().상성_강;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			}

			if (force.hasTech(기교_정예기병))
				troops_damage *= 1.15;
			else if (force.hasTech(기교_기병단련))
				troops_damage *= 1.10;
			break;

		case 병기_정란:
		case 병기_주가:
		case 병기_누선:
		case 병기_투함:
			if (전법Id_isValid(tactics_id))
			{
				if (병기Id_to병종Id(target_unit.무기) == 병종_병기)
					troops_damage *= 0.8f;
			}
			break;
		}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		// 특급 난이도일 경우 75%로 감소
		/*
		if (Scenario().난이도 == 난이도_특급 && unit.isPlayer())
			troops_damage *= 0.75f;
		*/
		if (unit.isPlayer())
			troops_damage *= 기타xml().대미지패널티[Scenario().난이도];
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		if (type != 0)
		{
			if (type == 1)
				troops_damage *= 0.9f;
			else if (type == 2)
				troops_damage *= 0.4f;

			damage.병력피해량 = int(troops_damage);

			// 반격 파트이기 때문에 target_unit은 공격을 실행한 부대를 뜻함.
			// 헷갈리지 않도록 주의.
			if (target_unit.isInWater())
			{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				/*
				if (target_unit.hasSkill(특기_강습) && randbool(50))
				{
					damage.병력피해량 = 0;
					damage.방어특기 = 특기_강습;
				}
				*/
				if (target_unit.hasSkill(특기_강습) && randbool(u::getSkillInt(target_unit, 특기_강습)))
				{
					damage.병력피해량 = 0;
					damage.방어특기 = 특기_강습;
				}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			}
			else
			{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				/*
				if (target_unit.hasSkill(특기_급습) && randbool(50))
				{
					damage.병력피해량 = 0;
					damage.방어특기 = 특기_급습;
				}
				*/
				if (target_unit.hasSkill(특기_급습) && randbool(u::getSkillInt(target_unit, 특기_급습)))
				{
					damage.병력피해량 = 0;
					damage.방어특기 = 특기_급습;
				}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			}
		}
		else
		{
			if (damage.치명타)
				troops_damage *= 1.15f;

			damage.병력피해량 = int(troops_damage);

			// 방어 특기, 기교
			if (func_5af230(damage, unit, target_unit, tactics_id))
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
		}

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
		int target_troops;
		int target_def;
		int target_atk;
		func_5af0e0(target_atk, target_troops, _f4, target_def, target_base);
		damage.적병력 = target_base.병력;
		float troops_damage = func_5aee60(atk, troops, _f4, _00, target_def, target_troops);

		if (unit.무기 == 병기_정란)
		{
			troops_damage *= 1.8f;
		}
		else if (unit.무기 == 병기_투석)
		{
			troops_damage *= 1.2f;
		}
		else
		{
			troops_damage = func_5aee60(atk, std::max(troops * 75 / 100, 1), _f4, _00, target_def, target_troops);

			switch (target_base.시설)
			{
			case 시설_도시:
				troops_damage *= 0.55f; break;
			case 시설_관문:
				troops_damage *= 0.45f; break;
			case 시설_항구:
				troops_damage *= 0.60f; break;
			}
		}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		// 특급 난이도일 경우 75%로 감소
		/*
		if (Scenario().난이도 == 난이도_특급 && unit.isPlayer())
			troops_damage *= 0.75f;
		*/
		if (unit.isPlayer())
			troops_damage *= 기타xml().대미지패널티[Scenario().난이도];
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		if (type != 0)
		{
			if (type == 1)
				troops_damage *= 0.9f;
			else if (type == 2)
				troops_damage *= 0.4f;

			damage.병력피해량 = int(troops_damage);

			// 반격 파트이기 때문에 target_unit은 공격을 실행한 부대를 뜻함.
			// 헷갈리지 않도록 주의.
			if (target_unit.isInWater())
			{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				/*
				if (target_unit.hasSkill(특기_강습) && randbool(50))
				{
					damage.병력피해량 = 0;
					damage.방어특기 = 특기_강습;
				}
				*/
				if (target_unit.hasSkill(특기_강습) && randbool(u::getSkillInt(target_unit, 특기_강습)))
				{
					damage.병력피해량 = 0;
					damage.방어특기 = 특기_강습;
				}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			}
			else
			{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				/*
				if (target_unit.hasSkill(특기_급습) && randbool(50))
				{
					damage.병력피해량 = 0;
					damage.방어특기 = 특기_급습;
				}
				*/
				if (target_unit.hasSkill(특기_급습) && randbool(u::getSkillInt(target_unit, 특기_급습)))
				{
					damage.병력피해량 = 0;
					damage.방어특기 = 특기_급습;
				}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			}
		}
		else
		{
			if (damage.치명타)
				troops_damage *= 1.15f;

			damage.병력피해량 = int(troops_damage);
		}
	}

	if (target_object.isInstance(kTypeIdBuilding))
	{
		Building target_building = target_object;
		
		int edi = 5;
		if (전법Id_isValid(tactics_id))
			edi = Tactics(tactics_id).내구공격력;
		else if (Map().isNeighbor(unit.getPos(), target_pos))
			edi = 0xf;

		float hp_damage;
		if (unit.무기 == 병기_충차 || unit.무기 == 병기_목수)
			hp_damage = func_5af050(atk, troops, _00, edi);
		else
			hp_damage = func_5aeff0(atk, troops, _00, edi);

		if (damage.치명타)
			hp_damage *= 1.15f;

		if (target_building.시설 >= 시설_불씨 && target_building.시설 <= 시설_업화종)
		{
			hp_damage *= 1.6f;
		}
		else if (target_building.시설 >= 시설_시장 && target_building.시설 <= 시설_조선3단)
		{
			hp_damage *= 1.1f;
		}
		else if (target_building.시설 == 시설_제방)
		{
			hp_damage *= 0.7f;
		}
		else if (unit.무기 != 병기_충차 && unit.무기 != 병기_목수)
		{
			switch (target_building.시설)
			{
			case 시설_도시:
			case 시설_요새:
			case 시설_연노로:
			case 시설_석벽:
				hp_damage *= 0.7f; break;
			case 시설_항구:
			case 시설_진:
				hp_damage *= 0.8f; break;
			case 시설_토루:
				hp_damage *= 0.9f; break;
			case 시설_관문:
			case 시설_성채:
				hp_damage *= 0.6f; break;
			}
		}

		damage.내구피해량 = int(hp_damage);

		if (target_building.시설 == 시설_제방 && !target_building.건설완료)
			damage.내구피해량 = 0;

		// 운제
		if (unit.hasTech(기교_운제))
		{
			if (unit.무기 >= 병기_검 && unit.무기 <= 병기_군마)
			{
				damage.병력피해량 = damage.병력피해량 * 1.4f;
				damage.내구피해량 = damage.내구피해량 * 1.4f;
			}
			else
			{
				damage.병력피해량 = damage.병력피해량 * 1.2f;
				damage.내구피해량 = damage.내구피해량 * 1.2f;
			}
		}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		// 특급 난이도일 경우 75%로 감소
		/*
		if (Scenario().난이도 == 난이도_특급 && unit.isPlayer())
			damage.내구피해량 = damage.내구피해량 * 3 / 4;
		*/
		if (unit.isPlayer())
			damage.내구피해량 = damage.내구피해량 * 기타xml().대미지패널티[Scenario().난이도];
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	}
}

/***/
int func_5aecc0(Unit unit, Unit target_unit)
{
	if (isalive(unit) && isalive(target_unit) && unit.무기 == 병기_창 && unit.hasTech(기교_병량습격))
	{
		int a = rand(unit.공격) + unit.공격;
		int b = std::max(unit.병력 / 2, 1);
		int c = target_unit.병량;
		int d = unit.최대병량 - unit.병량;
		return std::min(a, b, c, d);
	}
	return 0;
}

/** 공격력 상승 효과를 가진 시설 검색 */
class __func_5aed80
{
	bool callback(Hex hex, Point pos)
	{
		Building building = hex.getBuilding();
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		/*
		return isalive(building) && building.시설 == 시설_태고대 && building.건설완료 && building.getForceId() == this.force_id;
		*/

		if (isalive(building) && building.건설완료 && building.getForceId() == this.force_id)
		{
			// 시설 중심 좌표인지 확인
			if (pos != building.getPos())
				return false;

			if (시설xml(building.시설).공격력상승) {
				int max_range = Facility(building.시설).최대범위;
				if (building.시설 == 시설_도시)
					max_range++;
				if (Map().getDistance(this.pos, pos) <= max_range)
					return true;
			}
		}
		return false;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	}

	int force_id;
	Point pos;
};

/** 진, 요새, 성채 검색 */
class __func_5aedc0
{
	bool callback(Hex hex, Point pos)
	{
		Building building = hex.getBuilding();
		return isalive(building) && building.건설완료 && building.getForceId() == this.force_id && (building.시설 == 시설_진 || building.시설 == 시설_요새 || building.시설 == 시설_성채);
	}

	int force_id;
};

/** 지휘 가능한 병력 수 */
int func_5aee10(Unit unit)
{
	Person leader(unit.주장);
	if (isalive(leader))
		return std::min(leader.지휘, unit.병력);
	return unit.병력;
}

/***/
float func_5aee60(int src_atk, int src_troops, int a3, int a4, int dst_def, int dst_troops)
{
	float result = sqrt(a3 * 64.f);
	result += std::max((src_troops - dst_troops) / 2000, 0);

	int atk = std::max(src_atk, 40);
	int def = std::max(dst_def, 40);
	atk *= atk;
	def *= def;

	result += std::max((atk - def) / 300, 0);
	result += 50.f;
	result *= a4 + 10;

	atk = (src_troops / 100 + 300) * (src_atk + 50) * (src_atk + 50) / 100;
	def = (dst_troops / 100 + 300) * (dst_def + 50) * (dst_def + 50) / 100;
	int sum = atk + def;
	int tmp;
	if (atk >= def)
		tmp = atk * 100 / sum;
	else
		tmp = std::max(100 - (def * 100 / sum), 1);

	result *= tmp;

	float st0 = float(std::max(src_troops / 4, 1));
	st0 = std::min(sqrt(st0), 40.f);

	result *= st0;
	result /= 2100.f; // *= 0.0004761905
	result += src_troops / 200;
	return result;
}

/***/
float func_5aeff0(int src_atk, int src_troops, int a3, int a4)
{
	src_troops = std::max(src_troops, 1);
	float a = sqrt(src_atk * src_atk / 15.f);
	float b = sqrt(src_troops);
	float c = a3 + 10;
	float d = a4 * 4 + 100;
	return a * b * c * d / 10000;
}

/***/
float func_5af050(int src_atk, int src_troops, int a3, int a4)
{
	src_troops = std::max(src_troops, 1);
	float a = sqrt(src_atk * src_atk / 15.f);
	float b = sqrt(src_troops);
	float c = a3 + 10;
	float d = a4 * 4 + 100;
	return a * std::min(b, 40.f) * c * d / 10000 + (src_troops / 25) + b;
}

/***/
void func_5af0e0(int &out atk, int &out troops, int &out a3, int &out def, Building building)
{
	a3 = 10;

	Person taishu(building.태수);

	if (isalive(taishu))
	{
		atk = std::max(taishu.무력 - 25, 40);
		def = std::max(taishu.통솔 - 25, 40);
		troops = std::min(building.병력, taishu.지휘);
	}
	else
	{
		atk = 30;
		def = 30;
		troops = std::min(building.병력, 7000);
		if (troops != 0)
			troops = std::max(troops, 500);
	}
}

/** 방어 특기, 기교 */
bool func_5af230(__damage damage, Unit unit, Unit target_unit, int tactics_id)
{
	if (전법Id_isValid(tactics_id))
		return false;

	Point pos = unit.getPos();
	Point target_pos = target_unit.getPos();

	if (target_unit.무기 == 병기_극)
	{
		// 화살방패
		if (target_unit.hasTech(기교_화살방패))
		{
			if (!Map().isNeighbor(pos, target_pos) && randbool(30))
			{
				damage.방어기교 = 기교_화살방패;
				return true;
			}
		}

		// 큰방패
		if (target_unit.hasTech(기교_큰방패))
		{
			if (Map().isNeighbor(pos, target_pos) && randbool(30))
			{
				damage.방어기교 = 기교_큰방패;
				return true;
			}
		}
	}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// 불굴
	/*
	if (target_unit.병력 < 3000 && target_unit.hasSkill(특기_불굴) && randbool(50))
	{
		damage.방어특기 = 특기_불굴;
		return true;
	}
	*/
	if (target_unit.hasSkill(특기_불굴) && u::test_fukutsu(target_unit))
	{
		damage.방어특기 = 특기_불굴;
		return true;
	}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// 금강
	/*
	if (damage.병력피해량 < 500 && target_unit.hasSkill(특기_금강) && randbool(50))
	{
		damage.방어특기 = 특기_금강;
		return true;
	}
	*/
	if (target_unit.hasSkill(특기_금강) && u::test_kongou(target_unit, damage.병력피해량))
	{
		damage.방어특기 = 특기_금강;
		return true;
	}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	return false;
}