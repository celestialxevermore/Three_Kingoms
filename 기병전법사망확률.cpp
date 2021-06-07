/**
	돌격, 돌진 전법에 당했을 때 사망할 확률을 계산합니다.
	@param leader 전법을 사용한 부대의 주장
	@param target 대상 부대 무장 중 무작위 1명(강운 특기 보유자 제외)
	@param critical 크리티컬 여부
	@param tactics #전법Id
*/
int PK_기병전법사망확률(Person leader, Person target, bool critical, int tactics)
{
	int result = 0;

	// 돌파 전법을 확인하는 부분이 있지만 실제로 사용되지는 않습니다.
	switch (tactics)
	{
	case 전법_돌파: result += 1; break;
	case 전법_돌진: result += 2; break;
	}

	if (Scenario().전사 == 전사_많음)
		result += 2;

	if (critical)
		result += 2;

	switch (target.성격)
	{
	case 성격_소심: result -= 1; break;
	case 성격_저돌: result += 1; break;
	}

	int diff = std::max(leader.통솔, leader.무력) - std::max(target.통솔, target.무력);

	// 목표 무장보다 능력치 낮음
	if (diff <= 0)
		result -= 3;
	// 목표 무장보다 능력치 높음
	else if (diff <= 6)
		result -= 1;
	else if (diff <= 12)
		result += 0;
	else
		result += 1;

	return result;
}