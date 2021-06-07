/**
	부대 능력치 계산.
	능력치가 범위를 벗어날 경우 자동으로 조정됩니다.
	@param[out] ability 결과
	@param member 무장
	@param weapon_id #병기Id
	@param troops 병력
	@param type #부대종류Id
	@param status #부대상태Id
	@param navy 수상부대
	@param shoubyou 상병포함
*/
void PK_부대능력치(Unit__ac ability, const arrayptr<Person> &in member, int weapon_id, int troops, int type, int status, bool navy, bool shoubyou)
{
	Person leader = member[0];
	if (!isalive(leader))
		return;

	Force force = leader.getForceId();
	if (!isalive(force))
		return;

	if (!병기Id_isValid(weapon_id) || !부대종류Id_isValid(type) || !부대상태Id_isValid(status))
		return;

	// 부장 있음
	if (bool(member[1]) || bool(member[2]))
	{
		// 혐오 관계가 있다면 보정하지 않음
		if (func_4960d0(leader, member[1]) || func_4960d0(leader, member[2]) || func_4960d0(member[1], member[2]))
		{
			for (int i = 0; i < 무장능력_끝; i++)
				ability.능력[i] = leader.getStat(i, shoubyou);
		}
		// 혐오 관계가 없다면 보정
		else
		{
			for (int i = 0; i < 무장능력_끝; i++)
			{
				int a = 0;
				int b = 0;
				int leader_stat = leader.getStat(i, shoubyou);

				// 통솔, 무력은 무장 관계에 따라 보정
				if (i <= 무장능력_무력)
				{
					if (member[1]) a = func_495ff0(leader, leader_stat, member[1], member[1].getStat(i, shoubyou));
					if (member[2]) b = func_495ff0(leader, leader_stat, member[2], member[2].getStat(i, shoubyou));
				}
				// 지력, 정치, 매력은 최대값
				else
				{
					if (member[1]) a = std::max(leader_stat, member[1].getStat(i, shoubyou));
					if (member[2]) b = std::max(leader_stat, member[2].getStat(i, shoubyou));
				}

				ability.능력[i] = std::max(a, b);
			}
		}
	}
	// 부장 없음
	else
	{
		// 주장 능력치 그대로 사용
		for (int i = 0; i < 무장능력_끝; i++)
			ability.능력[i] = leader.getStat(i, shoubyou);
	}

	for (int i = 0; i < 병종_끝; i++)
	{
		int max = 0;
		for (int j = 0; j < 3; j++)
		{
			if (member[j])
				max = std::max(max, member[j].적성[i]);
		}
		ability.적성[i] = max;
	}

	const float onethrid = (1.f / 3.f);
	const float twothrid = (2.f / 3.f);

	int tekisei = ability.적성[병기Id_to병종Id(weapon_id)];
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/*
	float tekisei_factor = (tekisei + 7) * 0.1f;
	*/
	float tekisei_factor = 기타xml().적성부대능력[tekisei];
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	float status_factor = 1.0f;
	float type_factor1 = 1.0f;
	float type_factor2 = 1.0f;

	Equipment e(weapon_id);

	int atk = e.공격;
	int def = e.방어;
	int mov = e.이동;

	// 검병이거나 수송부대
	if (weapon_id == 병기_검 || (weapon_id == 병기_주가 && type == 부대종류_수송))
		tekisei_factor = 0.6f;

	if (status == 부대상태_혼란)
		status_factor = 0.8f;

	if (type == 부대종류_수송)
	{
		type_factor1 = 0.4f;
		type_factor2 = onethrid;
	}

	if (weapon_id <= 병기_군마)
	{
		int tech_id = -1;
		switch (weapon_id)
		{
		case 병기_창: tech_id = 기교_정예창병; break;
		case 병기_극: tech_id = 기교_정예극병; break;
		case 병기_노: tech_id = 기교_정예노병; break;
		case 병기_군마: tech_id = 기교_정예기병; break;
		}
		if (force.hasTech(tech_id))
		{
			atk += 10;
			def += 10;
		}
	}

	ability.능력[부대능력_공격] = int(std::max(1.f, ability.능력[부대능력_무력] * atk * tekisei_factor * 0.01f * type_factor1 * status_factor));
	ability.능력[부대능력_방어] = int(std::max(1.f, ability.능력[부대능력_통솔] * def * tekisei_factor * 0.01f * type_factor2 * status_factor));
	float build = ((ability.능력[부대능력_정치] * twothrid) + 50.f) * type_factor2 * status_factor;
	ability.능력[부대능력_건설] = int(std::max(1.f, build));

	if (type == 부대종류_전투)
	{
		switch (weapon_id)
		{
		case 병기_창:
			if (force.hasTech(기교_정예창병))
				mov += 6;
			break;
		case 병기_극:
			if (force.hasTech(기교_정예극병))
				mov += 6;
			break;
		case 병기_노:
			if (force.hasTech(기교_정예노병))
				mov += 6;
			break;
		case 병기_군마:
			if (force.hasTech(기교_정예기병))
				mov += 2;
			if (force.hasTech(기교_양마산출))
				mov += 4;
			break;
		case 병기_충차:
		case 병기_정란:
		case 병기_투석:
		case 병기_목수:
			if (force.hasTech(기교_차축강화))
				mov += 4;
			break;
		}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if (weapon_id <= 병기_노)
		{
			mov += u::getSkillInt(member, 특기_강행);
		}
		else if (weapon_id == 병기_군마)
		{
			if (u::hasSkill(member, 특기_강행))
				mov += u::getSkillInt(member, 특기_강행);
			else if (u::hasSkill(member, 특기_행군))
				mov += u::getSkillInt(member, 특기_행군);
		}
	}
	else
	{
		if (force.hasTech(기교_목우유마))
			mov += 3;
		mov += 5;
		mov += u::getSkillInt(member, 특기_운반);
	}

	if (navy)
		mov += u::getSkillInt(member, 특기_조타);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	ability.능력[부대능력_이동] = mov;
}

// 서로 상대방을 혐오하는 관계가 있는지 확인
bool func_4960d0(Person a, Person b)
{
	if (bool(a) && bool(b))
		return a.isDislike(b.getId()) || b.isDislike(a.getId());
	return false;
}

// 관계에 따른 능력 보정
int func_495ff0(Person leader, uint8 leader_stat, Person deputy, uint8 deputy_stat)
{
	// 주장의 능력치가 부장보다 높다면 보정 없음
	if (leader_stat > deputy_stat)
		return leader_stat;

	int leader_id = leader.getId();
	int deputy_id = deputy.getId();

	if (leader.isGikyoudai(deputy_id) || leader.isFuufu(deputy_id))
		return deputy_stat;

	if (leader.isLike(deputy_id) || deputy.isLike(leader_id))
		return leader_stat + (deputy_stat - leader_stat) / 2;

	if (leader.isKetsuen(deputy_id))
		return leader_stat + (deputy_stat - leader_stat) / 3;

	if (leader.isDislike(deputy_id) || deputy.isDislike(leader_id))
		return leader_stat;

	return leader_stat + (deputy_stat - leader_stat) / 4;
}