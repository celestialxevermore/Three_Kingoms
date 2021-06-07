/**
	전법 성공 확률을 계산합니다.
	@param unit 부대
	@param pos 좌표
	@param target 목표 오브젝트
	@param tactics_id #전법Id
*/
int PK_전법성공확률(Unit unit, Point pos, HexObject target, int tactics_id)
{
	if (target.isInstance(kTypeIdUnit) && Unit(target).상태 != 부대상태_통상)
		return 100;

	int result = 기타xml().적성전법성공확률보너스[unit.적성];
	Point temp;

	switch (tactics_id)
	{
	case 전법_돌출:
	case 전법_돌격:
		result += height_diff_push_factor(height_diff(unit, target)) + 70;
		break;

	case 전법_이단첨:
		result += height_diff_push_factor(height_diff(unit, target)) + 60;
		temp = Map().getNeighbor(target.getPos(), Map().getDirection(unit.getPos(), target.getPos()));
		result += cutoff_diff(height_diff(target.getPos(), temp));
		break;

	case 전법_갈퀴:
		result += height_diff_pull_factor(height_diff(unit, target)) + 70;
		temp = Map().getNeighbor(unit.getPos(), Map().getDirection(target.getPos(), unit.getPos()));
		result += cutoff_diff(height_diff(unit.getPos(), temp));
		break;

	case 전법_나선첨:
	case 전법_횡치:
	case 전법_관시:
		result += 70;
		break;

	case 전법_화시:
		result += 화시_지형factor(Hex(target.getPos()).지형) + 75;
		break;

	case 전법_돌파:
		result += height_diff_push_factor(height_diff(unit, target)) + 65;
		break;

	case 전법_돌진:
		result += height_diff_push_factor(height_diff(unit, target)) + 60;
		temp = Map().getNeighbor(target.getPos(), Map().getDirection(unit.getPos(), target.getPos()));
		result += cutoff_diff(height_diff(target.getPos(), temp));
		break;

	case 전법_선풍:
	case 전법_난사:
	case 전법_함선격돌:
		result += 65;
		break;

	default:
		return 100;
	}

	return std::min(result + 무장xml(unit.주장).전법성공확률보너스, 100);
}

int height_diff(Point src, Point dst)
{
	return HeightMap(coordconv().hex2heightmap(src) + 2).높이 - HeightMap(coordconv().hex2heightmap(dst) + 2).높이;
}

int height_diff(HexObject src, HexObject dst)
{
	return height_diff(src.getPos(), dst.getPos());
}

int cutoff_diff(int value)
{
	// 상대보다 높음
	if (value >= 10)
		return 10;
	// 상대보다 높음
	else if (value >= 5)
		return 5;
	// 평지
	else if (value >= -5)
		return 0;
	// 상대보다 낮음
	else if (value >= -10)
		return -5;
	// 상대보다 낮음
	return -10;
}

int height_diff_push_factor(int value)
{
	return cutoff_diff(value) + 5;
}

int height_diff_pull_factor(int value)
{
	return 5 - cutoff_diff(value);
}

int 화시_지형factor(int terrain)
{
	switch (terrain)
	{
	case 지형_초원: return 0;
	case 지형_땅: return -5;
	case 지형_모래: return -5;
	case 지형_습지: return -15;
	case 지형_독천: return -15;
	case 지형_숲: return +10;
	case 지형_내: return -10;
	case 지형_강: return -10;
	case 지형_바다: return -10;
	case 지형_황무지: return 0;
	case 지형_주요도로: return 0;
	case 지형_벼랑길: return 0;
	case 지형_다리: return 0;
	case 지형_얕은여울: return -10;
	case 지형_해안: return 0;
	case 지형_언덕: return 0;
	case 지형_도시: return 0;
	case 지형_관문: return 0;
	case 지형_항구: return 0;
	case 지형_지름길: return -5;
	}
	return 0;
}