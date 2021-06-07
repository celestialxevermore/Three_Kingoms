/**
	도독 선택
*/
bool PK_도독후보비교(Person left, Person right)
{
	if (!isalive(left) || !isalive(right))
		return left.p < right.p;

	if ((left.isKunshu() && !right.isKunshu()) || (!left.isKunshu() && right.isKunshu()))
		return left.isKunshu();

	if (left.지휘 != right.지휘)
		return left.지휘 > right.지휘;

	if (left.관직 != right.관직)
		return left.관직 < right.관직;

	if (left.통솔 != right.통솔)
		return left.통솔 > right.통솔;

	return left.p < right.p;
}