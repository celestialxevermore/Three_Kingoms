/**
	월별 무장 충성도 증감값을 계산합니다.
	@param building 거점
	@param person 무장(군주, 도독, 태수, 일반, 포로만 해당)
*/
int PK_월별무장충성도증감(Building building, Person person)
{
	if (person.isKunshu())
		return 0;

	// 거점에 인정 특기 보유자가 있을 경우 일반 무장은 감소하지 않음
	if (!person.isHoryo() && 무장Id_isValid(building.getWhoHasSkill(특기_인정)))
		return 0;

	// 군주가 없을 경우 감소하지 않음(멸망한 세력의 포로)
	int kunshu_id = person.군주;
	Person kunshu(kunshu_id);
	if (!isalive(kunshu))
		return 0;

	// 일반 무장은 분기별 첫 달에만 감소함(1, 4, 7, 10월)
	if (!person.isHoryo() && !Scenario().isFirstMonthOfQuarter())
		return 0;

	// 군주를 친애하거나 부부, 의형제, 부모자식 관계일 경우 감소하지 않음
	if (person.isLike(kunshu_id) || person.isFuufu(kunshu_id) || person.isGikyoudai(kunshu_id) || person.isOyako(kunshu_id))
		return 0;

	// 일반 무장이고 군주와의 궁합 25 이하(좋음)
	if (!person.isHoryo() && person.getAishouDistance(kunshu_id) <= 25)
	{
		// 의리가 보통 이상이거나 야망이 보통 이하
		if (person.의리 >= 의리_보통 || person.야망 <= 야망_보통)
		{
			// 군주를 혐오하지만 않으면 감소하지 않음
			if (!person.isDislike(kunshu_id))
				return 0;
		}
	}

	// 인심장악 기교가 연구된 경우 66% 확률로 감소 안 함
	Force force(person.getForceId());
	if (isalive(force) && force.hasTech(기교_인심장악) && rand(3) >= 1)
		return 0;

	int n = rand(3);

	City city(building.toCity());
	if (isalive(city) && city.hasFacility(시설_부절태))
		n += 2;

	// 군주의 의리가 매우낮고 야망이 매우 높음
	if (kunshu.의리 == 의리_매우낮음 && kunshu.야망 == 야망_매우높음)
		n += (의리_매우높음 - person.의리) / 2;

	n += rand(3);

	return -n;
}