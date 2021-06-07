/**
	계략에 필요한 소비 기력을 계산합니다.
	@param unit 부대
	@param strategy #계략Id
*/
int PK_계략_소비기력(Unit unit, int strategy)
{
	if (unit.hasSkill(특기_백출))
		return 1;

	switch (strategy)
	{
	case 계략_화계: return 10;
	case 계략_소화: return 10;
	case 계략_위보: return 15;
	case 계략_교란: return 15;
	case 계략_진정: return 10;
	case 계략_복병: return 10;
	case 계략_동토: return 20;
	case 계략_요술: return 50;
	case 계략_낙뢰: return 50;
	}

	return 0;
}