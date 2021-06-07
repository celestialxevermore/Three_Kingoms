/**
	계략 크리티컬 확률을 계산합니다.
	@param src 실행 부대
	@param src_pos 실행 좌표
	@param dst_pos 목표 좌표
	@param strategy #계략Id
*/
int PK_계략_크리티컬확률(Unit src, Point src_pos, Point dst_pos, int strategy)
{
	if (!isalive(src) || !Map().isValidPos(src_pos) || !Map().isValidPos(dst_pos))
		return 0;

	int src_int = src.지력;
	int dst_int = 0;

	Hex dst_hex(dst_pos);
	if (dst_hex.hasUnit())
		dst_int = dst_hex.getUnit().지력;

	// 일반 계략
	if (strategy >= 0 && strategy <= 계략_동토 && strategy != 계략_소화)
	{
		// 신산 특기 보유
		if (src.hasSkill(특기_신산))
			return 100;
		// 심모 특기 보유
		if (src.hasSkill(특기_심모))
			return 100;
		// 모계 특기 보유자 지력이 목표 오브젝트 지력보다 높음
		if (src.getBestMemberStat(특기_묘계, 무장능력_지력) > dst_int)
			return 100;
		// 비책 특기 보유자 지력이 목표 오브젝트 지력보다 낮음
		int i = src.getBestMemberStat(특기_비책, 무장능력_지력);
		if (i > -1 && i < dst_int)
			return 100;
	}

	switch (strategy)
	{
	case 계략_화계:
		return std::max((src_int - dst_int / 2) / 10, 3);

	case 계략_소화:
		return 0;

	case 계략_위보:
		return std::max((src_int + 위보크리_성격factor(Person(src.주장).성격) - dst_int / 2) / 10, 3);

	case 계략_교란:
		return std::max((src_int + 교란크리_성격factor(Person(src.주장).성격) - dst_int / 2) / 10, 3);

	case 계략_진정:
		return std::max((src_int / 10), 3);

	case 계략_복병:
		if (src.hasSkill(특기_매복))
			return 100;
		return std::max((src_int + 복병크리_병기factor(src.getWeaponId(src_pos)) - dst_int / 2) / 10, 3);

	case 계략_동토:
		return std::max((src_int + 동토크리_의리factor(Person(src.주장).의리) - dst_int / 2) / 10, 3);

	case 계략_요술:
	case 계략_낙뢰:
		return std::max((src_int / 12), 3);
	}

	return 0;
}

int 위보크리_성격factor(int id)
{
	switch (id)
	{
	case 성격_소심: return 10;
	case 성격_냉정: return 5;
	case 성격_대담: return 0;
	case 성격_저돌: return -5;
	}
	return 0;
}

int 교란크리_성격factor(int id)
{
	switch (id)
	{
	case 성격_소심: return -5;
	case 성격_냉정: return 0;
	case 성격_대담: return 5;
	case 성격_저돌: return 10;
	}
	return 0;
}

int 복병크리_병기factor(int id)
{
	switch (id)
	{
	case 병기_창:
	case 병기_극: return 10;
	case 병기_검:
	case 병기_노: return 5;
	}
	return 0;
}

int 동토크리_의리factor(int id)
{
	switch (id)
	{
	case 의리_매우낮음: return 10;
	case 의리_낮음: return 5;
	case 의리_보통: return 0;
	case 의리_높음: return -5;
	case 의리_매우높음: return -10;
	}
	return 0;
}