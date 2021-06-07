/**
	화계 피해량 계산
	@param[out] damage	대미지 정보
	@param unit			부대
	@param target		목표
	@param critical		크리티컬
*/
void PK_화계대미지(__damage damage, Unit unit, HexObject target, bool critical)
{
	Force target_force(target.getForceId());
	int atk;

	// 목표오브젝트가 부대
	if (target.isInstance(kTypeIdUnit))
	{
		atk = 300;
		damage.병력피해량 = atk + rand(200);
	}
	// 목표오브젝트가 건물
	else
	{
		atk = 100;
		damage.내구피해량 = atk + rand(50);
	}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/*
	if (isalive(target_force) && target.hasTech(기교_폭약연성))
	{
		damage.병력피해량 = damage.병력피해량 + atk;
		damage.공격기교 = 기교_폭약연성;
	}
	*/
	if (기타xml().폭약연성버그수정 ? isalive(unit) && unit.hasTech(기교_폭약연성) : isalive(target_force) && target.hasTech(기교_폭약연성))
	{
		damage.병력피해량 = damage.병력피해량 + atk;
		damage.공격기교 = 기교_폭약연성;
	}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	

	// 화신 특기를 보유중이면 대미지 2배
	if (isalive(unit) && unit.hasSkill(특기_화신))
	{
		damage.병력피해량 = damage.병력피해량 * 2;
		damage.공격특기 = 특기_화신;
	}

	// 목표오브젝트가 등갑 특기를 보유중이면 대미지 2배
	if (target.hasSkill(특기_등갑))
	{
		damage.병력피해량 = damage.병력피해량 * 2;
		damage.방어특기 = 특기_등갑;
	}
	// 목표오브젝트가 화신 특기를 보유중이면 무효
	else if (target.hasSkill(특기_화신))
	{
		damage.병력피해량 = 0;
		damage.방어특기 = 특기_화신;
	}

	// 회복중인 제방일 경우 무효
	if (isinstance(target, kTypeIdBuilding))
	{
		Building building(target);
		if (building.시설 == 시설_제방 && !building.건설완료)
			damage.내구피해량 = 0;
	}
}