/**
	역병으로인한 병력 증감값을 계산합니다.
	@param building 거점
*/
int PK_역병_병력증감(Building building)
{
	return -(building.병력 * (rand(6) + 5) / 100);
}

/**
	역병으로인한 치안 증감값을 계산합니다.
	@param building 거점
*/
int PK_역병_치안증감(Building building)
{
	return -(2 + rand(3));
}

/**
	역병으로인한 무장 상병을 계산합니다.
	@param building 거점
	@param person 건강 상태인 무장
	@return #상병Id
*/
int PK_역병_무장상병(Building building, Person person)
{
	if (randbool(8))
		return 상병_경증;
	else if (randbool(2))
		return 상병_중증;
	else
		return -1;
}