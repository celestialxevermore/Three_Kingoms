/** 황건의 난 */
bool PK_역사이벤트0(bool cond)
{
	if (cond)
	{
		if (Scenario().번호 != 0)
			return false;
		if (Scenario().getElapsedDays() != 0)
			return false;
		if (!Person(무장_장각).isIdle())
			return false;
		if (!Person(무장_장보).isIdle())
			return false;
		if (!Person(무장_장량).isIdle())
			return false;
		if (!Person(무장_황보숭).isIdle())
			return false;
		if (!Person(무장_주준).isIdle())
			return false;
		if (!Person(무장_노식).isIdle())
			return false;
		return true;
	}

	trgmsg().setPerson(2, 무장_하진);
	trgmsg().setPerson(3, 무장_장각);
	trgmsg().setPerson(4, 무장_황보숭);
	trgmsg().setPerson(5, 무장_주준);
	trgmsg().setPerson(6, 무장_노식);

	trgsound().playBgm(16);
	trgscene().move(Building(Person(무장_장각).소속), 0);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgmsg(15094, 무장_장각, 무장_장보);
	trgsound().playSfx(610);
	trgmsg(15095, 무장_장보, 무장_장각);
	trgmsg(15096, 무장_장량, 무장_장각);
	trgmsg(15097, 무장_장각, 무장_장보);
	trgscene().effect(18);
	trgmsg(15098, 무장_황건적, 무장_장각);
	trgsound().playSfx(613);
	trgmsg(15099, 무장_장량, 무장_사자);
	trgmsg(15100, 무장_장보, 무장_장각);
	trgmsg(15101, 무장_장각, 무장_장보);
	trgscene().effect(20);
	trgmsg(15102, 무장_장각, 무장_장보);
	trgsound().playSfx(604);
	trgscene().eventStill(8);
	trgmsg(15103, 무장_황건적, 무장_장각);
	trgscene().closeEventStill();
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().move(Building(Person(무장_하진).소속));
	trgscene().fade(0);
	trgsleep();
	trgscene().background(1, 1);
	trgscene().fade(255);
	trgmsg(15104, 무장_영제, 무장_하진);
	trgmsg(15105, 무장_하진, 무장_영제);
	trgscene().effect(18);
	trgsound().playSfx(12);
	trgmsg(15106, 무장_사자, 무장_영제);
	trgmsg(15107, 무장_영제, 무장_하진);
	trgmsg(15108, 무장_하진, 무장_영제);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgmsg(15109, 무장_하진, 무장_황보숭);
	trgsound().playSfx(610);
	trgscene().eventStill(21);
	trgmsg(15110, 무장_황보숭, 무장_하진);
	trgmsg(15111, 무장_노식, 무장_하진);
	trgmsg(15112, 무장_주준, 무장_하진);
	trgmsg(15113, 무장_하진, 무장_황보숭);
	trgscene().closeEventStill();
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().eventStill(3);
	trgsound().playSfx(603);
	trgmsg(15114);
	trgscene().closeEventStill();

	return true;
}

/** 소제 폐위 */
bool PK_역사이벤트1(bool cond)
{
	if (cond)
	{
		if (!Person(무장_동탁).isIdle())
			return false;
		if (!Person(무장_이유).isIdle())
			return false;
		if (Scenario().getStartDayCount() > daycount(189, 8, 1))
			return false;
		if (daycount(189, 9, 1) > Scenario().getDayCount())
			return false;
		if (Scenario().황제 != 무장_소제)
			return false;
		int force_id = Person(무장_동탁).getForceId();
		if (force_id == -1)
			return false;
		if (Force(force_id).군주 != 무장_동탁)
			return false;
		if (!Force(force_id).isProtectingTheEmperor())
			return false;
		if (City(도시_장안).getForceId() != force_id)
			return false;
		if (City(도시_낙양).getForceId() != force_id)
			return false;
		if (Person(무장_이유).getForceId() != force_id)
			return false;
		return true;
	}

	trgmsg().setPerson(2, 무장_소제);
	trgmsg().setPerson(3, 무장_헌제);

	trgsound().playBgm(20);
	trgscene().move(Building(Person(무장_동탁).소속), 1200);
	trgsleep(800);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(1);
	trgscene().fade(255);
	trgscene().effect(16);
	trgmsg(15134, 무장_이유, 무장_동탁);
	if (Force(Person(무장_동탁).getForceId()).isPlayer())
	{
		trgchooser().setItems(15135, 15136);
		if (trgchooser().show(15137, 무장_동탁, 무장_이유) != 0)
		{
			trgmsg(15138, 무장_동탁, 무장_이유);
			return true;
		}
	}
	trgscene().effect(17);
	trgmsg(15139, 무장_동탁, 무장_이유);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgscene().effect(13);
	trgmsg(15140, 무장_동탁, 무장_이유);
	trgmsg(15141, 무장_이유, 무장_동탁);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(1);
	trgscene().fade(255);
	trgscene().effect(20);
	trgmsg(15142, 무장_동탁, 무장_소제);
	trgmsg(15143, 무장_소제, 무장_동탁);
	trgmsg(15144, 무장_동탁, 무장_소제);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgmsg(15145, 무장_동탁, 무장_이유);
	trgscene().effect(16);
	trgmsg(15146, 무장_이유, 무장_동탁);
	trgscene().fade(0);
	trgsleep(2000);
	trgscene().fade(255);
	trgscene().effect(16);
	trgmsg(15147, 무장_이유, 무장_동탁);
	trgmsg(15148, 무장_동탁, 무장_이유);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(1);
	trgscene().fade(255);
	trgmsg(15149, 무장_동탁, 무장_헌제);
	trgmsg(15150, 무장_헌제, 무장_동탁);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().eventStill(4);
	trgsound().playSfx(12);
	trgmsg(15151);
	trgscene().closeEventStill();

	Scenario().setEmperor(무장_헌제);

	return true;
}

/** 반동탁 연합 */
bool PK_역사이벤트2(bool cond)
{
	if (cond)
	{
		if (Scenario().번호 != 1)
			return false;
		if (Scenario().턴수 != 0)
			return false;
		if (!Person(무장_동탁).isIdle())
			return false;
		if (!Person(무장_조조).isIdle())
			return false;
		if (!Person(무장_원소).isIdle())
			return false;
		return true;
	}

	trgmsg().setPerson(2, 무장_동탁);
	trgmsg().setPerson(3, 무장_조조);
	trgmsg().setPerson(4, 무장_원소);
	trgmsg().setCity(0, 도시_진류);

	trgsound().playBgm(17);
	trgscene().move(Building(Person(무장_조조).소속), 0);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgmsg(15152, 무장_조조, 무장_하후돈);
	trgmsg(15153, 무장_하후돈, 무장_조조);
	trgscene().effect(17);
	trgmsg(15154, 무장_조조, 무장_하후돈);
	trgmsg(15155, 무장_하후돈, 무장_조조);
	trgmsg(15156, 무장_조조, 무장_하후돈);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().move(Building(Person(무장_원소).소속), 1200);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgsound().playSfx(601);
	trgmsg(15157, 무장_사자, 무장_원소);
	trgscene().effect(14);
	trgmsg(15158, 무장_원소, 무장_사자);
	trgscene().eventStill(21);
	trgmsg(15159, 무장_봉기, 무장_원소);
	trgsound().playSfx(11);
	trgmsg(15160, 무장_원소, 무장_봉기);
	trgscene().closeEventStill();
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().move(Building(Person(무장_동탁).소속), 800);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(1);
	trgscene().fade(255);
	trgscene().effect(18);
	trgmsg(15161, 무장_무관, 무장_동탁);
	trgscene().effect(13);
	trgmsg(15162, 무장_동탁, 무장_이유);
	trgmsg(15163, 무장_이유, 무장_동탁);
	trgmsg(15164, 무장_동탁, 무장_이유);
	trgmsg(15165, 무장_이유, 무장_동탁);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().eventStill(24);
	trgsound().playSfx(603);
	trgmsg(15166);
	trgscene().closeEventStill();

	return true;
}

/** 원술, 스스로 자신이 황제라고 참칭하다. */
bool PK_역사이벤트3(bool cond)
{
	if (cond)
	{
		if (!Person(무장_원술).isIdle())
			return false;
		if (Person(무장_원술).신분 != 신분_군주)
			return false;
		if (30 > Scenario().getElapsedDays())
			return false;
		int force_id = Person(무장_원술).getForceId();
		if (Force(force_id).isProtectingTheEmperor())
			return false;
		if (Item(보물_옥새).소유무장 != 무장_원술)
			return false;
		if (Force(force_id).작위 == 작위_황제)
			return false;
		if (3 > Force(force_id).도시수)
			return false;
		if (List<Force>().init(세력속성_국호, 국호_성) != 0)
			return false;
		return true;
	}

	trgmsg().setPerson(2, 무장_원술);
	trgmsg().setItem(0, 보물_옥새);

	trgsound().playBgm(20);
	trgscene().move(Building(Person(무장_원술).소속), 800);
	trgmsg(15433);
	trgmsg(15434, 무장_원술);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(1);
	trgscene().fade(255);
	trgscene().effect(17);
	trgmsg(15435, 무장_원술);
	int var0 = 무장_문관;
	if (Person(무장_염상).군주 == 무장_원술 && Person(무장_염상).isIdle())
		var0 = 무장_염상;
	trgscene().effect(13);
	trgmsg(15436, var0, 무장_원술);
	trgmsg(15437, 무장_원술, var0);
	trgmsg(15438, var0, 무장_원술);
	if (Person(무장_원술).isPlayer())
	{
		trgchooser().setItems(15440, 15441);
		if (trgchooser().show(15439, 무장_원술) != 0)
		{
			trgmsg(15442, 무장_원술, var0);
			return true;
		}
	}
	trgscene().effect(20);
	trgmsg(15443, 무장_원술, var0);
	trgmsg(15444, var0, 무장_원술);
	trgmsg(15445, 무장_원술, var0);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().eventStill(4);
	trgsound().playSfx(12);
	trgmsg(15446);
	trgscene().closeEventStill();

	int force_id = Person(무장_원술).getForceId();

	Force(force_id).setTitle(작위_황제);
	Force(force_id).setKokugou(국호_성);

	List<Force> forces;
	List<Person> officers;

	officers.push_back(무장_조조);
	officers.push_back(무장_유비);
	officers.push_back(무장_손견);
	officers.push_back(무장_손책);
	officers.push_back(무장_손권);
	officers.push_back(무장_여포);
	officers.push_back(무장_원소);

	forces.init(세력속성_플레이어, false);
	forces.remove(force_id);
	for (auto i = forces.begin(); i; i++)
	{
		if (i().isProtectingTheEmperor() || Person(i().군주).한실 == 한실_중시 || officers.contains(i().군주))
		{
			i().unally(force_id);
			i().setRelations(force_id, 0);
		}
	}

	forces.init(세력속성_플레이어, true);
	forces.remove(force_id);
	for (auto i = forces.begin(); i; i++)
	{
		if (!i().isEnemy(force_id) || i().우호도[force_id] >= 75)
			continue;

		if (i().isProtectingTheEmperor() || Person(i().군주).한실 == 한실_중시 || officers.contains(i().군주))
			i().addRelations(force_id, -50);
	}

	return true;
}

/** 이강 개전 */
bool PK_역사이벤트4(bool cond)
{
	if (cond)
	{
		if (!Person(무장_조조).isIdle())
			return false;
		if (!Person(무장_원소).isIdle())
			return false;
		if (Person(무장_조조).신분 != 신분_군주)
			return false;
		if (Person(무장_원소).신분 != 신분_군주)
			return false;
		if (Scenario().번호 == 3 && Scenario().getElapsedDays() == 0)
			return true;
		if (daycount(199, 12, 1) < Scenario().getDayCount())
			return false;
		if (Person(무장_조조).isCloseWith(무장_원소))
			return false;
		if (!Force(Person(무장_조조).getForceId()).isEnemy(Person(무장_원소).getForceId()))
			return false;
		List<City> list;
		list.init(도시속성_지방, 지방_중원);
		if (list.remove_all_but(도시속성_세력, Person(무장_조조).getForceId()) < 5)
			return false;
		list.init(도시속성_지방, 지방_하북);
		if (list.remove_all_but(도시속성_세력, Person(무장_원소).getForceId()) < 5)
			return false;
		if (!Force(Person(무장_조조).getForceId()).hasNeighborCity(Person(무장_원소).getForceId()))
			return false;
		return true;
	}

	trgmsg().setPerson(2, 무장_조조);
	trgmsg().setPerson(3, 무장_원소);
	trgmsg().setPerson(4, 무장_진림);

	trgsound().playBgm(16);
	trgscene().move(Building(Person(무장_원소).소속), 0);
	trgmsg(15447, 무장_원소);
	trgmsg(15448, 무장_위병);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(1);
	trgscene().fade(255);
	trgscene().effect(20);
	trgmsg(15449, 무장_원소);
	trgscene().effect(13);
	trgmsg(15450, (Person(무장_전풍).군주 == 무장_원소 && Person(무장_전풍).isIdle()) ? 무장_전풍 : 무장_문관, 무장_원소);
	trgmsg(15451, (Person(무장_저수).군주 == 무장_원소 && Person(무장_저수).isIdle()) ? 무장_저수 : 무장_문관, 무장_원소);
	trgscene().effect(17);
	trgmsg(15452, (Person(무장_곽도).군주 == 무장_원소 && Person(무장_곽도).isIdle()) ? 무장_곽도 : 무장_문관, 무장_원소);
	trgmsg(15453, (Person(무장_심배).군주 == 무장_원소 && Person(무장_심배).isIdle()) ? 무장_심배 : 무장_문관, 무장_원소);
	trgmsg(15454, 무장_원소);
	bool var0 = Person(무장_진림).군주 == 무장_원소 && Person(무장_진림).isIdle();
	if (var0)
	{
		trgmsg(15455, 무장_원소, 무장_진림);
		trgsound().playSfx(610);
		trgscene().eventStill(21);
		trgmsg(15456, 무장_진림, 무장_원소);
		trgmsg(15457, 무장_원소, 무장_진림);
		trgmsg(15458, 무장_진림, 무장_원소);
		trgscene().closeEventStill();
	}
	else
	{
		trgsound().playSfx(610);
		trgscene().eventStill(21);
		trgmsg(15459, 무장_원소, 무장_천문관);
		trgmsg(15456, 무장_천문관, 무장_원소);
		trgscene().closeEventStill();
	}
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().move(Building(Person(무장_조조).소속));
	trgscene().fade(0);
	trgsleep();
	trgscene().background(1);
	trgscene().fade(255);
	trgsound().playSfx(12);
	trgmsg(15460, 무장_사자, 무장_조조);
	trgscene().effect(14);
	trgmsg(15461, 무장_조조, 무장_사자);
	if (var0)
	{
		trgscene().effect(13);
		trgmsg(15462, 무장_조조);
		trgmsg(15463, 무장_문관);
		trgscene().eventStill(21);
		trgmsg(15464, 무장_조조, 무장_사자);
		trgmsg(15465, 무장_사자, 무장_조조);
		trgmsg(15466, 무장_조조);
		trgscene().closeEventStill();
		trgscene().effect(20);
		trgmsg(15467, 무장_조조);
	}
	else
	{
		trgmsg(15468, 무장_조조);
	}
	trgscene().fade(0);
	trgsleep(2000);
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().eventStill(24);
	trgsound().playSfx(603);
	trgmsg(15469);
	trgscene().closeEventStill();

	Force(Person(무장_조조).getForceId()).setRelations(Person(무장_원소).getForceId(), 0);
	Force(Person(무장_조조).getForceId()).unally(Person(무장_원소).getForceId());

	return true;
}

/** 조조, 남정 */
bool PK_역사이벤트5(bool cond)
{
	if (cond)
	{
		if (Person(무장_조조).신분 != 신분_군주)
			return false;
		if (!Person(무장_조조).isIdle())
			return false;
		if (Scenario().getElapsedDays() < 30)
			return false;
		int force_id = Person(무장_조조).getForceId();
		if (City(도시_허창).getForceId() != force_id)
			return false;
		if (City(도시_완).getForceId() != force_id)
			return false;
		if (City(도시_신야).getForceId() == force_id)
			return false;
		List<City> list;
		list.init(도시속성_지방, 지방_중원);
		if (list.remove_all_but(도시속성_세력, force_id) < 7)
			return false;
		list.init(도시속성_지방, 지방_하북);
		int var0 = list.remove(도시_양평);
		if (list.remove_all_but(도시속성_세력, force_id) < var0)
			return false;
		list.init(도시속성_지방, 지방_강동);
		if (0 < list.remove_all_but(도시속성_세력, force_id))
			return false;
		list.clear();
		list.push_back(도시_양양);
		list.push_back(도시_강릉);
		list.push_back(도시_시상);
		list.push_back(도시_건업);
		for (auto i = list.begin(); i; i++)
		{
			if (i().getForceId() != -1 && !Force(i().getForceId()).isEnemy(force_id))
				return false;
		}
		return true;
	}

	trgmsg().setPerson(2, 무장_조조);

	trgsound().playBgm(17);
	trgscene().move(Building(Person(무장_조조).소속));
	trgmsg(15742, 무장_조조, 무장_위병);
	trgmsg(15743, 무장_위병, 무장_조조);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(1);
	trgscene().fade(255);
	trgmsg(15744, 무장_조조);
	trgscene().effect(20);
	trgmsg(15745, 무장_조조);
	trgscene().effect(21);
	trgmsg(15746, 무장_무관);
	trgmsg(15747, 무장_위병);
	trgmsg(15748, 무장_병사);
	trgmsg(15749, 무장_조조);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().eventStill(24);
	trgsound().playSfx(603);
	trgmsg(15750);
	trgscene().closeEventStill();

	List<City> cities;
	cities.push_back(도시_양양);
	cities.push_back(도시_강릉);
	cities.push_back(도시_시상);
	cities.push_back(도시_건업);
	for (auto i = cities.begin(); i; i++)
	{
		if (i().getForceId() == -1 || i().getForceId() == Person(무장_조조).getForceId())
			continue;

		Force(Person(무장_조조).getForceId()).unally(i().getForceId());
		Force(Person(무장_조조).getForceId()).setRelations(i().getForceId(), 10);
	}

	return true;
}

/** 한중왕 즉위 */
bool PK_역사이벤트6(bool cond)
{
	if (cond)
	{
		if (Scenario().getStartDayCount() >= daycount(218, 12, 1))
			return false;
		if (180 > Scenario().getElapsedDays())
			return false;
		if (Person(무장_유비).신분 != 신분_군주)
			return false;
		int var0 = Person(무장_유비).getForceId();
		if (Scenario().황제 == -1)
			return false;
		if (!Person(무장_유비).isIdle())
			return false;
		if (!Person(무장_제갈량).isIdle())
			return false;
		if (작위_공 > Force(Person(무장_유비).getForceId()).작위)
			return false;
		if (Person(무장_제갈량).getForceId() != var0)
			return false;
		if (Force(var0).isProtectingTheEmperor())
			return false;
		if (Region(지방_파촉).점령세력 != var0)
			return false;
		return true;
	}

	int var0 = Person(무장_유비).getForceId();

	trgmsg().setPerson(2, 무장_유비);
	trgmsg().setPerson(3, 무장_제갈량);

	trgsound().playBgm(16);
	trgscene().move(Building(Person(무장_유비).소속));
	trgsound().playSfx(601);
	trgmsg(15841, 무장_문관, 무장_유비);
	trgmsg(15842, 무장_유비, 무장_문관);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgscene().effect(20);
	trgmsg(15843, 무장_제갈량, 무장_유비);
	trgsound().playSfx(12);
	trgmsg(15844, 무장_유비, 무장_제갈량);
	trgmsg(15845, 무장_제갈량, 무장_유비);
	trgmsg(15846, 무장_유비, 무장_제갈량);
	trgmsg(15847, 무장_제갈량, 무장_유비);
	if (Person(무장_장비).getForceId() == Person(무장_유비).getForceId() && Person(무장_장비).isIdle())
	{
		trgscene().effect(13);
		trgmsg(15848, 무장_장비, 무장_유비);
		trgscene().effect(20);
		trgmsg(15849, 무장_유비, 무장_장비);
	}
	trgsleep();
	trgmsg(15850, 무장_유비, 무장_제갈량);
	trgsound().playSfx(11);
	trgmsg(15851, 무장_유비, 무장_제갈량);
	trgsound().playBgm(17);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(1);
	trgscene().fade(255);
	trgmsg(15852, 무장_유비);
	trgscene().effect(21);
	trgmsg(15853, 무장_문관);
	trgmsg(15854, 무장_병사);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().eventStill(27);
	trgsound().playSfx(612);
	trgmsg(15855);
	trgscene().closeEventStill();

	Force(var0).setTitle(작위_왕);

	List<City> cities(도시속성_세력, var0);
	for (auto i = cities.begin(); i; i++)
	{
		i().addPublicOrder(15);
		if (i().병력 != 0)
			i().addEnergy(15);
	}

	Person(무장_제갈량).addKouseki(2000);

	List<Person> officers(무장속성_세력, var0);
	officers.remove(무장_유비);
	for (auto i = officers.begin(); i; i++)
		i().addLoyalty(15);

	List<Force> forces;
	forces.init();
	forces.remove(var0);
	forces.remove_all_but(세력속성_외교 + var0, -1);
	// forces.remove_all_but(176 + var0, 75, 연산자_보다작음);
	for (auto i = forces.begin(); i; i++)
	{
		if (i().군주 == 무장_조조 || Person(무장_조조).isCloseWith(i().군주) || i().isProtectingTheEmperor())
			i().addRelations(var0, -15);
	}

	return true;
}

/** 위제 즉위 */
bool PK_역사이벤트7(bool cond)
{
	if (cond)
	{
		if (Scenario().getStartDayCount() > daycount(219, 12, 1))
			return false;
		if (180 > Scenario().getElapsedDays())
			return false;
		if (List<Force>().init(세력속성_국호, 국호_위) != 0)
			return false;
		if (Scenario().황제 == -1)
			return false;
		if (Scenario().황제보호세력 == -1)
			return false;
		int var0 = Scenario().황제보호세력;
		int var1 = Force(var0).군주;
		if (!Person(var1).isIdle())
			return false;
		if (Person(var1).혈연 != Person(무장_조조).혈연)
			return false;
		if (Person(var1) == 무장_조조)
			return false;
		if (Force(var0).작위 != 작위_왕)
			return false;
		if (12 > Force(var0).도시수)
			return false;
		if (City(도시_허창).getForceId() != var0)
			return false;
		if (City(도시_낙양).getForceId() != var0)
			return false;
		if (City(도시_업).getForceId() != var0)
			return false;
		if (City(도시_장안).getForceId() != var0)
			return false;
		List<Person> list(무장속성_신분, 신분_군주);
		if (list.remove_all_but(무장속성_혈연, Person(무장_조조).혈연) != 1)
			return false;
		return true;
	}

	int var0 = Scenario().황제보호세력;
	int var1 = Force(var0).군주;

	trgmsg().setPerson(2, var1);
	trgmsg().setPerson(3, Scenario().황제);

	trgsound().playBgm(20);
	trgscene().move(Building(Person(var1).소속));
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	int var2 = 무장_문관;
	if (Person(무장_화흠).getForceId() == var0)
		var2 = 무장_화흠;
	trgmsg(15873, var2, var1);
	trgmsg(15874, var1, var2);
	trgscene().effect(16);
	trgmsg(15875, var2, var1);
	trgmsg(15876, var1, var2);
	trgscene().effect(17);
	trgmsg(15877, var2, var1);
	if (Force(var0).isPlayer())
	{
		trgchooser().setItems(15879, 15880);
		if (trgchooser().show(15878, var1) != 0)
		{
			trgmsg(15881, var1, var2);
			trgmsg(15882, var2, var1);
			return true;
		}
	}
	trgscene().effect(20);
	trgmsg(15883, var1, var2);
	trgmsg(15882, var2, var1);
	trgscene().fade(0);
	trgsleep(2000);
	trgscene().background(1);
	trgscene().fade(255);
	trgmsg(15884, var2, Scenario().황제);
	trgsound().playSfx(613);
	trgmsg(15885, Scenario().황제, var2);
	trgscene().effect(17);
	trgmsg(15886, var2, Scenario().황제);
	trgmsg(15887, Scenario().황제, var2);
	trgmsg(15888, var2, Scenario().황제);
	trgsound().playSfx(12);
	trgmsg(15889, Scenario().황제);
	trgscene().fade(0);
	trgsleep(2000);
	trgscene().fade(255);
	trgsound().playSfx(11);
	trgmsg(15890, var1);
	trgscene().effect(21);
	trgmsg(15891, 무장_문관);
	trgmsg(15892, 무장_위병);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().eventStill(4);
	trgsound().playSfx(12);
	trgmsg(15893);
	trgscene().closeEventStill();

	trgmgr().setLastRunTime(107, Scenario().getDayCount());

	Scenario().setEmperor(-1);

	Force(var0).setTitle(작위_황제);
	Force(var0).setKokugou(국호_위);

	List<City> cities(도시속성_세력, var0);
	for (auto i = cities.begin(); i; i++) {
		i().addPublicOrder(20);
		if (i().병력 != 0)
			i().addEnergy(20);
	}

	List<Person> officers(무장속성_세력, var0);
	officers.remove(var1);
	for (auto i = officers.begin(); i; i++) {
		if (i().한실 == 한실_중시)
			i().addLoyalty(-20);
		else
			i().addLoyalty(20);
	}

	List<Force> forces;
	forces.init();
	forces.remove(var0);
	forces.remove_all_but(세력속성_외교 + var0, -1);
	// forces.remove_all_but(176 + var0, 75, 연산자_보다작음);
	for (auto i = forces.begin(); i; i++) {
		if (Person(무장_유비).isCloseWith(i().군주) || Person(i().군주).한실 == 한실_중시 || i().작위 == 작위_황제)
			i().addRelations(var0, -50);
	}

	return true;
}

/** 촉제 즉위 */
bool PK_역사이벤트8(bool cond)
{
	if (cond)
	{
		if (Scenario().getStartDayCount() > daycount(220, 12, 1))
			return false;
		if (180 > Scenario().getElapsedDays())
			return false;
		if (Scenario().황제 != -1)
			return false;
		if (!Person(무장_제갈량).isIdle())
			return false;
		if (List<Force>().init(세력속성_국호, 국호_촉) != 0)
			return false;
		// 위제 즉위 이벤트가 발생했다면 90일 이상 지나야함
		if (trgmgr().hasRun(146) && 90 > trgmgr().getElapsedDays(107))
			return false;
		int var0 = City(도시_낙양).getForceId();
		if (var0 == -1)
			return false;
		if (Person(Force(var0).군주).혈연 != Person(무장_조조).혈연)
			return false;
		if (Force(var0).작위 != 작위_황제)
			return false;
		if (8 > Force(var0).도시수)
			return false;
		if (City(도시_업).getForceId() != var0)
			return false;
		int var1 = Region(지방_파촉).점령세력;
		if (var1 == -1)
			return false;
		if (!Person(Force(var1).군주).isCloseWith(무장_유비))
			return false;
		if (Force(var1).작위 != 작위_왕)
			return false;
		if (Person(무장_제갈량).getForceId() != var1)
			return false;
		if (Person(무장_제갈량).신분 == 신분_군주)
			return false;
		if (Person(Force(var0).군주).isCloseWith(Force(var1).군주))
			return false;
		if (!Force(var0).isEnemy(var1))
			return false;
		if (Force(var0).우호도[var1] >= 75)
			return false;
		if (!Person(Force(var1).군주).isIdle())
			return false;
		List<Person> list(무장속성_신분, 신분_군주);
		if (list.remove_all_but(무장속성_혈연, Person(무장_조조).혈연) != 1)
			return false;
		return true;
	}

	int var0 = Region(지방_파촉).점령세력;
	int kunshu_id = Force(var0).군주;

	trgmsg().setPerson(2, kunshu_id);
	trgmsg().setPerson(3, 무장_제갈량);

	trgsound().playBgm(16);
	trgscene().move(Building(Person(kunshu_id).소속));
	trgsound().playSfx(601);
	trgmsg(15894, 무장_문관, kunshu_id);
	trgmsg(15895, kunshu_id, 무장_문관);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgmsg(15896, kunshu_id, 무장_제갈량);
	trgmsg(15897, 무장_제갈량, kunshu_id);
	trgscene().effect(13);
	trgmsg(15898, kunshu_id, 무장_제갈량);
	trgmsg(15899, 무장_제갈량, kunshu_id);
	trgmsg(15900, kunshu_id, 무장_제갈량);
	trgscene().effect(20);
	trgmsg(15901, 무장_제갈량, kunshu_id);
	trgmsg(15902, kunshu_id, 무장_제갈량);
	trgscene().fade(0);
	trgsleep(2000);
	trgscene().fade(255);
	trgscene().effect(16);
	trgmsg(15903, 무장_문관, kunshu_id);
	trgsound().playSfx(12);
	trgmsg(15904, kunshu_id, 무장_문관);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(5);
	trgscene().fade(255);
	trgmsg(15905, kunshu_id, 무장_제갈량);
	trgmsg(15906, 무장_제갈량, kunshu_id);
	trgsound().playSfx(613);
	trgmsg(15907, kunshu_id, 무장_제갈량);
	trgmsg(15908, 무장_제갈량, kunshu_id);
	trgmsg(15909, kunshu_id, 무장_제갈량);
	trgscene().effect(20);
	trgmsg(15910, 무장_제갈량, kunshu_id);
	trgsleep(1500);
	trgmsg(15911, kunshu_id, 무장_제갈량);
	trgsound().playBgm(17);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(1);
	trgscene().fade(255);
	trgsound().playSfx(11);
	trgmsg(15912, kunshu_id);
	trgscene().effect(21);
	trgmsg(15913, 무장_무관);
	trgmsg(15914, 무장_병사);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().eventStill(4);
	trgsound().playSfx(612);
	trgmsg(15915);
	trgscene().closeEventStill();

	Force(var0).setTitle(작위_황제);
	Force(var0).setKokugou(국호_촉);

	List<City> cities(도시속성_세력, var0);
	for (auto i = cities.begin(); i; i++) {
		i().addPublicOrder(30);
		if (i().병력 != 0)
			i().addEnergy(30);
	}

	List<Person> officers(무장속성_세력, var0);
	officers.remove(kunshu_id);
	officers.addLoyalty(30);

	List<Force> forces;
	forces.init();
	forces.remove(var0);
	forces.remove_all_but(세력속성_외교 + var0, -1);
	// forces.remove_all_but(176 + var0, 75, 연산자_보다작음);
	for (auto i = forces.begin(); i; i++) {
		if (i().군주 == 무장_조조 || Person(i().군주).혈연 == Person(무장_조조).혈연 || i().작위 == 작위_황제)
			i().addRelations(var0, -20);
	}

	return true;
}

/** 오, 칭신 */
bool PK_역사이벤트9(bool cond)
{
	if (cond)
	{
		if (Scenario().getStartDayCount() > daycount(221, 12, 1))
			return false;
		if (180 > Scenario().getElapsedDays())
			return false;
		if (Scenario().황제 != -1)
			return false;
		if (3 > List<Force>().init())
			return false;
		// 위제 즉위 이벤트가 발생했다면 180일 이상 지나야함
		if (trgmgr().hasRun(146) && 180 > trgmgr().getElapsedDays(107))
			return false;
		int var0 = City(도시_낙양).getForceId();
		if (var0 == -1)
			return false;
		if (Person(Force(var0).군주).혈연 != Person(무장_조조).혈연)
			return false;
		if (Force(var0).작위 != 작위_황제)
			return false;
		if (8 > Force(var0).도시수)
			return false;
		if (City(도시_업).getForceId() != var0)
			return false;
		int var1 = Province(주_양주).점령세력;
		if (var1 == -1)
			return false;
		if (Person(Force(var1).군주).혈연 != Person(무장_손견).혈연)
			return false;
		if (8 > Force(var1).도시수)
			return false;
		if (작위_공 > Force(var1).작위)
			return false;
		if (40 > Force(var0).우호도[var1])
			return false;
		if (!Person(Force(var1).군주).isIdle())
			return false;
		List<Person> list;
		list.init(무장속성_신분, 신분_군주);
		if (list.remove_all_but(무장속성_혈연, Person(무장_조조).혈연) != 1)
			return false;
		list.init(무장속성_신분, 신분_군주);
		if (list.remove_all_but(무장속성_혈연, Person(무장_손견).혈연) != 1)
			return false;
		return true;
	}

	int var0 = City(도시_낙양).getForceId();
	int var1 = Province(주_양주).점령세력;
	int var2 = 무장_문관;

	if (Person(무장_장소).getForceId() == var1 && Person(무장_장소).isIdle())
	{
		var2 = 무장_장소;
	}
	else
	{
		List<Person> list(무장속성_세력, var1);
		list.remove(Force(var1).군주);
		if (0 < list.remove_all_but(무장속성_유휴, true))
		{
			list.sort(무장속성_능력 + 무장능력_지력, 정렬_내림차순);
			var2 = list[0].getId();
		}
	}

	trgmsg().setPerson(2, Force(var1).군주);
	trgmsg().setPerson(3, var2);
	trgmsg().setPerson(4, Force(var0).군주);
	trgmsg().setForce(0, var0);

	trgsound().playBgm(16);
	trgscene().move(Building(Person(Force(var1).군주).소속));
	trgsound().playSfx(601);
	trgmsg(15944, 무장_문관, Force(var1).군주);
	trgmsg(15945, Force(var1).군주, 무장_문관);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgmsg(15946, Force(var1).군주, var2);
	trgscene().effect(17);
	trgmsg(15947, var2, Force(var1).군주);
	trgsound().playSfx(613);
	trgmsg(15948, Force(var1).군주, var2);
	trgscene().effect(20);
	trgmsg(15949, var2, Force(var1).군주);
	trgmsg(15950, Force(var1).군주, var2);
	trgmsg(15951, var2, Force(var1).군주);
	trgscene().fade(0);
	trgsleep();
	trgsound().playSfx(11);
	trgmsg(15952);
	trgscene().fade(255);
	trgscene().background(1);
	trgmsg(15953, Force(var1).군주);
	trgscene().effect(21);
	trgmsg(15954, 무장_문관);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().eventStill(27);
	trgsound().playSfx(612);
	trgmsg(15955);
	trgscene().closeEventStill();

	trgmgr().setLastRunTime(108, Scenario().getDayCount());

	Force(var1).setTitle(작위_왕);

	List<City> cities(도시속성_세력, var1);
	for (auto i = cities.begin(); i; i++)
	{
		i().addPublicOrder(10);
		if (i().병력 != 0)
			i().addEnergy(10);
	}

	List<Person> officers(무장속성_세력, var1);
	officers.remove(Force(var1).군주);
	for (auto i = officers.begin(); i; i++)
		i().addLoyalty(10);

	Force(var1).addRelations(var0, 20);

	List<Force> forces;
	forces.init();
	forces.remove(var1);
	forces.remove(var0);
	forces.remove_all_but(세력속성_외교 + var1, -1);
	// forces.remove_all_but(176 + var1, 75, 연산자_보다작음);
	for (auto i = forces.begin(); i; i++)
	{
		if (Person(i().군주).isCloseWith(무장_유비) || i().작위 == 작위_황제)
			i().addRelations(var1, -30);
	}
	return true;
}

/** 출사표 */
bool PK_역사이벤트10(bool cond)
{
	if (cond)
	{
		if (!Person(무장_제갈량).isIdle())
			return false;
		if (Person(무장_제갈량).getForceId() == -1)
			return false;
		if (!Person(Force(Person(무장_제갈량).getForceId()).군주).isIdle())
			return false;
		if (30 > Scenario().getElapsedDays())
			return false;
		if (Scenario().황제 != -1)
			return false;
		if (Person(무장_제갈량).신분 == 신분_군주)
			return false;
		if (Person(무장_제갈량).사망예정)
			return false;
		int force_id = Person(무장_제갈량).getForceId();
		if (!Person(Force(force_id).군주).isCloseWith(무장_유비))
			return false;
		if (Force(force_id).작위 != 작위_황제)
			return false;
		if (95 > City(도시_성도).치안)
			return false;
		if (95 > City(도시_한중).치안)
			return false;
		if (Region(지방_파촉).점령세력 != force_id)
			return false;
		if (Region(지방_남만).점령세력 != force_id)
			return false;
		int var0 = City(도시_낙양).getForceId();
		if (var0 == -1)
			return false;
		if (var0 == force_id)
			return false;
		if (Force(var0).작위 != 작위_황제)
			return false;
		if (Force(Person(무장_제갈량).getForceId()).도시수 >= Force(var0).도시수)
			return false;
		if (City(도시_허창).getForceId() != var0)
			return false;
		if (City(도시_업).getForceId() != var0)
			return false;
		if (!Force(force_id).isEnemy(var0))
			return false;
		if (Person(Force(force_id).군주).isCloseWith(Force(var0).군주))
			return false;
		if (Force(force_id).우호도[var0] >= 75)
			return false;
		return true;
	}

	int force_id = Person(무장_제갈량).getForceId();
	int var0 = City(도시_낙양).getForceId();

	trgmsg().setPerson(2, 무장_제갈량);
	trgmsg().setForce(0, var0);

	trgsound().playBgm(16);
	trgscene().move(Building(Person(무장_제갈량).소속));
	trgmsg(15985, 무장_제갈량, 무장_무관);
	trgmsg(15986, 무장_무관, 무장_제갈량);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(1);
	trgscene().fade(255);
	trgmsg(15987, Force(force_id).군주, 무장_제갈량);
	trgscene().effect(14);
	trgmsg(15988, 무장_제갈량, Force(force_id).군주);
	trgmsg(15989, Force(force_id).군주, 무장_제갈량);
	trgscene().effect(10);
	trgmsg(15990, 무장_제갈량, Force(force_id).군주);
	trgscene().fade(0);
	trgsleep(2000);
	trgscene().fade(255);
	trgmsg(15991, 무장_제갈량, Force(force_id).군주);
	trgmsg(15992, Force(force_id).군주, 무장_제갈량);
	trgmsg(15993, 무장_제갈량, Force(force_id).군주);
	trgmsg(15994, Force(force_id).군주, 무장_제갈량);
	trgsound().playBgm(17);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgmsg(15995, 무장_제갈량);
	if (Person(무장_조운).getForceId() == force_id && Person(무장_조운).isIdle())
	{
		trgscene().effect(20);
		trgmsg(15996, 무장_조운, 무장_제갈량);
	}
	trgmsg(15997, 무장_제갈량);
	trgscene().effect(21);
	trgmsg(15998, 무장_무관);
	trgmsg(15999, 무장_병사);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().eventStill(24);
	trgsound().playSfx(603);
	trgmsg(16000);
	trgscene().closeEventStill();

	Force(force_id).setRelations(var0, 0);
	Force(force_id).unally(var0);

	List<Person> officers(무장속성_세력, force_id);
	officers.remove(Force(force_id).군주);
	officers.addLoyalty(10);

	return true;
}

/** 오제 즉위 */
bool PK_역사이벤트11(bool cond)
{
	if (cond)
	{
		if (Scenario().getStartDayCount() > daycount(228, 12, 1))
			return false;
		if (180 > Scenario().getElapsedDays())
			return false;
		if (Scenario().황제 != -1)
			return false;
		if (List<Force>().init(세력속성_국호, 국호_오) != 0)
			return false;
		if (trgmgr().hasRun(149) && 360 > trgmgr().getElapsedDays(108))
			return false;
		if (List<Force>().init(세력속성_작위, 작위_황제) < 2)
			return false;
		int var0 = Province(주_양주).점령세력;
		if (var0 == -1)
			return false;
		if (Person(Force(var0).군주).혈연 != Person(무장_손견).혈연)
			return false;
		if (Force(var0).작위 != 작위_왕)
			return false;
		if (8 > Force(var0).도시수)
			return false;
		if (!Person(Force(var0).군주).isIdle())
			return false;
		List<Person> officers(무장속성_신분, 신분_군주);
		if (officers.remove_all_but(무장속성_혈연, Person(무장_손견).혈연) != 1)
			return false;
		return true;
	}

	int var0 = Province(주_양주).점령세력;
	int var1 = 무장_문관;

	if (Person(무장_장소).getForceId() == var0 && Person(무장_장소).isIdle())
	{
		var1 = 무장_장소;
	}
	else
	{
		List<Person> officers(무장속성_세력, var0);
		officers.remove(Force(var0).군주);
		if (0 < officers.remove_all_but(무장속성_유휴, true))
		{
			officers.sort(무장속성_능력 + 무장능력_지력, 정렬_내림차순);
			var1 = officers[0].getId();
		}
	}

	trgmsg().setPerson(2, Force(var0).군주);
	trgmsg().setPerson(3, var1);

	trgsound().playBgm(16);
	trgscene().move(Building(Person(Force(var0).군주).소속));
	trgsound().playSfx(601);
	trgmsg(16001, 무장_문관, Force(var0).군주);
	trgmsg(16002, Force(var0).군주, 무장_문관);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgscene().effect(17);
	trgmsg(16003, var1, Force(var0).군주);
	trgmsg(16004, Force(var0).군주, var1);
	trgmsg(16005, var1, Force(var0).군주);
	trgscene().effect(20);
	trgmsg(16006, Force(var0).군주, var1);
	trgscene().fade(0);
	trgscene().background(1);
	trgscene().fade(255);
	trgsound().playSfx(11);
	trgmsg(16007, Force(var0).군주);
	trgscene().effect(21);
	trgmsg(16008, 무장_무관);
	trgmsg(16009, 무장_문관);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().eventStill(4);
	trgsound().playSfx(612);
	trgmsg(16010);
	trgscene().closeEventStill();

	Force(var0).setTitle(작위_황제);
	Force(var0).setKokugou(국호_오);

	List<City> cities(도시속성_세력, var0);
	for (auto i = cities.begin(); i; i++)
	{
		i().addPublicOrder(20);
		if (i().병력 != 0)
			i().addEnergy(20);
	}

	List<Person> officers(무장속성_세력, var0);
	officers.remove(Force(var0).군주);
	officers.addLoyalty(20);

	List<Force> forces;
	forces.init();
	forces.remove(var0);
	forces.remove_all_but(세력속성_외교 + var0, -1);
	// forces.remove_all_but(176 + var0, 75, 연산자_보다작음);
	for (auto i = forces.begin(); i; i++)
	{
		if (i().작위 == 작위_황제)
			i().addRelations(var0, -50);
	}

	return true;
}

/** 장안 천도 */
bool PK_역사이벤트12(bool cond)
{
	if (cond)
	{
		if (Scenario().getStartDayCount() > daycount(190, 1, 1))
			return false;
		if (Person(무장_동탁).신분 != 신분_군주)
			return false;
		if (Person(무장_조조).신분 != 신분_군주)
			return false;
		if (Person(무장_원소).신분 != 신분_군주)
			return false;
		int var0 = Person(무장_동탁).getForceId();
		if (daycount(190, 4, 1) > Scenario().getDayCount() && Building(건물_호로관).getForceId() == var0)
			return false;
		if (Scenario().황제 == -1)
			return false;
		if (Person(Scenario().황제).소속 == 건물_장안)
			return false;
		if (!Force(var0).isProtectingTheEmperor())
			return false;
		if (City(도시_낙양).getForceId() != var0)
			return false;
		if (City(도시_장안).getForceId() != var0)
			return false;
		if (Person(무장_이유).getForceId() != var0)
			return false;
		if (Person(무장_동탁).소속 != 건물_낙양)
			return false;
		if (Force(Person(무장_조조).getForceId()).isEnemy(Person(무장_원소).getForceId()))
			return false;
		if (!Force(var0).isEnemy(Person(무장_조조).getForceId()))
			return false;
		if (!Force(var0).isEnemy(Person(무장_원소).getForceId()))
			return false;
		if (Force(var0).우호도[Person(무장_조조).getForceId()] >= 40)
			return false;
		if (Force(var0).우호도[Person(무장_원소).getForceId()] >= 40)
			return false;
		if (Person(무장_동탁).isCloseWith(무장_조조))
			return false;
		if (Person(무장_동탁).isCloseWith(무장_원소))
			return false;
		if (!Person(무장_동탁).isIdle())
			return false;
		if (!Person(무장_이유).isIdle())
			return false;
		return true;
	}

	int var0 = Person(무장_동탁).getForceId();
	int var1 = 무장_문관;
	if (Person(무장_왕윤).군주 == 무장_동탁 && Person(무장_왕윤).isIdle())
		var1 = 무장_왕윤;
	int var2 = 무장_무관;
	if (Person(무장_여포).군주 == 무장_동탁 && Person(무장_여포).isIdle())
		var2 = 무장_여포;

	trgmsg().setPerson(2, 무장_동탁);
	trgmsg().setCity(0, 도시_낙양);
	trgmsg().setCity(1, 도시_장안);

	trgsound().playBgm(20);
	trgscene().move(Building(Person(무장_동탁).소속), 1000);
	trgmsg(18282);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(1);
	trgscene().fade(255);
	trgmsg(18283, 무장_동탁, 무장_이유);
	trgscene().eventStill(21);
	trgmsg(18284, 무장_이유, 무장_동탁);
	trgmsg(18285, 무장_동탁, 무장_이유);
	trgmsg(18286, 무장_이유, 무장_동탁);
	trgsound().playSfx(11);
	trgmsg(18287, 무장_동탁, 무장_이유);
	trgscene().closeEventStill();
	trgscene().effect(13);
	trgmsg(18288, var1, 무장_동탁);
	if (Force(var0).isPlayer())
	{
		trgchooser().setItems(18290, 18291);
		if (trgchooser().show(18289, 무장_동탁) != 0)
		{
			trgmsg(18292, 무장_동탁, var1);
			return true;
		}
	}
	trgscene().effect(20);
	trgmsg(18293, 무장_동탁, var1);
	trgmsg(18294, var1, 무장_동탁);
	if (var2 == 무장_여포)
		trgmsg(18295, 무장_동탁, var2);
	else
		trgmsg(18296, 무장_동탁, var2);
	trgsound().playSfx(610);
	trgscene().eventStill(21);
	trgmsg(18297, var2, 무장_동탁);
	trgmsg(18298, 무장_동탁, var2);
	trgmsg(18299, var2, 무장_동탁);
	trgscene().closeEventStill();
	trgscene().fade(0);
	trgsleep(2000);
	trgscene().fade(255);
	trgmsg(18300, 무장_동탁, var2);
	trgmsg(18301, var2, 무장_동탁);
	trgmsg(18302, 무장_동탁, var2);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgsound().playSfx(332);
	trgsound().playSfx(332);
	trgsound().playSfx(332);
	trgsound().playSfx(332);
	trgsound().playSfx(332);
	trgmsg(18303, Scenario().황제);
	trgmsg(18304, 무장_동탁);
	trgscene().fade(255);
	trgscene().eventStill(3);
	trgsound().playSfx(603);
	trgmsg(18305);
	trgscene().closeEventStill();

	Person(무장_영제).move(건물_장안);
	Person(무장_영제).setLocationByBuildingId(건물_장안);
	Person(무장_소제).move(건물_장안);
	Person(무장_소제).setLocationByBuildingId(건물_장안);
	Person(무장_헌제).move(건물_장안);
	Person(무장_헌제).setLocationByBuildingId(건물_장안);

	List<Person> officers;

	officers.init(무장속성_세력, var0);
	officers.remove_all_but(무장속성_소속, 건물_낙양);
	officers.move(건물_장안);
	officers.init(무장속성_세력, var0);
	officers.remove_all_but(무장속성_소속, 건물_호로관);
	officers.move(건물_장안);
	officers.init(무장속성_세력, var0);
	officers.remove_all_but(무장속성_소속, 건물_맹진항);
	officers.move(건물_장안);
	officers.init(무장속성_세력, var0);
	officers.remove_all_but(무장속성_소속, 건물_해현항);
	officers.move(건물_장안);

	officers.init(무장속성_세력, var0);
	officers.remove(Force(var0).군주);
	for (auto i = officers.begin(); i; i++)
	{
		if (i().한실 == 한실_중시)
			i().addLoyalty(-10 - (2 * i().의리));
	}

	List<Building> buildings;
	buildings.push_back(건물_낙양);
	buildings.push_back(건물_호로관);
	buildings.push_back(건물_맹진항);
	buildings.push_back(건물_해현항);
	buildings.remove_all_but(건물속성_세력, var0);
	for (auto i = buildings.begin(); i; i++)
	{
		Building(건물_장안).addGold(i().금);
		Building(건물_장안).addFood(i().병량);
		Building(건물_장안).addTroops(i().병력);
		Building(건물_장안).addWeapons(병기_창, i().병기[병기_창]);
		Building(건물_장안).addWeapons(병기_극, i().병기[병기_극]);
		Building(건물_장안).addWeapons(병기_노, i().병기[병기_노]);
		Building(건물_장안).addWeapons(병기_군마, i().병기[병기_군마]);
		Building(건물_장안).addWeapons(병기_충차, i().병기[병기_충차]);
		Building(건물_장안).addWeapons(병기_정란, i().병기[병기_정란]);
		Building(건물_장안).addWeapons(병기_투석, i().병기[병기_투석]);
		Building(건물_장안).addWeapons(병기_목수, i().병기[병기_목수]);
		Building(건물_장안).addWeapons(병기_누선, i().병기[병기_누선]);
		i().setGold(0);
		i().setFood(0);
		i().setHP(0);
		i().setTroops(0);
		i().setEnergy(0);
		i().setWeapons(병기_창, 0);
		i().setWeapons(병기_극, 0);
		i().setWeapons(병기_노, 0);
		i().setWeapons(병기_군마, 0);
		i().setWeapons(병기_충차, 0);
		i().setWeapons(병기_정란, 0);
		i().setWeapons(병기_투석, 0);
		i().setWeapons(병기_목수, 0);
		i().setWeapons(병기_누선, 0);
	}

	City(도시_낙양).setPublicOrder(0);
	City(도시_낙양).resetWeapons();

	for (auto i = buildings.begin(); i; i++)
		i().neutralize();

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/*
	trgmap().removeBuilding(71, 73);
	trgmap().removeBuilding(71, 74);
	trgmap().removeBuilding(72, 73);
	trgmap().removeBuilding(72, 74);
	trgmap().removeBuilding(72, 75);
	trgmap().removeBuilding(73, 72);
	trgmap().removeBuilding(73, 73);
	trgmap().removeBuilding(73, 74);
	trgmap().removeBuilding(74, 79);
	trgmap().removeBuilding(74, 80);
	trgmap().removeBuilding(75, 79);
	trgmap().removeBuilding(75, 80);
	trgmap().removeBuilding(76, 80);
	trgmap().removeBuilding(76, 81);
	trgmap().removeBuilding(83, 70);
	trgmap().removeBuilding(83, 71);
	trgmap().removeBuilding(84, 70);
	trgmap().removeBuilding(84, 71);
	trgmap().removeBuilding(84, 72);
	trgmap().removeBuilding(85, 70);
	trgmap().removeBuilding(85, 71);
	trgmap().removeBuilding(85, 72);
	*/

	City city(도시_낙양);
	for (int i = 0; i < city.개발지수; i++)
	{
		Building building(city.개발지[i].building);
		if (isalive(building))
			trgmap().removeBuilding(building.getId());
	}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	Building(건물_장안).addGold(30000);

	trgscene().fade(0);
	trgsleep();
	trgmap().refresh();
	trgscene().fade(255);

	return true;
}

/** 반동탁 연합 붕괴 */
bool PK_역사이벤트13(bool cond)
{
	if (cond)
	{
		if (Scenario().번호 != 1)
			return false;
		if (Person(무장_동탁).신분 != 신분_군주)
			return false;
		if (Person(무장_조조).신분 != 신분_군주)
			return false;
		if (Person(무장_원소).신분 != 신분_군주)
			return false;
		int var0 = Person(무장_동탁).getForceId();
		if (daycount(191, 1, 1) > Scenario().getDayCount())
			return false;
		if (!Force(var0).isProtectingTheEmperor())
			return false;
		if (2 > Force(var0).도시수)
			return false;
		if (Force(Person(무장_조조).getForceId()).isEnemy(Person(무장_원소).getForceId()))
			return false;
		if (!Force(var0).isEnemy(Person(무장_조조).getForceId()))
			return false;
		if (!Force(var0).isEnemy(Person(무장_원소).getForceId()))
			return false;
		if (Person(무장_동탁).isCloseWith(무장_조조))
			return false;
		if (Person(무장_동탁).isCloseWith(무장_원소))
			return false;
		if (!Person(무장_동탁).isIdle())
			return false;
		return true;
	}

	int var0 = Person(무장_동탁).getForceId();

	trgmsg().setPerson(2, 무장_동탁);

	trgsound().playBgm(16);
	trgscene().move(Building(Person(무장_동탁).소속));
	trgmsg(18306);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(1);
	trgscene().fade(255);
	trgscene().effect(18);
	trgmsg(18307, 무장_사자, 무장_동탁);
	trgmsg(18308, 무장_동탁, 무장_사자);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1, 0);
	trgscene().fade(255);
	trgscene().eventStill(8);
	trgsound().playSfx(603);
	trgmsg(18309);
	trgscene().closeEventStill();

	List<Person> officers;
	officers.push_back(무장_조조);
	officers.push_back(무장_유비);
	officers.push_back(무장_손견);
	officers.push_back(무장_마등);
	officers.push_back(무장_원소);
	officers.push_back(무장_원술);
	officers.push_back(무장_공손찬);
	officers.push_back(무장_한복);
	officers.push_back(무장_공융);
	officers.push_back(무장_유대);
	officers.push_back(무장_도겸);
	officers.push_back(무장_공주);
	officers.push_back(무장_장양);
	officers.remove_all_but(무장속성_신분, 신분_군주);
	for (auto i = officers.begin(); i; i++)
	{
		for (auto j = i; ++j; true)
			Force(i().getForceId()).addRelations(j().getForceId(), -40);
	}
	return true;
}

/** 조숭 참살 */
bool PK_역사이벤트14(bool cond)
{
	if (cond)
	{
		int var0 = Person(무장_조조).getForceId();
		if (Scenario().getDayCount() > daycount(194, 12, 1))
			return false;
		if (180 > Scenario().getElapsedDays())
			return false;
		if (City(도시_진류).getForceId() != var0)
			return false;
		if (City(도시_복양).getForceId() != var0)
			return false;
		if (Force(var0).도시수 > 4)
			return false;
		if (Force(Person(무장_도겸).getForceId()).isPlayer())
			return false;
		if (City(도시_하비).getForceId() != Person(무장_도겸).getForceId())
			return false;
		if (!Force(var0).isEnemy(Person(무장_도겸).getForceId()))
			return false;
		if (Force(var0).우호도[Person(무장_도겸).getForceId()] > 61)
			return false;
		if (Person(무장_조조).isCloseWith(무장_도겸))
			return false;
		if (!Person(무장_조조).isIdle())
			return false;
		return true;
	}

	int var0 = Person(무장_조조).getForceId();
	int var1 = 무장_무관;
	if (Person(무장_하후돈).군주 == 무장_조조 && Person(무장_하후돈).isIdle())
		var1 = 무장_하후돈;

	trgmsg().setPerson(2, 무장_조조);
	trgmsg().setPerson(3, 무장_도겸);
	trgmsg().setCity(0, 도시_진류);
	trgmsg().setCity(1, 도시_복양);

	trgsound().playBgm(18);
	trgscene().move(Building(Person(무장_조조).소속), 1200);
	trgmsg(18388);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgmsg(18389, 무장_조조, var1);
	trgmsg(18390, var1, 무장_조조);
	if (var1 == 무장_하후돈)
		trgmsg(18391, 무장_조조, var1);
	else
		trgmsg(18392, 무장_조조, var1);
	trgmsg(18393, var1, 무장_조조);
	if (var1 == 무장_하후돈)
		trgmsg(18394, 무장_조조, var1);
	else
		trgmsg(18395, 무장_조조, var1);
	trgscene().fade(0);
	trgsleep(2000);
	trgscene().background(2);
	trgscene().fade(255);
	trgsound().playBgm(21);
	trgscene().effect(18);
	trgmsg(18396, 무장_사자, 무장_조조);
	trgmsg(18397, 무장_조조, 무장_사자);
	trgmsg(18398, 무장_사자, 무장_조조);
	trgscene().effect(13);
	trgmsg(18399, 무장_조조, 무장_사자);
	trgscene().effect(20);
	trgmsg(18400, 무장_조조, 무장_사자);
	trgscene().eventStill(21);
	trgmsg(18401, 무장_사자, 무장_조조);
	trgmsg(18402, 무장_조조, 무장_사자);
	trgscene().closeEventStill();
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgscene().fade(255);
	trgscene().eventStill(8);
	trgsound().playSfx(603);
	trgmsg(18403);
	trgscene().closeEventStill();

	Force(var0).setRelations(Person(무장_도겸).getForceId(), 0);
	Force(var0).unally(Person(무장_도겸).getForceId());

	Person(무장_조조).resetRelationship(무장_도겸);

	List<Building> buildings(건물속성_세력, var0);
	for (auto i = buildings.begin(); i; i++)
	{
		if (i().병력 != 0)
			i().addEnergy(10);
	}

	List<Unit> units(부대속성_세력, var0);
	for (auto i = units.begin(); i; i++)
	{
		if (i().병력 != 0)
			i().addEnergy(10);
	}

	if (Person(무장_장개).getForceId() == Person(무장_도겸).getForceId() && Person(무장_장개).신분 == 신분_일반 && Person(무장_장개).isIdle())
		Person(무장_장개).banish();

	return true;
}

/*
bool PK_역사이벤트15(bool cond)
{
}

bool PK_역사이벤트16(bool cond)
{
}

bool PK_역사이벤트17(bool cond)
{
}

bool PK_역사이벤트18(bool cond)
{
}

bool PK_역사이벤트19(bool cond)
{
}

bool PK_역사이벤트20(bool cond)
{
}

bool PK_역사이벤트21(bool cond)
{
}
*/

/** 도원결의 */
bool PK_역사이벤트22(bool cond)
{
	if (cond)
	{
		int force_id = trgevent().getPerson().getForceId();
		if (Person(무장_유비).getForceId() != force_id)
			return false;
		if (Person(무장_관우).getForceId() != force_id)
			return false;
		if (Person(무장_장비).getForceId() != force_id)
			return false;
		if (Scenario().번호 != 0)
			return false;
		if (Scenario().getElapsedDays() != 0)
			return false;
		if (!Person(무장_유비).isIdle())
			return false;
		if (!Person(무장_관우).isIdle())
			return false;
		if (!Person(무장_장비).isIdle())
			return false;
		return true;
	}

	int var0;

	trgmsg().setPerson(2, 무장_유언);
	trgmsg().setCity(0, 도시_계);

	trgsound().playBgm(18);
	trgscene().move(Building(Person(무장_유비).소속), 1500);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(4);
	trgscene().fade(255);
	var0 = trgsound().playSfxLoop(615);
	trgmsg(15115);
	trgmsg(15116, 무장_유비, 무장_장비);
	trgscene().effect(13);
	trgmsg(15117, 무장_장비, 무장_유비, 15093);
	trgmsg(15118, 무장_유비, 무장_장비);
	trgsound().playSfx(610);
	trgmsg(15119, 무장_장비, 무장_유비);
	trgmsg(15120, 무장_유비, 무장_장비);
	trgmsg(15121, 무장_장비, 무장_유비);
	trgmsg(15122, 무장_유비, 무장_장비);
	trgscene().fade(0);
	trgsleep(2000);
	trgscene().fade(255);
	trgmsg(15123, 무장_장비, 무장_유비);
	trgscene().effect(18);
	trgmsg(15124, 무장_관우, 무장_유비, 15093);
	trgmsg(15125, 무장_장비, 무장_관우);
	trgmsg(15126, 무장_관우, 무장_장비, 15093);
	trgmsg(15127, 무장_유비, 무장_관우);
	trgscene().effect(20);
	trgmsg(15128, 무장_관우, 무장_장비);
	trgmsg(15129, 무장_장비, 무장_관우);
	trgsound().stopSfxLoop(var0);
	trgscene().fade(0);
	trgsound().playBgm(17);
	trgsleep(2000);
	var0 = trgsound().playSfxLoop(608);
	trgscene().background(0);
	trgscene().fade(255);
	trgmsg(15130, 무장_유비, 무장_관우);
	trgsound().playSfx(606);
	trgsleep(1200);
	trgmsg(15131, 무장_관우, 무장_장비);
	trgsound().playSfx(606);
	trgsleep(1200);
	trgmsg(15132, 무장_장비, 무장_관우);
	trgsound().playSfx(606);
	trgsound().stopSfxLoop(var0);
	trgsleep(1200);
	trgscene().effect(0);
	trgmsg(15133);

	return true;
}

/*
bool PK_역사이벤트23(bool cond)
{
}

bool PK_역사이벤트24(bool cond)
{
}

bool PK_역사이벤트25(bool cond)
{
}

bool PK_역사이벤트26(bool cond)
{
}

bool PK_역사이벤트27(bool cond)
{
}

bool PK_역사이벤트28(bool cond)
{
}

bool PK_역사이벤트29(bool cond)
{
}

bool PK_역사이벤트30(bool cond)
{
}

bool PK_역사이벤트31(bool cond)
{
}

bool PK_역사이벤트32(bool cond)
{
}

bool PK_역사이벤트33(bool cond)
{
}

bool PK_역사이벤트34(bool cond)
{
}

bool PK_역사이벤트35(bool cond)
{
}

bool PK_역사이벤트36(bool cond)
{
}

bool PK_역사이벤트37(bool cond)
{
}

bool PK_역사이벤트38(bool cond)
{
}

bool PK_역사이벤트39(bool cond)
{
}

bool PK_역사이벤트40(bool cond)
{
}

bool PK_역사이벤트41(bool cond)
{
}

bool PK_역사이벤트42(bool cond)
{
}

bool PK_역사이벤트43(bool cond)
{
}

bool PK_역사이벤트44(bool cond)
{
}

bool PK_역사이벤트45(bool cond)
{
}

bool PK_역사이벤트46(bool cond)
{
}

bool PK_역사이벤트47(bool cond)
{
}

bool PK_역사이벤트48(bool cond)
{
}

bool PK_역사이벤트49(bool cond)
{
}

bool PK_역사이벤트50(bool cond)
{
}

bool PK_역사이벤트63(bool cond)
{
}

bool PK_역사이벤트64(bool cond)
{
}

bool PK_역사이벤트65(bool cond)
{
}

bool PK_역사이벤트66(bool cond)
{
}

bool PK_역사이벤트67(bool cond)
{
}

bool PK_역사이벤트68(bool cond)
{
}

bool PK_역사이벤트69(bool cond)
{
}

bool PK_역사이벤트70(bool cond)
{
}

bool PK_역사이벤트71(bool cond)
{
}

bool PK_역사이벤트72(bool cond)
{
}

bool PK_역사이벤트73(bool cond)
{
}

bool PK_역사이벤트74(bool cond)
{
}

bool PK_역사이벤트75(bool cond)
{
}

bool PK_역사이벤트78(bool cond)
{
}

bool PK_역사이벤트79(bool cond)
{
}

bool PK_역사이벤트80(bool cond)
{
}

bool PK_역사이벤트85(bool cond)
{
}

bool PK_역사이벤트86(bool cond)
{
}
*/