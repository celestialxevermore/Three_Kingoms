/**
	항복권고 결과를 계산합니다.
	@param[out] accurate 군사의 예측 결과가 정확할지 여부
	@param actor 실행무장
	@param target 목표세력
	@param gold 금(항상 0)
	@return 0: 성공, 1: 설전, 2: 실패
*/
int PK_항복권고결과(bool &out accurate, Person actor, Force target, int gold)
{
	accurate = true;

	// 1대1 상황일 경우 실패
	if (List<Force>().init(세력속성_번호, 세력_강, 연산자_보다작음) <= 2)
		return 2;

	Force source(actor.getForceId());
	if (!isalive(source))
		return 2;

	if (Scenario().getElapsedYears() < 1)
		return 2;

	if (source.도시수 < target.도시수 * 4)
		return 2;

	if (source.병력 < target.병력 * 3)
		return 2;

	if (target.도시수 >= 5)
		return 2;

	Person target_kunshu(target.군주);
	if (!isalive(target_kunshu))
		return 2;

	if (!source.hasNeighborCity(target))
		return 2;

	if (target_kunshu.isDislike(source.군주))
		return 2;

	if (target_kunshu.isDislike(actor.getId()))
		return 2;

	switch (target.군주)
	{
	case 무장_여포:
	case 무장_동탁:
	case 무장_장각:
	case 무장_유비:
	case 무장_관우:
	case 무장_장비:
	case 무장_손견:
	case 무장_손책:
	case 무장_조조:
		return 2;
	}

	if (target.도시수 <= 0)
		return 2;

	int goal_value = (target_kunshu.성격 * 7) - (target.우호도[source.getId()] / 4);

	int value = 0;
	value += (source.도시수 / target.도시수) / 2;
	value += (source.도시수 - target.도시수) / 5;
	value -= target_kunshu.getAishouDistance(actor.getId()) / 7;
	value += source.isProtectingTheEmperor() ? 10 : 0;
	value += func_5b3f40(actor, target_kunshu, 0, 10, 20);
	value += actor.매력;
	switch (Scenario().난이도)
	{
	case 난이도_상급: value *= 0.8f; break;
	case 난이도_특급: value *= 0.7f; break;
	}
	value /= 2;
	value += rand(value, gold, target.getId(), actor.getId(), actor.소속, 0, 0, 0);

	if (value * 2 >= goal_value + 100)
		accurate = false;

	if (value >= goal_value + 100)
		return 0;

	if (value >= goal_value + 95)
		return 1;

	return 2;
}

// 목표세력 군주와 실행무장의 관계에 따른 보너스
int func_5b3f40(Person actor, Person target_kunshu, int bad, int good, int best)
{
	int actor_id = actor.getId();

	if (target_kunshu.isGikyoudai(actor_id) || target_kunshu.isFuufu(actor_id))
		return best;

	if (target_kunshu.isLike(actor_id))
		return good;

	if (target_kunshu.isDislike(actor_id))
		return bad;

	return 0;
}