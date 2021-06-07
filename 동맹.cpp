/**
	동맹 결과를 계산합니다.
	@param[out] accurate 군사의 예측 결과가 정확할지 여부
	@param actor 실행무장
	@param target 목표세력
	@param gold 금
	@return 0: 성공, 1: 설전, 2: 실패
*/
int PK_동맹결과(bool &out accurate, Person actor, Force target, int gold)
{
	accurate = true;

	Person target_kunshu(target.군주);
	if (!isalive(target_kunshu))
		return 2;

	// 포로 무장이 있음
	if (func_5be0e0(actor.getForceId(), target.getId()) || func_5be0e0(target.getId(), actor.getForceId()))
		return 2;

	// 실행 무장이 논객 특기가 없고 목표 세력 군주가 실행 세력 군주를 혐오
	if (!actor.hasSkill(특기_논객) && target_kunshu.isDislike(actor.군주))
		return 2;

	int goal_value = (110 - target.우호도[actor.getForceId()]) * 2;

	int value = 0;
	value += func_5b3130(actor, target_kunshu, -1.f, 1.f, 1.5f) * 10.f;
	value += gold / 150;
	value -= target_kunshu.getAishouDistance(actor.getId()) / 5;
	value += actor.정치;
	switch (Scenario().난이도)
	{
	case 난이도_상급: value *= 0.8f; break;
	case 난이도_특급: value *= 0.7f; break;
	}

	if (value * 2 > goal_value)
		accurate = false;

	if (value > goal_value)
		return 0;

	// 실행 무장이 논객 특기가 있음
	if (actor.hasSkill(특기_논객))
	{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		/*
		// 특급 모드 플레이어일 경우에만 20%, 나머지 100% 설전
		if (Scenario().난이도 != 난이도_특급 || !actor.isPlayer() || randbool(20))
			return 1;
		*/
		if (!actor.isPlayer() || randbool(무장xml(actor.getId()).논객[Scenario().난이도]))
			return 1;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	}

	goal_value = (100 - target.우호도[actor.getForceId()]) * 2;
	if (value > goal_value)
		return 1;

	return 2;
}

// src 세력이 dst 세력 무장을 포로로 잡고 있는지 확인
bool func_5be0e0(int src, int dst)
{
	List<Person> list;
	if (list.init(무장속성_신분, 신분_포로) <= 0)
		return false;

	for (auto i = list.begin(); i; i++)
	{
		if (i().구세력 != dst)
			continue;

		HexObject object(i().소재);
		if (!isalive(object) || object.getForceId() != src)
			continue;

		return true;
	}

	return false;
}

// 목표세력 군주와 실행무장의 관계에 따른 보너스
float func_5b3130(Person actor, Person target_kunshu, float bad, float good, float best)
{
	int actor_id = actor.getId();

	if (target_kunshu.isGikyoudai(actor_id) || target_kunshu.isFuufu(actor_id))
		return best;

	if (target_kunshu.isLike(actor_id))
		return good;

	if (target_kunshu.isDislike(actor_id))
		return bad;

	return 0.f;
}