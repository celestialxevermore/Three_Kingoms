/**
	부대 병량의 예상 일수를 계산합니다.
	출진 화면과 부대를 선택했을때 나오는 예상 일수 계산에 사용됩니다.
*/
int PK_부대병량예상일수(int food, int troops)
{
	return food * 100 / troops;
}

/**
	부대의 병량 소모량을 계산합니다.
	@param unit 부대
	@bug 원본과 +-1 오차가 발생할 수 있습니다.
*/
int PK_부대병량소모(Unit unit)
{
	if (!isalive(unit))
		return 0;

	float eat = 1.f;
	float burn = 0.f;

	if (unit.종류 == 부대종류_전투)
	{
		switch (func_49d8e0(unit))
		{
		case 시설_성채: eat = 1.f; break;
		case 시설_요새: eat = 4.f / 3.f; break; // 1.333...
		case 시설_진: eat = 5.f / 3.f; break; // 1.666...
		default: eat = 2.f; break;
		}
	}

	if (unit.isOnFire())
		burn = (6.f - (unit.정치 / 20.f)) * unit.병량 / 100.f;

	int n = unit.병력 * eat / 20.f + burn;

	if (n <= 0 && unit.병력 > 0)
		return 1;

	return n;
}

// 주변의 진, 성채, 요새 검색
int func_49d8e0(Unit unit)
{
	Force force(unit.getForceId());
	if (!isalive(force))
		return -1;

	int facility_id = 시설_진;
	if (force.기교[기교_성벽강화])
		facility_id = 시설_성채;
	else if (force.기교[기교_시설강화])
		facility_id = 시설_요새;

	__func_49d870 func_49d870;
	func_49d870.facility_id = facility_id;
	func_49d870.force_id = unit.getForceId();

	if (Map().range(unit.getPos(), 1, Facility(facility_id).최대범위 + 1, RingCallbackType(func_49d870.callback)))
		return facility_id;

	return -1;
}

class __func_49d870
{
	bool callback(Hex hex, Point pos)
	{
		if (!hex.hasBuilding())
			return false;

		Building building = hex.getBuilding();
		if (!isalive(building) || building.시설 != facility_id || !building.건설완료 || building.getForceId() != force_id)
			return false;

		return true;
	}

	int facility_id;
	int force_id;
};