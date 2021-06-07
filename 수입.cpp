/**
	도시 금 수입
	@param city 도시
*/
int PK_도시_금수입(City city)
{
	if (!isalive(city) || !세력Id_isValid(city.getForceId()))
		return 0;

	int result = city.금수입;

	for (int i = 0; i < city.개발지수; i++)
	{
		Building building = city.개발지[i].건물;
		if (!isalive(building))
			continue;

		int facility_id = building.시설;
		switch (facility_id)
		{
		case 시설_시장:
		case 시설_대시장:
		case 시설_어시장:
		case 시설_암시장:
			if (!building.건설완료)
				continue;
			break;

		case 시설_시장2단:
			if (!building.건설완료)
				facility_id = 시설_시장;
			break;

		case 시설_시장3단:
			if (!building.건설완료)
				facility_id = 시설_시장2단;
			break;

		default:
			continue;
		}

		Facility facility(facility_id);
		if (!isalive(facility))
			continue;

		int n = facility.생산력;

		// 시장은 조폐와 인접해 있다면 1.5배
		if (facility_id == 시설_시장 || facility_id == 시설_시장2단 || facility_id == 시설_시장3단)
		{
			if (func_49ed70(building.getPos(), 시설_조폐))
				n = n * 3 / 2;
		}

		result += n;
	}

	result *= 100;

	switch (Scenario().난이도)
	{
	case 난이도_특급:
		if (city.isPlayer())
		{
			result *= 75;
			break;
		}
		result *= 125;
		break;

	case 난이도_상급:
		result *= 100;
		break;

	case 난이도_초급:
		result *= 125;
		break;
	}

	result /= 100;
	result *= std::max(city.치안, 50);
	result /= 100;
	result /= 100;

	return result;
}

/**
	도시 병량 수입
	@param city 도시
	@bug 초급난이도에서 원본과 +-1 오차가 발생할 수 있습니다.
*/
int PK_도시_병량수입(City city)
{
	if (!isalive(city) || !세력Id_isValid(city.getForceId()))
		return 0;

	int result = city.병량수입;

	for (int i = 0; i < city.개발지수; i++)
	{
		Building building = city.개발지[i].건물;
		if (!isalive(building))
			continue;

		int facility_id = building.시설;
		switch (facility_id)
		{
		case 시설_농장:
		case 시설_군둔농:
			if (!building.건설완료)
				continue;
			break;

		case 시설_농장2단:
			if (!building.건설완료)
				facility_id = 시설_농장;
			break;

		case 시설_농장3단:
			if (!building.건설완료)
				facility_id = 시설_농장2단;
			break;

		default:
			continue;
		}

		Facility facility(facility_id);
		if (!isalive(facility))
			continue;

		int n = facility.생산력;

		// 농장은 곡창과 인접해 있다면 1.5배
		if (facility_id == 시설_농장 || facility_id == 시설_농장2단 || facility_id == 시설_농장3단)
		{
			if (func_49ed70(building.getPos(), 시설_곡창))
				n = n * 3 / 2;
		}
		else if (facility_id == 시설_군둔농)
		{
			n = std::max(city.병력, 15000) * n / 15000;
		}

		result += n;
	}

	result *= 100;

	switch (Scenario().난이도)
	{
	case 난이도_특급:
		if (city.isPlayer())
		{
			result *= 75;
			break;
		}
		result *= 125;
		break;

	case 난이도_상급:
		result *= 100;
		break;

	case 난이도_초급:
		result *= 125;
		break;
	}

	result /= 100;
	result *= std::max(city.치안, 50);
	result /= 100;
	result /= 100;

	return result;
}

/**
	관문, 항구 금 수입
	@param building 관문, 항구
	@param value 도시 금 수입
*/
int PK_관문_금수입(Building building, int value)
{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/*
	return value * 20 / 100;
	*/
	return value * 1 / 100;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}

/**
	관문, 항구 병량 수입
	@param building 관문, 항구
	@param value 도시 병량 수입
*/
int PK_관문_병량수입(Building building, int value)
{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/*
	return value * 20 / 100;
	*/
	return value * 5 / 100;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}

// 인접 시설 검색
bool func_49ed70(Point pos, int facility_id)
{
	for (int i = 0; i < 방향_끝; i++)
	{
		Point neighbor = Map().getNeighbor(pos, i);
		if (!Map().isValidPos(neighbor))
			continue;
		Building building = Hex(neighbor).getBuilding();
		if (!isalive(building))
			continue;
		if (building.시설 == facility_id && building.건설완료)
			return true;
	}
	return false;
}