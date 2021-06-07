/**
	턴마다 증가할 행동력을 계산합니다.
*/
int PK_행동력(District district)
{
	Person totoku(district.도독);
	int result = 0;

	result += std::max(totoku.통솔, totoku.매력) / 5;
	if (result < 6)
		result = 6;

	int city_count = std::min(district.도시수, 6) * 10;
	result += city_count + 10;
	result += std::min(city_count, district.일반무장수);

	Person gunshi(Force(district.getForceId()).군사);
	if (isalive(gunshi))
	{
		int i = gunshi.지력;
		i -= 60;
		i /= 2;
		i += 100;
		i *= result;
		i /= 100;
		result = i;
	}

	result += district.queryValue(군단속성_건설완료시설수 + 시설_부절태) * 5;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	if (!district.isPlayer())
		result *= 2;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	return result;
}