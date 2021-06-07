/**
	부대 혼란 여부를 계산합니다.
	@param unit 부대
*/
bool PK_부대혼란(Unit unit)
{
	int troops = unit.병력;
	if (troops >= 1000)
		return false;

	if (unit.상태 != 부대상태_통상)
		return false;

	// 병력 수 8% + 10 확률로 회피
	if (randbool(std::min(std::max(troops * 8 / 100 + 10, 10), 90)))
		return false;

	// 통솔 20% + 20 확률로 회피
	if (randbool(unit.통솔 / 5 + 20))
		return false;

	__func_59b130 f;
	f.src = unit;
	Map().range(unit.좌표, 1, 4, RingCallbackType(f.callback));

	if (f.max_enemy_troops < 500)
		return false;

	// 적 부대 병력 수가 자세력 부대 병력 수의 1/5이 안될 경우 60% 확률로 회피
	if (f.sum_enemy_troops < f.sum_own_troops / 5)
	{
		if (randbool(60))
			return false;
	}
	// 적 부대 병력 수가 자세력 부대 병력 수의 1/2이 안될 경우 40% 확률로 회피
	else if (f.sum_enemy_troops < f.sum_own_troops / 2)
	{
		if (randbool(40))
			return false;
	}

	// 병력 수를 20배한 값이 적 부대 중 최대 병력 수보다 높고
	// 병력 수를 40배한 값이 적 부대 병력 합보다 높다면 회피
	if (troops * 20 >= f.max_enemy_troops && troops * 40 >= f.sum_enemy_troops)
		return false;

	return true;
}

class __func_59b130
{
	bool callback(Hex hex, Point pos)
	{
		if (!hex.hasUnit())
			return false;

		Unit dst = hex.getUnit();
		if (!isalive(dst))
			assert(false);

		if (dst.상태 != 부대상태_통상)
			return false;

		// 적 부대
		if (src.isEnemy(dst))
		{
			int troops = dst.병력;
			sum_enemy_troops += troops;
			if (troops > max_enemy_troops)
				max_enemy_troops = troops;
		}
		// 자세력 부대
		else if (src.isOwn(dst))
		{
			// 이웃 좌표
			if (Map().isNeighbor(src.좌표, dst.좌표))
				sum_own_troops += dst.병력;
		}

		return false;
	}

	Unit src;
	int max_enemy_troops = 0; // 3칸 이하 적 부대 중 최대 병력
	int sum_enemy_troops = 0; // 3칸 이하 적 부대 병력 합
	int sum_own_troops = 0;   // 인접 자세력 부대 병력 합
};