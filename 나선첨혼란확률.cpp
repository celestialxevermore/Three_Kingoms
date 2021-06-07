/**
	나선첨 혼란 확률을 계산합니다.
	@param unit 나선첨을 사용한 부대
	@param target 목표 부대
	@param critical 전법 크리티컬 여부
*/
int PK_나선첨혼란확률(Unit unit, Unit target, bool critical)
{
	return critical ? 100 : 30;
}