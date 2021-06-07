/**
	석병팔진 혼란 확률을 계산합니다.
	@param unit 부대
*/
int PK_석병팔진혼란확률(Unit unit)
{
	return int((1.0 - (unit.지력 * unit.지력 * 0.0001)) * 100.0 + hachijin_character_factor(Person(unit.주장).성격));
}

int hachijin_character_factor(int character)
{
	switch (character)
	{
	case 성격_소심: return 20;
	case 성격_냉정: return 10;
	case 성격_대담: return 5;
	case 성격_저돌: return 0;
	}
	return 0;
}