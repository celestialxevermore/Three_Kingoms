/**
	포로가 탈출할 확률을 계산합니다.
	@param person 포로
*/
int PK_포로탈출확률(Person person)
{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// 부대 포로일 경우에도 탈출
	/*
	Building building(person.getBuildingId());
	if (!isalive(building))
		return 0;
	*/
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	int n = person.포로기간;

	// 2개월 미만
	if (n < 2)
		return 0;

	n -= 2;
	if (n < 1)
		n = 1;

	return std::max(n * n * std::max(person.지력, person.무력, 30) / 166, 1);
}