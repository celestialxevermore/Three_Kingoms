/**
	낙뢰 피해량 계산
	@param[out] damage	대미지 정보
	@param unit			부대
	@param target		목표
	@param critical		크리티컬
*/
void PK_낙뢰대미지(__damage damage, Unit unit, HexObject target, bool critical)
{
	if (target.isInstance(kTypeIdUnit))
		damage.병력피해량 = 1500 + rand(1000);
	else
		damage.내구피해량 = 700 + rand(300);

	// 회복중인 제방일 경우 무효
	if (isinstance(target, kTypeIdBuilding))
	{
		Building building(target);
		if (building.시설 == 시설_제방 && !building.건설완료)
			damage.내구피해량 = 0;
	}
}