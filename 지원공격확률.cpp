/**
	지원 공격 확률을 계산합니다.
	@param assister 지원을 실행할 부대
	@param attacker 지원할 부대(공격을 실행한 부대)
	@param target 목표 부대
*/
int PK_지원공격확률(Unit assister, Unit attacker, Unit target)
{
	Person leader(assister.주장);
	int id = attacker.주장;
	int bonus = 무장xml(assister.주장).지원공격확률보너스;

	// 배우자나 의형제일 경우 50%
	if (leader.isFuufu(id) || leader.isGikyoudai(id))
		return std::min(50 + bonus, 100);

	// 보좌 특기일 경우 혐오무장만 아니면 30%
	if (leader.hasSkill(특기_보좌) && !leader.isDislike(id))
		return std::min(30 + bonus, 100);

	// 친애무장일 경우 30%
	if (leader.isLike(id))
		return std::min(30 + bonus, 100);

	// 혈연이고 혐오무장이 아닐경우 20%
	if (leader.isKetsuen(id) && !leader.isDislike(id))
		return std::min(20 + bonus, 100);

	return std::min(bonus, 100);
}