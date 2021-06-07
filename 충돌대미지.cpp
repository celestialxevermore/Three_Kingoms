/**
	충돌 피해량 계산
	@param[out] damage	대미지 정보
	@param unit			공격한 부대
	@param target		튕겨나간 오브젝트와 충돌한 오브젝트
*/
void PK_충돌대미지(__damage damage, Unit unit, HexObject target)
{
	// 사용되지 않음
	damage._20 = -std::max(rand(unit.공격) + unit.공격 / 2, 1);
	
	if (target.isInstance(kTypeIdUnit))
	{
		int n = unit.공격 * 2 - Unit(target).방어;
		if (n < 20)
			n = 20;
		damage.병력피해량 = std::max(n + rand(n), 1);
	}
	else if (target.isInstance(kTypeIdBuilding) && !Building(target).isTrap())
	{
		int n = unit.공격 + rand(unit.공격 / 2);
		n /= 2;
		damage.내구피해량 = std::max(n, 1);
	}

	// 회복중인 제방일 경우 무효
	if (isinstance(target, kTypeIdBuilding))
	{
		Building building(target);
		if (building.시설 == 시설_제방 && !building.건설완료)
			damage.내구피해량 = 0;
	}
}