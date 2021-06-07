/**
	컴퓨터의 포로처우 결과를 계산합니다.
	@param prisoner 포로
	@param info 정보
	@sa
	@code
	__ptr class __4b1690
	{
	public:
		__get HexObject object;			// 포로로 잡힌 오브젝트
		__get HexObject captured_by;	// 포로를 잡은 오브젝트
		__get bool can_return;			// 귀환가능
	};
	@endcode
*/
int PK_포로처우(Person prisoner, __4b1690 info)
{
	Person kunshu(info.captured_by.군주);

	if (func_4ae3a0(prisoner, kunshu))
		return 포로처우_처단;

	if (PK_등용결과예측(prisoner, kunshu, (info.can_return ? 1 : 2), 0))
		return 포로처우_등용;

	if (func_4af5b0(prisoner, kunshu))
		return 포로처우_처단;

	if (prisoner.isKunshu())
		return 포로처우_해방;

	if (!func_4b0740(info))
		return 포로처우_해방;

	return 포로처우_포로;
}

/**
	@param prisoner 포로
	@param kunshu 포로를 잡은 세력의 군주(이해를 위해 '나'라고 표현함)
*/
bool func_4ae3a0(Person prisoner, Person kunshu)
{
	if (!isalive(prisoner) || !isalive(kunshu))
		return false;

	// 내가 포로를 혐오할 경우 처단
	if (kunshu.isDislike(prisoner.getId()))
		return true;

	if (!prisoner.isKunshu())
		return false;

	Force force(kunshu.getForceId());
	Force prisoner_force(prisoner.getForceId());

	if (!isalive(force) || !isalive(prisoner_force))
		return false;

	// 포로가 황제이고 내가 후한의 황제를 보호중일 경우 처단
	if (prisoner_force.작위 == 작위_황제 && force.isProtectingTheEmperor())
		return true;

	// 내가 황제이고 포로가 후한의 황제를 보호중일 경우 처단
	if (prisoner_force.isProtectingTheEmperor() && force.작위 == 작위_황제)
		return true;

	return false;
}

/**
	@param prisoner 포로
	@param kunshu 포로를 잡은 세력의 군주(이해를 위해 '나'라고 표현함)
*/
bool func_4af5b0(Person prisoner, Person kunshu)
{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/*
	if (kunshu.의형제 == prisoner.의형제)
		return false;
	*/

	// 위에 처럼 확인하면 의형제 값이 -1인(의형제가 없는) 무장들도 무시되어
	// 결과적으로 의형제가 다른 무장들만 처단할지 확인하게됨.
	// 일부러 그랬는지도 모르겠지만...
	if (kunshu.isGikyoudai(prisoner.getId()))
		return false;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	if (kunshu.isFuufu(prisoner.getId()))
		return false;

	if (kunshu.isLike(prisoner.getId()))
		return false;

	int max_stat = 0, avg_stat = 0;
	for (int i = 0; i < 무장능력_끝; i++)
	{
		int n = prisoner.능력[i];
		max_stat = std::max(max_stat, n);
		avg_stat += n;
	}
	avg_stat /= 무장능력_끝;

	int deaths = 10;
	switch (Scenario().전사)
	{
	case 전사_없음: deaths = 20; break;
	case 전사_표준: deaths = 10; break;
	case 전사_많음: deaths = 0; break;
	}

	if (prisoner.isKunshu())
	{
		int value = 0;
		value += (kunshu.야망 + prisoner.야망) * 2;
		value -= (std::max(max_stat, 50) + std::max(avg_stat, 50)) / 2;
		value += (16 - kunshu.의리) * 5;
		value -= deaths;
		value -= rand(20);
		return randbool(std::max(value, 0));
	}

	float value = 0;
	value += 100 - (std::max(max_stat, 50) + std::max(avg_stat, 50)) / 2;
	value -= std::max(prisoner.공적, 20000) / 2000 * (kunshu.기용 == 기용_실적 ? 1.5f : 1);
	value -= prisoner.야망 * (kunshu.기용 == 기용_의리 ? 5 : 1);
	value -= rand(25) * (kunshu.기용 == 기용_임의 ? 1.5f : 1);
	value -= deaths;
	return randbool(std::max(value, 0.f));
}

bool func_4b0740(__4b1690 info)
{
	// 멸망시킨경우 모두 해방
	if (!info.can_return)
		return false;

	// 거점을 공격해 포로를 잡음
	if (info.object.isInstance(kTypeIdBuilding))
	{
		// 부대가 잡은게 아니라면 해방
		if (!info.captured_by.isInstance(kTypeIdUnit))
			return false;

		Building building(info.object);
		Unit unit(info.captured_by);
		int pay_sum = 0;

		// 부대 무장들의 봉록 합계
		for (int i = 0; i < 3; i++)
		{
			Person member(unit.무장[i]);
			if (!isalive(member) || member.신분 < 신분_도독 || member.신분 > 신분_일반)
				continue;

			int rank_id;
			Rank rank;

			rank_id = member.관직;
			if (!관직Id_isValid(rank_id))
				rank_id = 관직_없음;

			rank = rank_id;
			if (!isalive(rank))
				continue;

			pay_sum += rank.봉록;
		}

		// 부대가 잡고 있는 포로 비용 합계
		List<Person> list;
		list.init(무장속성_신분, 신분_포로);
		list.remove_all_but(무장속성_소재, unit.getLocationId());
		pay_sum += (list.size() + 2) * 50;

		pay_sum *= 2;

		// 금이 부족하다면 해방
		if (unit.금 + building.금 < pay_sum)
			return false;
	}
	// 부대를 공격해 포로를 잡음
	else
	{
		HexObject captured_by(info.captured_by);
		Person leader;
		Building service;
		int pay_sum = 0;

		// 4b08a4
		if (captured_by.isInstance(kTypeIdUnit))
			leader = Unit(captured_by).주장;
		else if (captured_by.isInstance(kTypeIdBuilding))
			leader = Building(captured_by).태수;
		else
			leader = captured_by.군주;

		if (isalive(leader))
			service = leader.소속;

		// 포로를 잡은 오브젝트의 소속이 확인되지 않음
		if (!isalive(service))
			return false;

		// 소속거점 무장들의 봉록 합계
		for (auto i = service.소속무장.begin(); i; i++)
		{
			if (!isalive(i()) || i().신분 < 신분_도독 || i().신분 > 신분_일반)
				continue;

			int rank_id;
			Rank rank;

			rank_id = i().관직;
			if (!관직Id_isValid(rank_id))
				rank_id = 관직_없음;

			rank = rank_id;
			if (!isalive(rank))
				continue;

			pay_sum += rank.봉록;
		}

		// 소속거점 포로 비용 합계
		List<Person> list;
		list.init(무장속성_신분, 신분_포로);
		list.remove_all_but(무장속성_소재, service.getId());
		pay_sum += (list.size() + 2) * 50;

		pay_sum *= 2;

		// 소속 거점으로 귀환했을 때 포로를 유지할 수 있는 비용이 부족하다면 해방
		if (service.금 < pay_sum)
			return false;
	}

	return true;
}