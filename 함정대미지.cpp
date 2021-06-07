/**
	함정 피해량 계산
	@details	제방으로 인한 피해량은 다른 함수에서 계산됩니다.\n
				낙석을 제외한 불함정의 경우 PK_화계대미지 결과가 더해집니다.(답파 특기 보유 시 피해량이 90% 감소하지만 실제로는 반감된 것처럼 보이는 이유임.)
	@param[out] damage	대미지 정보
	@param trap_id		함정 #시설Id
	@param unit			부대
	@param target		목표
	@param critical		크리티컬
*/
void PK_함정대미지(__damage damage, int trap_id, Unit unit, HexObject target, bool critical)
{
	int result = 0;
	int bakuyaku = 0; // 폭약연성 기교 추가 피해량

	if (target.isInstance(kTypeIdUnit))
	{
		bakuyaku = 300;
		switch (trap_id)
		{
		case 시설_불씨:
		case 시설_화구:
			result = 300 + rand(100) + 50;
			break;

		case 시설_화염종:
			result = 400 + rand(200) + 50;
			break;

		case 시설_화염구:
		case 시설_화선:
			result = 400 + rand(100) + 50;
			break;

		case 시설_업화구:
		case 시설_업화종:
			result = 500 + rand(200) + 50;
			break;

		case 시설_낙석:
			result = 1500 + rand(500) + 50;
			break;

		default:
			result = 0 + rand(0) + 50;
			break;
		}
	}
	else
	{
		bakuyaku = 100;
		int hp = 0;
		switch (trap_id)
		{
		case 시설_불씨:
			result = 100 + rand(100) + 50;
			break;

		case 시설_화염종:
		case 시설_화구:
		case 시설_화선:
			result = 200 + rand(100) + 50;
			break;

		case 시설_화염구:
		case 시설_업화종:
			result = 300 + rand(100) + 50;
			break;

		case 시설_업화구:
			result = 400 + rand(100) + 50;
			break;

		case 시설_낙석:
			result = 800 + rand(1000) + 50;
			break;

		case 시설_제방:
			// 사용되지 않음
			hp = Building(target).내구;
			if (target.isInstance(kTypeIdBuilding) && hp > 0)
			{
				int n = hp - std::max(hp - rand(40) - 980, 1);
				result = std::max(n, 0);
			}
			break;

		default:
			result = 0 + rand(0) + 50;
			break;
		}
	}

	if (trap_id == 시설_낙석 || trap_id == 시설_제방)
	{
		if (target.hasSkill(특기_등갑))
		{
			result = result / 2;
			damage.방어특기 = 특기_등갑;
		}
	}
	else
	{
		if (isalive(unit) && unit.hasTech(기교_폭약연성))
			result = result + bakuyaku;
		if (isalive(unit) && unit.hasSkill(특기_화신))
			result = result * 2;

		if (target.hasSkill(특기_등갑))
		{
			result = result * 2;
			damage.방어특기 = 특기_등갑;
		}
		else if (target.hasSkill(특기_화신))
		{
			result = 0;
		}
	}

	if (target.hasSkill(특기_답파))
	{
		result *= 0.1;
		damage.방어특기 = 특기_답파;
	}

	if (target.isInstance(kTypeIdUnit))
		damage.병력피해량 = result;
	else
		damage.내구피해량 = result;

	// 회복중인 제방일 경우 무효
	if (isinstance(target, kTypeIdBuilding))
	{
		Building building(target);
		if (building.시설 == 시설_제방 && !building.건설완료)
			damage.내구피해량 = 0;
	}
}