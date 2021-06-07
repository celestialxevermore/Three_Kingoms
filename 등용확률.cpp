/**
	등용 성공 여부를 예측합니다.
	@param target 목표무장
	@param actor 실행무장
	@param type	타입|설명
				-|-
				0|일반 등용
				1|포로처우 메뉴 등용
				2|포로처우 메뉴 등용(세력 멸망)
	@param seed 무작위 시드
*/
bool PK_등용결과예측(Person target, Person actor, int type, int seed)
{
	if (!isalive(target) || !isalive(actor))
		return false;

	if (!isalive(Person(actor.군주)))
		return false;

	// 특별한 관계가 있는지 확인
	bool special = false;
	if (func_4b0040(target, actor, type, special))
		return special;

	int giri = 10;
	if (type != 0)
		giri = std::min(15 - target.의리 * 2, 10);

	int n = std::min(func_5c6030(target, actor, type, seed) * giri / 10, 100);

	if (type != 0)
		return randbool(n);

	int n2 = rand(100, seed, target.getId(), actor.getId(), target.충성도, actor.매력, actor.getAishouDistance(target.getId()), 0);

	return n2 < n;
}

bool func_4b0040(Person target, Person actor, int type, bool &out special)
{
	special = false;
	int force_id = target.getForceId();
	bool can_return = 세력Id_isValid(force_id);

	// 세력 멸망
	if (type == 2)
		can_return = false;

	if (!isalive(target) || !isalive(actor))
		return true;

	// 실행무장 세력의 군주 없음
	Person actor_kunshu(actor.군주);
	if (!isalive(actor_kunshu))
		return true;

	// 실행무장 세력의 군주가 사관 금지 군주임
	if (target.사관금지군주 == actor_kunshu.getId())
		return true;

	// 목표무장이 군주임
	if (target.isKunshu() && can_return)
		return true;

	// 목표무장 의형제 있음(2인)
	Person gikyoudai(target.의형제);
	if (isalive(gikyoudai) && gikyoudai != target)
	{
		// 목표무장이 의형제와 같은 세력임
		if (can_return && 세력Id_isValid(force_id) && gikyoudai.getForceId() == force_id)
			return true;

		// 목표무장이 실행무장 세력의 군주나 실행무장과 의형제임
		if (gikyoudai == actor_kunshu || gikyoudai == actor)
		{
			special = true;
			return true;
		}
	}

	// 목표무장이 배우자와 같은 세력임
	Person spouse(target.배우자);
	if (isalive(spouse))
	{
		if (can_return && 세력Id_isValid(force_id) && spouse.getForceId() == force_id)
			return true;
	}

	// 목표무장이 의형제와 같은 세력임(3인 이상)
	List<Person> gikyoudai_list;
	if (무장Id_isValid(target.의형제))
	{
		gikyoudai_list.init(무장속성_의형제, target.의형제);
		gikyoudai_list.remove(target);
	}

	if (can_return && isalive(gikyoudai) && 세력Id_isValid(force_id) && gikyoudai_list.contains(무장속성_세력, force_id))
		return true;

	// 목표무장의 의형제가 이미 다른 세력에 소속되어 있음
	if (isalive(gikyoudai) && gikyoudai != target)
	{
		int gikyoudai_force_id = gikyoudai.getForceId();
		if (can_return || force_id != gikyoudai_force_id)
		{
			if (세력Id_isValid(gikyoudai_force_id) && actor_kunshu.getForceId() != gikyoudai_force_id)
				return true;
		}
	}

	// 목표무장의 배우자가 이미 다른 세력에 소속되어 있음
	if (isalive(spouse))
	{
		int spouse_force_id = spouse.getForceId();
		if (can_return || force_id != spouse_force_id)
		{
			if (세력Id_isValid(spouse_force_id) && actor_kunshu.getForceId() != spouse_force_id)
				return true;
		}
	}

	// 실행무장 세력의 군주나 실행무장이 목표무장의 매우자임
	if (isalive(spouse))
	{
		if (spouse == actor_kunshu || spouse == actor)
		{
			special = true;
			return true;
		}
	}

	// 목표무장이 실행무장 세력 군주를 혐오함
	if (target.isDislike(actor_kunshu.getId()))
		return true;

	// 목표무장이 실행무장을 혐오함
	if (target.isDislike(actor.getId()))
		return true;

	if (type == 0)
	{
		// 목표무장이 실행무장과 의형제임
		if (target.isGikyoudai(actor.getId()) ||
			// 목표무장이 실행무장 세력 군주와 의형제임
			target.isGikyoudai(actor_kunshu.getId()) ||
			// 목표무장이 실행무장과 부부임
			target.isFuufu(actor.getId()) ||
			// 목표무장이 실행무장 세력 군주와 부부임
			target.isFuufu(actor_kunshu.getId()))
		{
			special = true;
			return true;
		}

		// 목표무장의 충성도 + 의리 값이 96 이상임
		if (target.충성도 + target.의리 >= 96)
			return true;

		// 의형제가 실행무장 세력에 소속되어 있음
		if (isalive(gikyoudai) && gikyoudai.getForceId() == actor_kunshu.getForceId())
		{
			special = true;
			return true;
		}

		// 배우자가 실행무장 세력에 소속되어 있음
		if (isalive(spouse) && spouse.getForceId() == actor_kunshu.getForceId())
		{
			special = true;
			return true;
		}

		// 목표무장이 군주를 친애함
		int target_kunshu_id = target.군주;
		if (!target.isKunshu() && 무장Id_isValid(target_kunshu_id) && target.isLike(target_kunshu_id))
			return true;

		// 목표무장이 실행무장을 친애함
		if (target.isLike(actor.getId()) ||
			// 목표무장이 실행무장 세력 군주를 친애함
			target.isLike(actor_kunshu.getId()))
		{
			special = true;
			return true;
		}
	}
	else
	{
		// 실행무장 세력에 의형제가 소속되어 있음
		if (gikyoudai_list.contains(무장속성_세력, actor_kunshu.getForceId()))
		{
			special = true;
			return true;
		}

		// 실행무장 세력에 배우자가 소속되어 있음
		if (isalive(spouse) && spouse.getForceId() == actor_kunshu.getForceId())
		{
			special = true;
			return true;
		}

		if (can_return)
		{
			// 목표무장이 군주를 친애함
			int target_kunshu_id = target.군주;
			if (!target.isKunshu() && 무장Id_isValid(target_kunshu_id) && target.isLike(target_kunshu_id))
				return true;
		}

		// 목표무장이 실행무장 세력 군주를 친애함
		if (target.isLike(actor_kunshu.getId()))
		{
			special = true;
			return true;
		}
	}

	return false;
}

int func_5c6030(Person target, Person actor, int type, int seed)
{
	if (!isalive(target) || !isalive(actor))
		return 0;

	int loyalty = target.충성도;
	int aishou = 25;
	int giri = target.의리;

	if (type == 2)
		loyalty = std::min(loyalty, 70);

	// 목표무장이 재야이거나 멸망한 세력 포로임
	if (target.isZaiya() || (target.isHoryo() && !세력Id_isValid(target.getForceId())))
		loyalty = Scenario().난이도 == 난이도_초급 ? 60 : 70;

	if (무장Id_isValid(target.군주))
		aishou = target.getAishouDistance(target.군주);

	if (target.isZaiya())
		giri = 의리_보통;

	int result = (aishou - target.getAishouDistance(actor.군주)) / 5;
	result -= (giri + 18) * loyalty * 5 / 100;
	result += std::max(actor.매력, 30) * 3 / 5;
	result -= target.isLike(target.군주) ? 15 : 0;
	result -= target.isOyako(target.군주) ? 15 : 0;
	result += target.isDislike(target.군주) ? 15 : 0;
	result += rand(의리_끝 - giri, actor.getId(), target.getId(), actor.매력, seed, actor.군주, 0, 0);
	result += target.isHoryo() ? 15 : 0;
	result += 45;
	return std::max(result, 0);
}