/**
	보물 발견 확률을 계산합니다.
	@param building 실행 거점
	@param person 실행 무장
	@param item 미발견된 보물 무작위
*/
int PK_보물발견확률(Building building, Person person, Item item)
{
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/*
	return std::max((61 - item.가치) / 20, 1);
	*/
	return (266 - item.가치) / 10;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}