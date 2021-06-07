/**
	유적 발견 확률
	@param unit 부대
	@param type 0: 유적, 1: 묘
*/
int PK_유적발견확률(Unit unit, int type) {
	Person leader(unit.주장);
	if (leader.공적 < 10000 || unit.매력 < 80)
		return 0;
	else if (type == 0 && unit.hasMember(무장_이적))
		return 100;
	else
		return unit.매력 / 2;
}