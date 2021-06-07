/**
	공격 크리티컬 여부를 계산합니다.
	@param unit 부대
	@param target 목표 오브젝트
	@param tactics #전법Id
	@param ranged 원거리 공격 여부
*/
bool PK_공격_크리티컬(Unit unit, HexObject target, int tactics, bool ranged)
{
	Unit target_unit;
	if (target.isInstance(kTypeIdUnit))
		target_unit = target;

	Hex hex(unit.getPos());

	int target_strength = 기타xml().무장능력치제한 + 1;
	if (target_unit)
		target_strength = target_unit.getBestMemberStat(무장능력_무력);

	// 전법
	if (tactics >= 0 && tactics < 전법_끝)
	{
		// 패왕 특기 보유
		if (unit.hasSkill(특기_패왕))
			return true;
		// 용장 특기 보유자 무력이 목표 오브젝트 무력보다 높음
		if (unit.getBestMemberStat(특기_용장, 무장능력_무력) > target_strength)
			return true;

		switch (unit.무기)
		{
		case 병기_창:
			// 투신 특기 보유
			if (unit.hasSkill(특기_투신))
				return true;
			// 창신 특기 보유
			if (unit.hasSkill(특기_창신))
				return true;
			// 창장 특기 보유자 무력이 목표 오브젝트 무력보다 높음
			if (unit.getBestMemberStat(특기_창장, 무장능력_무력) > target_strength)
				return true;
			// 신장 특기 보유자 무력이 목표 오브젝트 무력보다 높음
			if (unit.getBestMemberStat(특기_신장, 무장능력_무력) > target_strength)
				return true;
			// 비장 특기 보유자 무력이 목표 오브젝트 무력보다 높음
			if (unit.getBestMemberStat(특기_비장, 무장능력_무력) > target_strength)
				return true;
			break;

		case 병기_극:
			// 투신 특기 보유
			if (unit.hasSkill(특기_투신))
				return true;
			// 극신 특기 보유
			if (unit.hasSkill(특기_극신))
				return true;
			// 극장 특기 보유자 무력이 목표 오브젝트 무력보다 높음
			if (unit.getBestMemberStat(특기_극장, 무장능력_무력) > target_strength)
				return true;
			// 신장 특기 보유자 무력이 목표 오브젝트 무력보다 높음
			if (unit.getBestMemberStat(특기_신장, 무장능력_무력) > target_strength)
				return true;
			// 비장 특기 보유자 무력이 목표 오브젝트 무력보다 높음
			if (unit.getBestMemberStat(특기_비장, 무장능력_무력) > target_strength)
				return true;
			break;

		case 병기_노:
			// 궁신 특기 보유
			if (unit.hasSkill(특기_궁신))
				return true;
			// 궁장 특기 보유자 무력이 목표 오브젝트 무력보다 높음
			if (unit.getBestMemberStat(특기_궁장, 무장능력_무력) > target_strength)
				return true;
			// 신장 특기 보유자 무력이 목표 오브젝트 무력보다 높음
			if (unit.getBestMemberStat(특기_신장, 무장능력_무력) > target_strength)
				return true;
			// 비장 특기 보유자 무력이 목표 오브젝트 무력보다 높음
			if (unit.getBestMemberStat(특기_비장, 무장능력_무력) > target_strength)
				return true;
			break;

		case 병기_군마:
			// 기신 특기 보유
			if (unit.hasSkill(특기_기신))
				return true;
			// 기장 특기 보유자 무력이 목표 오브젝트 무력보다 높음
			if (unit.getBestMemberStat(특기_기장, 무장능력_무력) > target_strength)
				return true;
			// 신장 특기 보유자 무력이 목표 오브젝트 무력보다 높음
			if (unit.getBestMemberStat(특기_신장, 무장능력_무력) > target_strength)
				return true;
			// 비장 특기 보유자 무력이 목표 오브젝트 무력보다 높음
			if (unit.getBestMemberStat(특기_비장, 무장능력_무력) > target_strength)
				return true;
			break;

		case 병기_충차:
		case 병기_정란:
		case 병기_투석:
		case 병기_목수:
			// 공신 특기 보유
			if (unit.hasSkill(특기_공신))
				return true;
			break;

		case 병기_주가:
		case 병기_누선:
		case 병기_투함:
			// 수신 특기 보유
			if (unit.hasSkill(특기_수신))
				return true;
			// 수장 특기 보유자 무력이 목표 오브젝트 무력보다 높음
			if (unit.getBestMemberStat(특기_수장, 무장능력_무력) > target_strength)
				return true;
			break;
		}
	}
	// 공격, 일제
	else
	{
		// 신장 특기 보유자 무력이 목표 오브젝트 무력보다 높음
		if (unit.getBestMemberStat(특기_신장, 무장능력_무력) > target_strength)
			return true;
		// 구축 특기 보유자 무력이 목표 오브젝트 무력보다 높음
		if (unit.getBestMemberStat(특기_구축, 무장능력_무력) > target_strength)
			return true;

		switch (unit.무기)
		{
		case 병기_군마:
			// 원거리 공격, 백마 특기 보유
			if (ranged && unit.hasSkill(특기_백마))
				return true;
			break;
		}
	}

	// 공성 특기 보유, 시설 목표
	if (unit.hasSkill(특기_공성) && target.isInstance(kTypeIdBuilding))
		return true;

	// 부대 목표
	if (target_unit)
	{
		// 숲, 난전 특기 보유
		if (hex.지형 == 지형_숲 && unit.hasSkill(특기_난전))
			return true;
	}

	int result = 0;
	Person leader(unit.주장);

	if (unit.무력 >= 80)
		result = 2;
	else if (unit.무력 >= 60)
		result = 1;

	result += unit.적성;

	for (int i = 0; i < 2; i++)
	{
		int deputy = unit.부장[i];
		if (!무장Id_isValid(deputy))
			continue;

		if (leader.isGikyoudai(deputy) || leader.isFuufu(deputy))
			result += 4;
		else if (leader.isLike(deputy))
			result += 2;
		else if (leader.isDislike(deputy))
			result -= 5;
	}

	return randbool(std::max(result, 0));
}