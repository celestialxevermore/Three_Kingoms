/**
	계략 성공 확률을 계산합니다.
	@param[out] blocked 실패 여부
	@param src 실행 부대
	@param src_pos 실행 좌표
	@param dst_pos 목표 좌표
	@param strategy #계략Id
	@return 확률
*/
int PK_계략_성공확률(bool &out blocked, Unit src, Point src_pos, Point dst_pos, int strategy)
{
	blocked = false;

	if (!isalive(src))
		return 0;

	int src_int = src.지력;
	int dst_int = 0;
	Unit dst;
	Hex dst_hex(dst_pos);
	int a = 0;
	int result = 0;
	int bonus = 무장xml(src.주장).계략성공확률보너스;

	// 목표 부대 있음
	if (dst_hex.hasUnit())
	{
		dst = dst_hex.getUnit();
		dst_int = dst.지력;
		// 목표 부대 상태 혼란
		if (dst.상태 == 부대상태_혼란)
			a = 10;
	}

	// 낙뢰 아님, 목표 부대 있음
	if (strategy != 계략_낙뢰 && dst)
	{
		// 목표 부대 적대 관계
		if (dst.isEnemy(src))
		{
			// 목표 부대 통찰 특기 보유
			if (dst.hasSkill(특기_통찰))
			{
				blocked = true;
				return 0;
			}
		}
	}

	switch (strategy)
	{
	case 계략_화계:
		do {
			int b = 0;
			if (dst_hex.hasBuilding())
				b = 화계_시설factor(dst_hex.getBuilding().시설);
			else
				b = 화계_지형factor(dst_hex.지형);

			if (b == 100)
				return b;

			int c = 100;
			c -= dst_int * 90 / 100;
			c /= 2;
			c *= src_int * src_int * 100;
			c /= dst_int * dst_int + src_int * src_int;
			c /= 55;
			c -= (100 - src_int) / 10;
			c += a;
			c += (b / 2) - 5;

			// 목표 오브젝트 지력보다 낮음
			if (src_int < dst_int)
				c -= (dst_int - src_int) / 3;

			if (c < 1)
				c = 1;

			int d = a + (src_int * 30 / 100) - (dst_int / 5) + 55;

			// 목표 부대 없음
			if (!dst)
				d += 10;

			result = std::max(1, std::min(c, d, 99));

			// 목표 부대 있음
			if (dst)
			{
				// 목표 부대 화신 특기 보유
				if (dst.hasSkill(특기_화신) ||
					// 목표 부대 간파 특기 보유자 지력보다 낮음
					dst.getBestMemberStat(특기_간파, 무장능력_지력) > src_int ||
					// 목표 부대 신산 특기 보유자 지력보다 낮음
					dst.getBestMemberStat(특기_신산, 무장능력_지력) > src_int)
				{
					blocked = true;
					return 0;
				}

				// 화공 특기 보유자 지력이 목표 오브젝트 지력보다 높음
				if (src.getBestMemberStat(특기_화공, 무장능력_지력) > dst_int ||
					// 허실 특기 보유자 지력이 목표 오브젝트 지력보다 높음
					src.getBestMemberStat(특기_허실, 무장능력_지력) > dst_int ||
					// 화신 특기 보유자 지력이 목표 오브젝트 지력보다 높음
					src.getBestMemberStat(특기_화신, 무장능력_지력) > dst_int ||
					// 신산 특기 보유자 지력이 목표 오브젝트 지력보다 높음
					src.getBestMemberStat(특기_신산, 무장능력_지력) > dst_int)
				{
					return 100;
				}
			}
		} while (false);
		break;

	case 계략_소화:
		do {
			// 화공 특기 보유자 지력이 목표 오브젝트 지력보다 높음
			if (src.getBestMemberStat(특기_화공, 무장능력_지력) > dst_int ||
				// 허실 특기 보유자 지력이 목표 오브젝트 지력보다 높음
				src.getBestMemberStat(특기_허실, 무장능력_지력) > dst_int ||
				// 화신 특기 보유자 지력이 목표 오브젝트 지력보다 높음
				src.getBestMemberStat(특기_화신, 무장능력_지력) > dst_int ||
				// 신산 특기 보유자 지력이 목표 오브젝트 지력보다 높음
				src.getBestMemberStat(특기_신산, 무장능력_지력) > dst_int)
			{
				return 100;
			}

			float b = std::max(src.지력 - 5, 10);
			float c = sqrt(b) * 11.f;
			int d = int(c);

			result = std::max(1, std::min(d, 99));
		} while (false);
		break;

	case 계략_위보:
		do {
			// 목표 부대 없음
			if (!isalive(dst))
				return 0;

			// 목표 부대 있음
			if (dst)
			{
				// 목표 부대 규율 특기 보유
				if (dst.hasSkill(특기_규율) ||
					// 목표 부대 명경 특기 보유
					dst.hasSkill(특기_명경))
				{
					blocked = true;
					return 0;
				}
			}

			// 언독 특기 보유자 지력이 목표 오브젝트 지력보다 높음
			if (src.getBestMemberStat(특기_언독, 무장능력_지력) > dst_int ||
				// 허실 특기 보유자 지력이 목표 오브젝트 지력보다 높음
				src.getBestMemberStat(특기_허실, 무장능력_지력) > dst_int ||
				// 신산 특기 보유자 지력이 목표 오브젝트 지력보다 높음
				src.getBestMemberStat(특기_신산, 무장능력_지력) > dst_int)
			{
				return 100;
			}

			// 목표 부대 있음
			if (dst)
			{
				// 목표 부대 간파 특기 보유자 지력보다 낮음
				if (dst.getBestMemberStat(특기_간파, 무장능력_지력) > src_int ||
					// 목표 부대 신산 특기 보유자 지력보다 낮음
					dst.getBestMemberStat(특기_신산, 무장능력_지력) > src_int)
				{
					blocked = true;
					return 0;
				}
			}

			int b = 위보_성격factor(Person(dst.주장).성격);
			int c = src.매력 / 20;
			int d = src_int * 30 / 100;

			d -= dst_int / 5;
			d += c;
			d += b;

			int e = a + d + 70;

			int f = 100;

			f -= dst_int * 90 / 100;
			f *= src_int * src_int * 100;
			f /= dst_int * dst_int + src_int * src_int;
			f /= 55;
			f -= (100 - src_int) / 10;
			f += c;
			f += b;
			f += a;

			// 목표 오브젝트 지력보다 낮음
			if (src_int < dst_int)
				f -= (dst_int - src_int) / 3;

			if (f < 1)
				f = 1;

			result = std::max(1, std::min(e, f, 99));
		} while (false);
		break;

	case 계략_교란:
		do {
			// 목표 부대 없음
			if (!isalive(dst))
				return 0;

			// 목표 부대 있음
			if (dst)
			{
				// 목표 부대 침착 특기 보유
				if (dst.hasSkill(특기_침착) ||
					// 목표 부대 명경 특기 보유
					dst.hasSkill(특기_명경))
				{
					blocked = true;
					return 0;
				}
			}

			// 기략 특기 보유자 지력이 목표 오브젝트 지력보다 높음
			if (src.getBestMemberStat(특기_기략, 무장능력_지력) > dst_int ||
				// 허실 특기 보유자 지력이 목표 오브젝트 지력보다 높음
				src.getBestMemberStat(특기_허실, 무장능력_지력) > dst_int ||
				// 신산 특기 보유자 지력이 목표 오브젝트 지력보다 높음
				src.getBestMemberStat(특기_신산, 무장능력_지력) > dst_int)
			{
				return 100;
			}

			// 목표 부대 있음
			if (dst)
			{
				// 목표 부대 간파 특기 보유자 지력보다 낮음
				if (dst.getBestMemberStat(특기_간파, 무장능력_지력) > src_int ||
					// 목표 부대 신산 특기 보유자 지력보다 낮음
					dst.getBestMemberStat(특기_신산, 무장능력_지력) > src_int)
				{
					blocked = true;
					return 0;
				}
			}

			int b = 교란_성격factor(Person(dst.주장).성격);
			int c = dst.방어 / 20;
			int d = src_int * 30 / 100;

			d -= dst_int / 5;
			d += c;
			d += b;

			int e = a + d + 70;

			int f = 100;

			f -= dst_int * 90 / 100;
			f *= src_int * src_int * 100;
			f /= dst_int * dst_int + src_int * src_int;
			f /= 45;
			f -= (100 - src_int) / 10;
			f += c;
			f += b;
			f += a;

			// 목표 오브젝트 지력보다 낮음
			if (src_int < dst_int)
				f -= (dst_int - src_int) / 3;

			if (f < 1)
				f = 1;

			result = std::max(1, std::min(e, f, 99));
		} while (false);
		break;

	case 계략_진정:
		do {
			// 목표 부대 없음
			if (!isalive(dst))
				return 0;

			// 허실 특기 보유자 지력이 목표 오브젝트 지력보다 높음
			if (src.getBestMemberStat(특기_허실, 무장능력_지력) > dst_int ||
				// 신산 특기 보유자 지력이 목표 오브젝트 지력보다 높음
				src.getBestMemberStat(특기_신산, 무장능력_지력) > dst_int)
			{
				return 100;
			}

			float b = std::max(src.지력 - 5, 10);
			float c = sqrt(b) * 11.f + 진정_성격factor(Person(dst.주장).성격);
			int d = int(c);

			result = std::max(1, std::min(d, 99));
		} while (false);
		break;

	case 계략_복병:
		do {
			// 목표 부대 없음
			if (!isalive(dst))
				return 0;

			// 허실 특기 보유자 지력이 목표 오브젝트 지력보다 높음
			if (src.getBestMemberStat(특기_허실, 무장능력_지력) > dst_int ||
				// 신산 특기 보유자 지력이 목표 오브젝트 지력보다 높음
				src.getBestMemberStat(특기_신산, 무장능력_지력) > dst_int)
			{
				return 100;
			}

			// 목표 부대 있음
			if (dst)
			{
				// 목표 부대 간파 특기 보유자 지력보다 낮음
				if (dst.getBestMemberStat(특기_간파, 무장능력_지력) > src_int ||
					// 목표 부대 신산 특기 보유자 지력보다 낮음
					dst.getBestMemberStat(특기_신산, 무장능력_지력) > src_int)
				{
					blocked = true;
					return 0;
				}
			}

			int b = 복병_성격factor(Person(dst.주장).성격);
			int c = (src.공격 - dst.방어) / 10;
			int d = src_int * 30 / 100;

			d -= dst_int / 3;
			d += b;
			d += c;

			int e = a + d + 80;

			int f = 100;

			f -= dst_int * 90 / 100;
			f *= src_int * src_int * 100;
			f /= dst_int * dst_int + src_int * src_int;
			f /= 50;
			f -= (100 - src_int) / 10;
			f += b;
			f += c;
			f += a;

			// 목표 오브젝트 지력보다 낮음
			if (src_int < dst_int)
				f -= (dst_int - src_int) / 3;

			if (f < 1)
				f = 1;

			result = std::max(1, std::min(e, f, 99));
		} while (false);
		break;

	case 계략_동토:
		do {
			// 목표 부대 없음
			if (!isalive(dst))
				return 0;

			// 궤계 특기 보유자 지력이 목표 오브젝트 지력보다 높음
			if (src.getBestMemberStat(특기_궤계, 무장능력_지력) > dst_int ||
				// 허실 특기 보유자 지력이 목표 오브젝트 지력보다 높음
				src.getBestMemberStat(특기_허실, 무장능력_지력) > dst_int ||
				// 신산 특기 보유자 지력이 목표 오브젝트 지력보다 높음
				src.getBestMemberStat(특기_신산, 무장능력_지력) > dst_int)
			{
				return 100;
			}

			// 목표 부대 있음
			if (dst)
			{
				// 목표 부대 간파 특기 보유자 지력보다 낮음
				if (dst.getBestMemberStat(특기_간파, 무장능력_지력) > src_int ||
					// 목표 부대 신산 특기 보유자 지력보다 낮음
					dst.getBestMemberStat(특기_신산, 무장능력_지력) > src_int)
				{
					blocked = true;
					return 0;
				}
			}

			int b = 교란_성격factor(Person(dst.주장).성격);
			int c = dst_int * 40 / 100;
			int d = src_int * 30 / 100 - c + b;
			int e = a + d + 70;

			int f = 100;
			f -= dst_int * 90 / 100;
			f *= src_int * src_int * 100;
			f /= dst_int * dst_int + src_int * src_int;
			f /= 55;
			f -= (100 - src_int) / 10;
			f += b;
			f += a;

			// 목표 오브젝트 지력보다 낮음
			if (src_int < dst_int)
				f -= (dst_int - src_int) / 3;

			if (f < 1)
				f = 1;

			result = std::max(1, std::min(e, f, 99));
		} while (false);
		break;

	case 계략_요술:
		do {
			// 목표 부대 없음
			if (!isalive(dst))
				return 0;

			int b = 교란_성격factor(Person(dst.주장).성격);
			int c = 100 - (dst_int * 90 / 100);
			int d = src_int / 10;

			d += b;
			d += c;
			d += a;

			// 목표 부대 지력이 더 높음
			if (dst_int > src_int)
			{
				b -= (100 - src_int) / 10;
				b += c;
				d = a + b - 5;
			}

			result = std::max(1, std::min(d, 99));
			return std::min(result + bonus, 100);
		} while (false);
		break;

	case 계략_낙뢰:
		do {
			int b = src_int * 60 / 100;
			int c = a + b + 15;
			result = std::max(1, std::min(c, 99));
			return std::min(result + bonus, 100);
		} while (false);
		break;
	}

	// 경국 특기 보유
	if (src.hasSkill(특기_경국))
	{
		// 목표 부대 여성 무장 없음
		if (isalive(dst) && !dst.hasFemaleMember())
			result *= 2;
	}

	return std::min(result + bonus, 100);
}

int 화계_시설factor(int id)
{
	switch (id)
	{
	case 시설_도시:
	case 시설_관문:
	case 시설_성채:
	case 시설_석벽:
	case 시설_석병팔진:
	case 시설_동작대:
		return 10;

	case 시설_항구:
	case 시설_연노로:
	case 시설_투석대:
	case 시설_태고대:
	case 시설_군악대:
	case 시설_본거지1:
	case 시설_유적:
	case 시설_묘:
	case 시설_농장:
	case 시설_공방:
	case 시설_조선:
	case 시설_조폐:
	case 시설_곡창:
	case 시설_암시장:
	case 시설_군둔농:
	case 시설_농장2단:
	case 시설_농장3단:
		return 30;

	case 시설_진:
		return 35;

	case 시설_요새:
		return 25;

	case 시설_궁노:
	case 시설_본거지2:
	case 시설_시장:
	case 시설_병영:
	case 시설_대장간:
	case 시설_마구간:
	case 시설_부절태:
	case 시설_군사부:
	case 시설_인재부:
	case 시설_외교부:
	case 시설_계략부:
	case 시설_연병소:
	case 시설_대시장:
	case 시설_어시장:
	case 시설_시장2단:
	case 시설_시장3단:
	case 시설_병영2단:
	case 시설_병영3단:
	case 시설_대장간2단:
	case 시설_대장간3단:
	case 시설_마구간2단:
	case 시설_마구간3단:
		return 40;

	case 시설_토루:
	case 시설_제방:
		return 20;

	case 시설_불씨:
	case 시설_화염종:
	case 시설_화구:
	case 시설_화염구:
	case 시설_화선:
	case 시설_업화구:
	case 시설_업화종:
		return 100;

	case 시설_낙석:
	case 시설_얕은여:
	case 시설_산악:
	case 시설_장성:
		return 0;
	}
	return 0;
}

int 화계_지형factor(int id)
{
	switch (id)
	{
	case 지형_초원: return 40;
	case 지형_땅: return 40;
	case 지형_모래: return 40;
	case 지형_습지: return 10;
	case 지형_독천: return 10;
	case 지형_숲: return 50;
	case 지형_내: return 0;
	case 지형_강: return 0;
	case 지형_바다: return 0;
	case 지형_황무지: return 35;
	case 지형_주요도로: return 30;
	case 지형_벼랑길: return 15;
	case 지형_다리: return 20;
	case 지형_얕은여울: return 10;
	case 지형_해안: return 0;
	case 지형_언덕: return 0;
	case 지형_도시: return 0;
	case 지형_관문: return 0;
	case 지형_항구: return 0;
	case 지형_지름길: return 10;
	}
	return 0;
}

int 위보_성격factor(int id)
{
	switch (id)
	{
	case 성격_소심: return 3;
	case 성격_냉정: return 1;
	case 성격_대담: return 0;
	case 성격_저돌: return -2;
	}
	return 0;
}

int 교란_성격factor(int id)
{
	switch (id)
	{
	case 성격_소심: return -2;
	case 성격_냉정: return 0;
	case 성격_대담: return 1;
	case 성격_저돌: return 3;
	}
	return 0;
}

int 진정_성격factor(int id)
{
	switch (id)
	{
	case 성격_소심: return -5;
	case 성격_냉정: return 5;
	case 성격_대담: return 0;
	case 성격_저돌: return -10;
	}
	return 0;
}

int 복병_성격factor(int id)
{
	switch (id)
	{
	case 성격_소심: return 3;
	case 성격_냉정: return -2;
	case 성격_대담: return 0;
	case 성격_저돌: return 1;
	}
	return 0;
}

