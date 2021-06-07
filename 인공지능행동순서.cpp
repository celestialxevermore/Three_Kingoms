/**
	턴마다 실행할 행동력이 필요한 명령입니다.
	@details 행동력이 필요없는 명령의 경우 매 턴마다 실행합니다.
	@param self	컨텍스트
	@param building 기준 거점
	@see
	@code
	// 내부 구조는 아직 정확히 파악되지 않았으며 아래 내용은 스크립트에서 접근할 수 있는 정보만을 나타냅니다.
	__ptr class __99c5228
	{
	public:
		__ptr class __99c5228__18
		{
		public:
			__get bool has_enemy3;			// 3칸(관문 2칸) 이내 적 부대 있음
			__get bool has_enemy5;			// 5칸(관문 4칸) 이내 적 부대 있음
			__get int own_units;			// 구역 내 자세력 부대수
			__get int enemy_units;			// 구역 내 적 부대수
			__get int neighbor_enemy_units;	// 인접 구역 적 부대수
			__get int enemy_facilities;		// 구역 내 적 군사시설수
			__get int player_units;			// 구역 내 플레이어 부대수
			__get int officers;				// 무장수
			__get int idle_officers;		// 명령 가능한 무장수
			__get int status;				// 거점상태
			__get int required_officers;	// 필요한 무장수
		};
	
		__get __99c5228__18 base[거점_끝];
	
		// 최대 36개
		void append(int id);
	};
				
	enum 거점상태
	{
		거점상태_후방 = 0,		// 전선과의 거리 2 이상
		거점상태_경계 = 1,		// 전선과의 거리 1
		거점상태_전방 = 2,		// 전선
		거점상태_전투 = 3,		// 구역안에 적군 있음
	};

	enum 인공지능
	{
		인공지능_개발 = 1,
		인공지능_징병 = 2,
		인공지능_생산 = 3,
		인공지능_순찰 = 4,
		인공지능_거래 = 5,					// ?
		인공지능_훈련 = 6,
		인공지능_방어 = 7,
		인공지능_공격 = 8,
		인공지능_설치 = 9,
		인공지능_관문수송 = 10,			// 도시 관문 간 수송?
		인공지능_도시수송 = 11,			// 도시 간 수송
		인공지능_이동 = 12,
		인공지능_소환 = 13,
		인공지능_인재탐색 = 14,
		인공지능_무장등용 = 15,
		인공지능_포상 = 16,
		인공지능_이호경식 = 17,
		인공지능_구호탄랑 = 18,
		인공지능_유언비어 = 19,
		인공지능_타세력무장등용 = 20,
		인공지능_철거 = 21,
		인공지능_계략 = 22,
		인공지능_최소인재탐색 = 23,			// 무장 수가 난이도 값 미만일 때만(실패 예상 시 무조건 안함): 인공지능.xml
		인공지능_최소무장등용 = 24,			// 무장 수가 난이도 값 미만일 때만(성공 예상 시 무조건 시도): 인공지능.xml
		인공지능_최소타세력무장등용 = 25,	// 무장 수가 3명 미만일 때만: 인공지능.xml
		인공지능_거래2 = 26,				// ?
		인공지능_흡수합병 = 27,
	};
	@endcode
*/
void PK_행동순서(__99c5228 self, Building building)
{
	int id = building.getId();
	__99c5228__18 base = self.base[id];

	// 주변 3칸 안에 적 있음(관문, 항구일 경우 2칸)
	if (base.has_enemy3)
	{
		self.append(인공지능_방어);
		if (id >= 건물_도시_시작 && id < 건물_도시_끝)
		{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			/*
			self.append(인공지능_징병);
			self.append(인공지능_순찰);
			self.append(인공지능_생산);
			self.append(인공지능_철거);
			*/

			// 플레이어가 공격중일 때만 방어 강화
			if (base.player_units > 0)
			{
				self.append(인공지능_순찰);
				self.append(인공지능_징병);
				self.append(인공지능_순찰);
				self.append(인공지능_징병);
				self.append(인공지능_순찰);
				self.append(인공지능_생산);
				self.append(인공지능_생산);
				self.append(인공지능_철거);
			}
			else
			{
				self.append(인공지능_징병);
				self.append(인공지능_순찰);
				self.append(인공지능_생산);
				self.append(인공지능_철거);
			}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		}
		return;
	}

	// 명령 가능한 무장 없음
	if (base.idle_officers == 0)
		return;

	// 도시
	if (id >= 건물_도시_시작 && id < 건물_도시_끝)
	{
		int gold = building.금;

		int required_officers = base.required_officers;
		if (required_officers < 10)
			required_officers = 10;

		int total_weapons = 0;
		for (int i = 0; i < 병기_충차; i++)
			total_weapons += building.병기[i];

		switch (base.status)
		{
		case 거점상태_후방:
			self.append(인공지능_순찰);
			self.append(인공지능_포상);
			self.append(인공지능_최소인재탐색);
			self.append(인공지능_최소무장등용);
			self.append(인공지능_최소타세력무장등용);
			self.append(인공지능_포상);
			self.append(인공지능_거래);
			self.append(인공지능_계략);
			self.append(인공지능_생산);
			self.append(인공지능_도시수송);
			self.append(인공지능_관문수송);
			self.append(인공지능_이동);
			self.append(인공지능_거래2);
			self.append(인공지능_징병);
			self.append(인공지능_훈련);
			self.append(인공지능_철거);
			self.append(인공지능_개발);
			self.append(인공지능_흡수합병);
			self.append(인공지능_관문수송);
			self.append(인공지능_인재탐색);
			self.append(인공지능_무장등용);
			self.append(인공지능_타세력무장등용);
			self.append(인공지능_포상);
			self.append(인공지능_계략);
			break;

		case 거점상태_경계:
			self.append(인공지능_공격);
			self.append(인공지능_도시수송);
			self.append(인공지능_관문수송);
			self.append(인공지능_이동);
			self.append(인공지능_최소인재탐색);
			self.append(인공지능_최소무장등용);
			self.append(인공지능_최소타세력무장등용);
			self.append(인공지능_포상);
			self.append(인공지능_징병);
			self.append(인공지능_순찰);
			self.append(인공지능_계략);
			self.append(인공지능_거래2);
			self.append(인공지능_거래);
			self.append(인공지능_생산);
			self.append(인공지능_훈련);
			self.append(인공지능_철거);
			self.append(인공지능_개발);
			self.append(인공지능_흡수합병);
			self.append(인공지능_관문수송);
			self.append(인공지능_인재탐색);
			self.append(인공지능_무장등용);
			self.append(인공지능_타세력무장등용);
			self.append(인공지능_포상);
			self.append(인공지능_계략);
			break;

		case 거점상태_전방:
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			/*
			self.append(인공지능_공격);
			self.append(인공지능_설치);
			self.append(인공지능_포상);
			self.append(인공지능_최소인재탐색);
			self.append(인공지능_최소무장등용);
			self.append(인공지능_최소타세력무장등용);
			self.append(인공지능_포상);
			self.append(인공지능_징병);
			self.append(인공지능_순찰);
			self.append(인공지능_훈련);
			self.append(인공지능_계략);
			self.append(인공지능_거래2);
			self.append(인공지능_거래);
			self.append(인공지능_생산);
			self.append(인공지능_철거);
			self.append(인공지능_개발);
			self.append(인공지능_흡수합병);
			self.append(인공지능_도시수송);
			self.append(인공지능_이동);
			self.append(인공지능_관문수송);
			self.append(인공지능_인재탐색);
			self.append(인공지능_무장등용);
			self.append(인공지능_타세력무장등용);
			self.append(인공지능_포상);
			self.append(인공지능_계략);
			*/

			self.append(인공지능_공격);
			self.append(인공지능_설치);
			self.append(인공지능_관문수송);
			self.append(인공지능_포상);
			self.append(인공지능_최소인재탐색);
			self.append(인공지능_최소무장등용);
			self.append(인공지능_최소타세력무장등용);
			self.append(인공지능_포상);
			self.append(인공지능_철거);
			self.append(인공지능_흡수합병);
			self.append(인공지능_개발);
			// 무장과 금이 충분한 경우 내정시설 2개씩 건설
			if (base.officers >= required_officers && gold > 1500)
				self.append(인공지능_개발);
			// 병기가 병력보다 모자르다면 병기생산 우선
			if (total_weapons < building.병력 - 5000)
				self.append(인공지능_생산);
			self.append(인공지능_징병);
			self.append(인공지능_순찰);
			self.append(인공지능_훈련);
			self.append(인공지능_거래2);
			self.append(인공지능_거래);
			self.append(인공지능_생산);
			self.append(인공지능_이동);
			self.append(인공지능_인재탐색);
			self.append(인공지능_무장등용);
			self.append(인공지능_타세력무장등용);
			self.append(인공지능_포상);
			self.append(인공지능_계략);
			self.append(인공지능_계략);
			self.append(인공지능_계략);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			break;

		case 거점상태_전투:
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			/*
			self.append(인공지능_방어);
			self.append(인공지능_철거);
			self.append(인공지능_포상);
			self.append(인공지능_징병);
			self.append(인공지능_훈련);
			self.append(인공지능_거래);
			self.append(인공지능_순찰);
			self.append(인공지능_생산);
			self.append(인공지능_계략);
			self.append(인공지능_거래2);
			self.append(인공지능_포상);
			self.append(인공지능_인재탐색);
			self.append(인공지능_무장등용);
			self.append(인공지능_타세력무장등용);
			self.append(인공지능_포상);
			self.append(인공지능_계략);
			*/

			self.append(인공지능_방어);
			// 적 군사시설만 있음
			if (base.enemy_units == 0)
			{
				self.append(인공지능_흡수합병);
				self.append(인공지능_개발);
				if (base.officers >= required_officers && gold > 1500)
					self.append(인공지능_개발);
			}
			// 적 부대 있음
			else
			{
				// 자세력 부대 수와 남아 있는 무장 수의 합이 적 세력 부대 수보다 적을 때만 철거
				if (base.own_units + base.idle_officers < base.enemy_units)
				{
					self.append(인공지능_철거);
				}
				else if (base.own_units > base.enemy_units && building.병력 > 15000)
				{
					self.append(인공지능_흡수합병);
					self.append(인공지능_개발);
				}
			}
			// 병기가 병력보다 모자르다면 병기생산 우선
			if (total_weapons < building.병력 - 5000)
				self.append(인공지능_생산);
			self.append(인공지능_징병);
			self.append(인공지능_훈련);
			self.append(인공지능_거래);
			self.append(인공지능_순찰);
			self.append(인공지능_생산);
			self.append(인공지능_거래2);
			self.append(인공지능_포상);
			self.append(인공지능_인재탐색);
			self.append(인공지능_무장등용);
			self.append(인공지능_타세력무장등용);
			self.append(인공지능_포상);
			self.append(인공지능_계략);
			self.append(인공지능_계략);
			self.append(인공지능_계략);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			break;
		}
	}
	// 관문, 항구
	else
	{
		switch (base.status)
		{
		case 거점상태_후방:
			self.append(인공지능_포상);
			self.append(인공지능_도시수송);
			self.append(인공지능_관문수송);
			self.append(인공지능_이동);
			self.append(인공지능_훈련);
			self.append(인공지능_계략);
			self.append(인공지능_인재탐색);
			self.append(인공지능_무장등용);
			self.append(인공지능_타세력무장등용);
			self.append(인공지능_포상);
			self.append(인공지능_계략);
			break;

		case 거점상태_경계:
			self.append(인공지능_공격);
			self.append(인공지능_도시수송);
			self.append(인공지능_관문수송);
			self.append(인공지능_이동);
			self.append(인공지능_포상);
			self.append(인공지능_훈련);
			self.append(인공지능_계략);
			self.append(인공지능_인재탐색);
			self.append(인공지능_무장등용);
			self.append(인공지능_타세력무장등용);
			self.append(인공지능_포상);
			self.append(인공지능_계략);
			break;

		case 거점상태_전방:
			self.append(인공지능_포상);
			self.append(인공지능_공격);
			self.append(인공지능_설치);
			self.append(인공지능_훈련);
			self.append(인공지능_도시수송);
			self.append(인공지능_이동);
			self.append(인공지능_관문수송);
			self.append(인공지능_계략);
			self.append(인공지능_인재탐색);
			self.append(인공지능_무장등용);
			self.append(인공지능_타세력무장등용);
			self.append(인공지능_포상);
			self.append(인공지능_계략);
			break;

		case 거점상태_전투:
			self.append(인공지능_방어);
			self.append(인공지능_훈련);
			self.append(인공지능_도시수송);
			self.append(인공지능_이동);
			self.append(인공지능_도시수송);
			self.append(인공지능_포상);
			self.append(인공지능_계략);
			break;
		}
	}
}