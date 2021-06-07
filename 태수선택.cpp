/**
	태수 선택
*/
bool PK_태수후보비교(Person left, Person right)
{
	if (!isalive(left) || !isalive(right) || left == right)
		return left.p < right.p;

	if ((left.신분 <= 신분_도독 || right.신분 <= 신분_도독) && left.신분 != right.신분)
		return left.신분 < right.신분;

	if (left.지휘 != right.지휘)
		return left.지휘 > right.지휘;

	if (left.통솔 != right.통솔)
		return left.통솔 > right.통솔;

	if (left.무력 != right.무력)
		return left.무력 > right.무력;

	if (left.공적 != right.공적)
		return left.공적 > right.공적;

	return left.getId() < right.getId();
}