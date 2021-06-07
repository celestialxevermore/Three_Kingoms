/**
	건물의 병량 소모량을 계산합니다.
	@param building 건물
	@bug 원본과 +-1 오차가 발생할 수 있습니다.
*/
int PK_건물병량소모(Building building)
{
	if (!isalive(building) || !세력Id_isValid(building.getForceId()))
		return 0;

	Person taishu(building.태수);
	float burned = 0.f;

	if (building.isOnFire())
	{
		int politics = 0;
		if (taishu)
			politics = taishu.정치;
		burned = (6.f - (politics / 20.f)) * building.병량 / 100.f;
	}

	int n = building.병력 / 40.f + burned;

	if (n <= 0 && building.병력 > 0)
		return 1;

	return n;
}