/**
	월별 도시 치안 증감값을 계산합니다.
	@param city 도시
	@param month 월
*/
int PK_월별도시치안증감(City city, int month)
{
	if (month == 1 || month == 4 || month == 7 || month == 10)
	{
		int force_id = city.getForceId();
		if (!세력Id_isValid(force_id))
			return 0;

		Force force(force_id);

		// 법령정비 연구 시 50% 확률로 감소하지 않음
		if (force.hasTech(기교_법령정비) && randbool(50))
			return 0;

		int n = 90;

		Person taishu(city.태수);
		if (isalive(taishu))
			n -= taishu.매력;

		n = std::max(n, 1);

		n /= 10;
		n += rand(3);

		return -std::min(n, 5);
	}
	return 0;
}