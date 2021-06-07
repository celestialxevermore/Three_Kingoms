/** 오호대장군 */
bool PK_범용이벤트52(bool cond)
{
	if (cond)
	{
		if (180 > Scenario().getElapsedDays())
			return false;
		int month = Scenario().월;
		if (month != 1 && month != 4 && month != 7 && month != 12)
			return false;
		if (!trgevent().getPerson().isIdle())
			return false;
		if (Force(trgevent().getPerson().getForceId()).군사 == -1)
			return false;
		if (!Person(Force(trgevent().getPerson().getForceId()).군사).isIdle())
			return false;
		if (Force(trgevent().getPerson().getForceId()).작위 > 작위_공)
			return false;
		if (10 > Force(trgevent().getPerson().getForceId()).도시수)
			return false;
		trglist<Person>()(0).init(무장속성_세력, trgevent().getPerson().getForceId(), 연산자_같음);
		trglist<Person>()(0).remove(trgevent().getPerson());
		trglist<Person>()(0).remove(Force(trgevent().getPerson().getForceId()).군사);
		trglist<Person>()(0).remove_all_but(무장속성_능력 + 무장능력_무력, 90, 연산자_크거나같음);
		trglist<Person>()(0).remove_all_but(무장속성_공적, 20000, 연산자_크거나같음);
		trglist<Person>()(0).remove_all_but(무장속성_충성도, 100, 연산자_크거나같음);
		if (5 > trglist<Person>()(0).size())
			return false;
		return true;
	}

	trglist<Person>()(0).sort(무장속성_공적, 정렬_내림차순);

	trgmsg().setPerson(2, trgevent().getPerson());
	trgmsg().setPerson(3, Force(trgevent().getPerson().getForceId()).군사);
	trgsound().playBgm(17);
	trgscene().move(Building(trgevent().getPerson().소속));
	trgsound().playSfx(601);
	trgmsg(16030, 무장_문관);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgmsg(16031, trgevent().getPerson(), Force(trgevent().getPerson().getForceId()).군사);
	trgscene().effect(16);
	trgmsg(16032, Force(trgevent().getPerson().getForceId()).군사, trgevent().getPerson());
	trgsound().playSfx(11);
	trgmsg(16033, trgevent().getPerson(), Force(trgevent().getPerson().getForceId()).군사);
	trgscene().effect(14);
	trgmsg(16034, Force(trgevent().getPerson().getForceId()).군사, trgevent().getPerson());
	trglist<Person>()(0).select(trglist<Person>()(0), 5, 5, 16035, false);
	trgmsg().setPerson(2, trglist<Person>()(0)[0]);
	trgmsg().setPerson(3, trglist<Person>()(0)[1]);
	trgmsg().setPerson(4, trglist<Person>()(0)[2]);
	trgmsg().setPerson(5, trglist<Person>()(0)[3]);
	trgmsg().setPerson(6, trglist<Person>()(0)[4]);
	trgmsg(16036, Force(trgevent().getPerson().getForceId()).군사, trgevent().getPerson());
	trgmsg(16037, trgevent().getPerson(), Force(trgevent().getPerson().getForceId()).군사);
	trgmsg(16038, Force(trgevent().getPerson().getForceId()).군사, trgevent().getPerson());
	trgscene().fade(0);
	trgsleep();
	trgscene().background(1);
	trgscene().fade(255);
	trgscene().effect(11);
	trgmsg(16039, trgevent().getPerson());
	for (auto i = trglist<Person>()(0).begin(); i; i++)
	{
		if (i().isIdle() && i().소속 == trgevent().getPerson().소속)
			trgmsg(16040, i());
	}
	trgscene().effect(21);
	trgmsg(16041);
	trgsound().playSfx(612);
	trgmsg(16042);

	for (auto i = trglist<Person>()(0).begin(); i; i++)
	{
		if (i().충성도 < 150)
			i().setLoyalty(150);
		i().addKouseki(2000);
		i().addWeaponExp(병기_창, 50);
		i().addWeaponExp(병기_극, 50);
		i().addWeaponExp(병기_노, 50);
		i().addWeaponExp(병기_군마, 50);
		i().addStatExp(무장능력_통솔, 50);
		i().addStatExp(무장능력_무력, 50);
	}

	return true;
}

/** 동작 */
bool PK_범용이벤트53(bool cond)
{
	if (cond)
	{
		if (!trgevent().getPerson().isIdle())
			return false;
		if (360 > Scenario().getElapsedDays())
			return false;
		int force_id = trgevent().getPerson().getForceId();
		if (City(도시_업).getForceId() != force_id)
			return false;
		if (trgevent().getPerson().소속 != 건물_업)
			return false;
		if (Force(force_id).작위 > 작위_대장군)
			return false;
		if (10 > Force(force_id).도시수)
			return false;
		if (Item(보물_동작).상태 != 보물상태_미등장)
			return false;
		return true;
	}

	trgmsg().setCity(0, 도시_업);
	trgsound().playBgm(17);
	trgscene().move(Building(trgevent().getPerson().소속), 1200);
	trgsound().playSfx(601, 100);
	trgmsg(16043, 무장_문관, trgevent().getPerson());
	trgmsg(16044, trgevent().getPerson());
	trgscene().fade(0);
	trgsleep(1000);
	trgscene().background(4);
	trgscene().fade(255);
	int var0 = trgsound().playSfxLoop(615);
	trgmsg(16045, trgevent().getPerson());
	trgmsg(16046, 무장_위병);
	trgscene().fade(0);
	trgsleep(1000);
	trgscene().fade(255);
	trgscene().effect(18);
	trgmsg(16047, 무장_위병);
	trgmsg(16048, trgevent().getPerson());
	trgmsg(16049, 무장_위병);
	trgsound().playSfx(11, 100);
	trgmsg(16050, trgevent().getPerson());
	trgmsg().setItem(0, 보물_동작);
	trgmsg(16051, 무장_문관);
	trgsound().stopSfxLoop(var0);
	trgsound().playSfx(612, 100);
	trgmsg(16052, trgevent().getPerson());

	Item(보물_동작).상태 = 보물상태_등장;
	Item(보물_동작).소유무장 = trgevent().getPerson().getId();

	return true;
}

/** 문관 수배 */
bool PK_범용이벤트54(bool cond)
{
	if (cond)
	{
		if (!trgevent().getPerson().isIdle())
			return false;

		if (!randbool(5))
			return false;

		if (180 > Scenario().getElapsedDays())
			return false;

		trglist<Person>()(0).init(무장속성_세력, trgevent().getPerson().getForceId());
		trglist<Person>()(0).remove_all_but(무장속성_소속, trgevent().getPerson().소속);
		trglist<Person>()(0).remove(trgevent().getPerson());
		trglist<Person>()(0).remove_all_but(무장속성_충성도, 90, 연산자_크거나같음);
		trglist<Person>()(0).remove_all_but(무장속성_능력 + 무장능력_정치, 80, 연산자_크거나같음);
		trglist<Person>()(0).remove_all_but(무장속성_유휴, true);
		if (trglist<Person>()(0).size() <= 0)
			return false;

		trglist<Person>()(1).clear();
		trglist<Person>()(2).init(무장속성_재야, true);
		trglist<Person>()(2).remove_all_but(무장속성_유휴, true);
		trglist<Person>()(2).remove_all_but(무장속성_친밀, false, trgevent().getPerson().getId());
		trglist<Person>()(2).remove_all_but(무장속성_배우자, -1);
		trglist<Person>()(2).remove_all_but(무장속성_의형제, -1);

		for (auto i = trglist<Person>()(2).begin(); i; i++)
		{
			if (i().무력 >= i().지력 && i().무력 >= i().정치)
				continue;

			for (auto j = trglist<Person>()(0).begin(); j; j++)
			{
				if (j().isGikyoudai(i().getId()) || j().출신 == i().출신 || j().혈연 == i().혈연 || j().isLike(i().getId()))
				{
					trglist<Person>()(1).push_back(i());
					break;
				}
			}
		}

		return 0 < trglist<Person>()(1).size();
	}

	Person var0 = trglist<Person>()(1).random();
	Person var1 = trglist<Person>()(0).random();

	trglist<Person>()(2).clear();

	for (auto i = trglist<Person>()(0).begin(); i; i++)
	{
		if (i().isGikyoudai(var0.getId()) || i().출신 == var0.출신 || i().혈연 == var0.혈연 || i().isLike(var0.getId()) || var0.isLike(i().getId()))
			trglist<Person>()(2).push_back(var1);
	}

	if (0 >= trglist<Person>()(2).size())
		assert(false);
	else
		var1 = trglist<Person>()(2).random();

	trgmsg().setPerson(2, trgevent().getPerson());
	trgmsg().setPerson(3, var1);
	trgsound().playBgm(18);
	trgscene().move(Building(trgevent().getPerson().소속));
	trgsound().playSfx(601);
	trgmsg(16053, 무장_문관);
	trgmsg(16054, trgevent().getPerson());
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgmsg().setPerson(2, var0);
	trgmsg().setPerson(3, var1);
	trgmsg().setPerson(4, trgevent().getPerson());
	trgmsg(16055, trgevent().getPerson(), var1);
	trgmsg(16056, var1, trgevent().getPerson());
	trgchooser().setItems(16057, 16058);
	if (trgchooser().show(16059, trgevent().getPerson(), var1) != 0)
	{
		trgmsg(16061, trgevent().getPerson(), var1);
		return true;
	}
	trgmsg(16060, trgevent().getPerson(), var1);
	trgmsg(16062, var1, trgevent().getPerson());
	trgscene().fade(0);
	trgsleep();
	trgscene().background(5);
	trgscene().fade(255);
	int var3 = trgsound().playSfxLoop(614);
	trgmsg().setPerson(2, trgevent().getPerson());
	trgmsg(16063, var1, var0);
	trgscene().eventStill(23);
	trgmsg(16064, var0, var1);
	trgmsg(16065, var1, var0);
	trgscene().closeEventStill();
	trgscene().effect(17);
	trgmsg(16066, var0, var1);
	trgsound().stopSfxLoop(var3);

	trgdebate().init();
	trgdebate().setSlot(0, var1, true);
	trgdebate().setSlot(1, var0, false);
	trgdebate().run();
	bool var4 = trgdebate().getWinner() == 0;

	if (var4)
	{
		trgscene().fade(0);
		trgsleep();
		trgscene().background(5);
		trgscene().fade(255);
		trgsound().playSfx(11);
		trgmsg(16067, var0, var1);
		trgscene().fade(0);
		trgsleep();
		trgscene().background(2);
		trgscene().fade(255);
		trgmsg().setPerson(2, var0);
		trgmsg().setPerson(3, var1);
		trgmsg().setPerson(4, trgevent().getPerson());
		trgmsg(16068, var1, trgevent().getPerson());
		trgmsg(16069, var0, trgevent().getPerson());
		trgmsg(16070, trgevent().getPerson(), var0);
		trgmsg(16071, var0, trgevent().getPerson());
		trgmsg().setPerson(0, var0);
		trgsound().playSfx(612);
		trgmsg(16072);
	}
	else
	{
		trgscene().fade(0);
		trgsleep();
		trgscene().background(5);
		trgscene().fade(255);
		trgmsg(16073, var0, var1);
		trgsound().playSfx(613, 100);
		trgmsg(16074, var1, var0);
		trgscene().fade(0);
		trgsleep();
		trgscene().background(2);
		trgscene().fade(255);
		trgsound().playSfx(12);
		trgmsg(16075, var1, trgevent().getPerson());
	}

	if (var4)
	{
		var1.addKouseki(200);
		var0.setLocation(trgevent().getPerson().소속);
		var0.changeForce(trgevent().getPerson().getForceId(), var1, 0);
		var0.addKouseki(200);
		var0.setLoyalty(var1.충성도);
	}
	else
	{
		trglist<City>()(0).init();
		trglist<City>()(0).remove(trgevent().getPerson().소속도시);
		City var5 = trglist<City>()(0).random();
		var0.appear();
		var0.move(var5.toBuilding());
		var0.setBannedKunshu(trgevent().getPerson().getId(), 12);
	}
	return true;
}

/** 무관 수배 */
bool PK_범용이벤트55(bool cond)
{
	if (cond)
	{
		if (!trgevent().getPerson().isIdle())
			return false;

		if (!randbool(5))
			return false;

		if (180 > Scenario().getElapsedDays())
			return false;

		trglist<Person>()(0).init(무장속성_세력, trgevent().getPerson().getForceId());
		trglist<Person>()(0).remove_all_but(무장속성_소속, trgevent().getPerson().소속);
		trglist<Person>()(0).remove(trgevent().getPerson());
		trglist<Person>()(0).remove_all_but(무장속성_충성도, 90, 연산자_크거나같음);
		trglist<Person>()(0).remove_all_but(무장속성_능력 + 무장능력_무력, 75, 연산자_크거나같음);
		trglist<Person>()(0).remove_all_but(무장속성_유휴, true);
		if (trglist<Person>()(0).size() <= 0)
			return false;

		trglist<Person>()(1).clear();
		trglist<Person>()(2).init(무장속성_재야, true);
		trglist<Person>()(2).remove_all_but(무장속성_능력 + 무장능력_무력, 70, 연산자_크거나같음);
		trglist<Person>()(2).remove_all_but(무장속성_유휴, true);
		trglist<Person>()(2).remove_all_but(무장속성_친밀, false, trgevent().getPerson().getId());
		trglist<Person>()(2).remove_all_but(무장속성_배우자, -1);
		trglist<Person>()(2).remove_all_but(무장속성_의형제, -1);

		for (auto i = trglist<Person>()(2).begin(); i; i++)
		{
			for (auto j = trglist<Person>()(0).begin(); j; j++)
			{
				if (j().isCloseWith(i().getId()) || j().isDislike(i().getId()) || i().isDislike(j().getId()) || j().혈연 == i().혈연)
					continue;

				if (j().출신 == i().출신 || j().isLike(i().getId()))
				{
					trglist<Person>()(1).push_back(i());
					break;
				}
			}
		}

		return 0 < trglist<Person>()(1).size();
	}

	Person var0 = trglist<Person>()(1).random();
	Person var1 = trglist<Person>()(0).random();

	trgmsg().setPerson(2, trgevent().getPerson());
	trgmsg().setPerson(3, var1);
	trgmsg().setPerson(4, var0);
	trgsound().playBgm(18);
	trgscene().move(Building(trgevent().getPerson().소속));
	trgsound().playSfx(600);
	trgmsg(16076, 무장_무관);
	trgmsg(16077, trgevent().getPerson());
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgmsg(16078, trgevent().getPerson(), var1);
	trgmsg(16079, var1, trgevent().getPerson());
	trgchooser().setItems(16080, 16081);
	if (trgchooser().show(16082, trgevent().getPerson(), var1) != 0)
	{
		trgmsg(16084, trgevent().getPerson(), var1);
		return true;
	}
	trgmsg(16085, var1, trgevent().getPerson());
	trgscene().fade(0);
	trgsleep();
	trgscene().background(4);
	trgscene().fade(255);
	int var3 = trgsound().playSfxLoop(615);
	trgmsg(16086, var1, var0);
	trgscene().eventStill(25);
	trgmsg(16087, var0, var1);
	trgmsg(16088, var1, var0);
	trgmsg(16089, var0, var1);
	trgmsg(16090, var1, var0);
	trgscene().closeEventStill();
	trgscene().effect(17);
	trgmsg(16091, var0, var1);
	trgsound().stopSfxLoop(var3);

	trgduel().init();
	trgduel().setSlot(0, 0, var1);
	trgduel().setSlot(1, 0, var0);
	trgduel().setControl(0, 0);
	trgduel().run(1);
	bool var4 = trgduel().getWinner() == 0;

	if (var4)
	{
		trgscene().fade(0);
		trgsleep();
		trgscene().background(4);
		trgscene().fade(255);
		int var5 = trgsound().playSfxLoop(615);
		trgsound().playSfx(11);
		trgmsg(16092, var0, var1);
		trgsound().stopSfxLoop(var5);
		trgscene().fade(0);
		trgsleep();
		trgscene().background(2);
		trgscene().fade(255);
		trgmsg(16093, var1, trgevent().getPerson());
		trgmsg(16094, var0, trgevent().getPerson());
		trgmsg(16095, trgevent().getPerson(), var0);
		trgmsg(16096, var0, trgevent().getPerson());
		trgmsg().setPerson(0, var0);
		trgsound().playSfx(612);
		trgmsg(16097);
	}
	else
	{
		trgscene().fade(0);
		trgsleep();
		trgscene().background(4);
		trgscene().fade(255);
		int var5 = trgsound().playSfxLoop(615);
		trgmsg(16098, var0, var1);
		trgsound().playSfx(613);
		trgmsg(16099, var1, var0);
		trgsound().stopSfxLoop(var5);
		trgscene().fade(0);
		trgsleep();
		trgscene().background(2);
		trgscene().fade(255);
		trgsound().playSfx(12);
		trgmsg(16100, var1, trgevent().getPerson());
	}

	if (var4)
	{
		var1.addKouseki(200);
		var0.setLocation(trgevent().getPerson().소속);
		var0.changeForce(trgevent().getPerson().getForceId(), var1, 0);
		var0.addKouseki(200);
		var0.setLoyalty(var1.충성도);
	}
	else
	{
		trglist<City>()(0).init();
		trglist<City>()(0).remove(trgevent().getPerson().소속도시);
		City var5 = trglist<City>()(0).random();
		var0.appear();
		var0.move(var5.toBuilding());
		var0.setBannedKunshu(trgevent().getPerson().getId(), 12);
	}
	return true;
}

/** 토사구팽 */
bool PK_범용이벤트56(bool cond)
{
	if (cond)
	{
		int month = Scenario().월;
		if (month != 1 && month != 4 && month != 7 && month != 10)
			return false;
		if (!trgevent().getPerson().isIdle())
			return false;
		if (Force(trgevent().getPerson().getForceId()).작위 >= 작위_공)
			return false;
		if (35 > Force(trgevent().getPerson().getForceId()).도시수)
			return false;
		if (360 > Scenario().getElapsedDays())
			return false;
		trglist<District>()(0).init(군단속성_세력, trgevent().getPerson().getForceId());
		trglist<District>()(0).remove(Force(trgevent().getPerson().getForceId()).getFirstDistrictId());
		if (trglist<District>()(0).size() <= 0)
			return false;
		trglist<Person>()(0).init(무장속성_세력, trgevent().getPerson().getForceId());
		trglist<Person>()(0).remove(trgevent().getPerson());
		trglist<Person>()(0).remove_all_but(무장속성_유휴, true);
		trglist<Person>()(0).remove_all_but(무장속성_친밀, false, trgevent().getPerson().getId());
		trglist<Person>()(0).remove_all_but(무장속성_소속, trgevent().getPerson().소속);
		trglist<Person>()(0).remove_all_but(무장속성_의리, 의리_낮음, 연산자_작거나같음);
		trglist<Person>()(1).clear();
		for (auto i = trglist<District>()(0).begin(); i; i++)
		{
			Person totoku(i().도독);
			if (totoku.isCloseWith(trgevent().getPerson()) && totoku.충성도 >= 100 && totoku.isIdle())
			{
				trglist<Person>()(1).push_back(totoku);
				trglist<Person>()(0).remove_all_but(무장속성_친밀, false, totoku.getId());
			}
		}
		return trglist<Person>()(1).size() > 0 && trglist<Person>()(0).size() > 0;
	}

	Person var0 = trglist<Person>()(1).random();
	Person var1 = trglist<Person>()(0).random();
	int var2 = 1000;

	// 매력, 지력이 가장 낮은 무장
	for (auto i = trglist<Person>()(0).begin(); i; i++)
	{
		if (i().매력 < var2)
		{
			var2 = i().매력;
			var1 = i();
		}
		else if (i().매력 == var2 && i().지력 < var1.지력)
		{
			var1 = i();
		}
	}

	trgmsg().setPerson(2, trgevent().getPerson());
	trgmsg().setPerson(3, var1);
	trgsound().playBgm(20);
	trgscene().move(Building(trgevent().getPerson().소속), 800);
	trgsound().playSfx(601);
	trgmsg(16101, 무장_문관);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgmsg().setPerson(2, var0);
	trgmsg().setPerson(4, trgevent().getPerson());
	trgmsg(16102, trgevent().getPerson(), var1);
	trgscene().effect(16);
	trgmsg(16103, var1, trgevent().getPerson());
	trgmsg(16104, trgevent().getPerson(), var1);
	trgsound().playSfx(616);
	trgmsg(16105, var1, trgevent().getPerson());
	trgsound().playSfx(12);
	trgmsg(16106, trgevent().getPerson(), var1);
	trgsound().playSfx(616);
	trgmsg(16107, var1, trgevent().getPerson());
	trgchooser().setItems(16108, 16109);
	int var3 = trgchooser().show(16110, trgevent().getPerson());

	if (var3 == 0)
	{
		trgscene().effect(20);
		trgmsg(16111, trgevent().getPerson(), var1);
		trgmsg(16112, var1, trgevent().getPerson());
		trgmsg(16113, trgevent().getPerson(), var1);
		trgsound().playSfx(613);
		trgmsg(16114, var1, trgevent().getPerson());
	}
	else
	{
		trgscene().effect(20);
		trgmsg(16115, trgevent().getPerson(), var1);
		trgmsg(16116, var1, trgevent().getPerson());
		trgscene().fade(0);
		trgsleep(2000);
		trgscene().background(-1);
		trgscene().fade(255);
		trgscene().eventStill(8);
		trgsound().playSfx(12);
		trgmsg(16117);
		trgscene().closeEventStill();
	}

	if (var3 == 0)
	{
		var1.addLoyalty(-20);
	}
	else
	{
		trgevent().getPerson().resetRelationship(var0);
		var0.newForce();
		trglist<Person>()(0).init(무장속성_세력, trgevent().getPerson().getForceId());
		trglist<Person>()(0).remove(trgevent().getPerson());
		trglist<Person>()(0).addLoyalty(-5);
		trglist<City>()(0).init(도시속성_세력, trgevent().getPerson().getForceId());
		trglist<City>()(0).addPublicOrder(-10);
	}

	return true;
}

/** 발탁 */
bool PK_범용이벤트76(bool cond)
{
	if (cond)
	{
		if (trgmgr().getElapsedDays(114) <= 90 && 1 <= trgmgr().getElapsedDays(114))
			return false;
		if (!trgevent().getPerson().isIdle())
			return false;
		if (!randbool(5))
			return false;
		if (360 > Scenario().getElapsedDays())
			return false;
		int month = Scenario().월;
		if (month != 2 && month != 6 && month != 10)
			return false;
		if (Force(trgevent().getPerson().getForceId()).작위 >= 작위_주목)
			return false;
		if (5 > Force(trgevent().getPerson().getForceId()).도시수)
			return false;
		trglist<Person>()(0).init(무장속성_세력, trgevent().getPerson().getForceId());
		trglist<Person>()(0).remove(trgevent().getPerson());
		if (trglist<Person>()(0).size() < 20)
			return false;
		trglist<Person>()(1).clear();
		trglist<Person>()(0).init(무장속성_세력, trgevent().getPerson().getForceId());
		trglist<Person>()(0).remove(trgevent().getPerson());
		trglist<Person>()(0).remove_all_but(무장속성_유휴, true);
		trglist<Person>()(0).remove_all_but(무장속성_의리, 의리_높음, 연산자_크거나같음);
		trglist<Person>()(0).remove_all_but(무장속성_충성도, 100, 연산자_크거나같음);
		trglist<Person>()(0).remove_all_but(무장속성_공적, 10000, 연산자_크거나같음);
		for (auto i = trglist<Person>()(0).begin(); i; i++)
		{
			if (i().isDislike(trgevent().getPerson().getId()) || trgevent().getPerson().isDislike(i().getId()))
				continue;
			trglist<Person>()(1).push_back(i());
		}
		if (trglist<Person>()(1).size() <= 0)
			return false;
		trglist<Person>()(2).clear();
		trglist<Person>()(3).clear();
		trglist<Person>()(0).init(무장속성_세력, trgevent().getPerson().getForceId());
		trglist<Person>()(0).remove(trgevent().getPerson());
		trglist<Person>()(0).remove_all_but(무장속성_유휴, true);
		trglist<Person>()(0).remove_all_but(무장속성_의리, 의리_보통, 연산자_크거나같음);
		trglist<Person>()(0).remove_all_but(무장속성_충성도, 95, 연산자_크거나같음);
		trglist<Person>()(0).remove_all_but(무장속성_공적, 2000, 연산자_보다작음);
		trglist<Person>()(0).remove_all_but(무장속성_신분, 신분_일반);
		for (auto i = trglist<Person>()(0).begin(); i; i++)
		{
			if (i().isDislike(trgevent().getPerson().getId()) || trgevent().getPerson().isDislike(i().getId()))
				continue;
			if (70 <= i().통솔 || 70 <= i().무력 || 70 <= i().지력 || 70 <= i().정치 || 70 <= i().매력)
				trglist<Person>()(2).push_back(i());
		}
		for (auto i = trglist<Person>()(2).begin(); i; i++)
		{
			for (auto j = trglist<Person>()(1).begin(); j; j++)
			{
				if (j().isCloseWith(i().getId()) || j().isDislike(i().getId()) || i().isDislike(j().getId()))
					continue;
				trglist<Person>()(3).push_back(i());
			}
		}
		return 0 < trglist<Person>()(3).size();
	}

	Person var0 = trglist<Person>()(1).random();
	trglist<Person>()(3).sort(무장속성_공적, 정렬_내림차순);
	Person var1 = trglist<Person>()(3).random();

	for (auto i = trglist<Person>()(3).begin(); i; i++)
	{
		if (var0.isLike(i().getId()) || var0.출신 == i().출신)
		{
			var1 = i();
			break;
		}
	}

	trgmsg().setPerson(2, trgevent().getPerson());
	trgmsg().setPerson(3, var0);
	trgmsg().setPerson(4, var1);
	trgsound().playBgm(18);
	trgscene().move(Building(trgevent().getPerson().소속));
	trgscene().fade(0);
	trgsleep();
	trgscene().background(2);
	trgscene().fade(255);
	trgmsg(18734, trgevent().getPerson());
	trgsound().playSfx(610);
	trgmsg(18735, var0, trgevent().getPerson());
	trgmsg(18736, trgevent().getPerson(), var0);
	trgmsg(18737, var0, trgevent().getPerson());
	trgmsg(18738, trgevent().getPerson(), var0);
	trgmsg(18739, trgevent().getPerson());
	trgscene().fade(0);
	trgsleep();
	trgscene().eventStill(21);
	trgscene().fade(255);
	trgmsg(18740, var1, trgevent().getPerson());
	trgsound().playSfx(610);
	trgmsg(18741, trgevent().getPerson(), var1);
	trgmsg(18742, var1, trgevent().getPerson());
	trgmsg(18743, trgevent().getPerson(), var1);
	trgmsg(18744, var1, trgevent().getPerson());
	trgmsg(18745, trgevent().getPerson(), var1);
	trgscene().closeEventStill();
	trgscene().effect(20);
	trgmsg(18746, var1, trgevent().getPerson());
	trgscene().fade(0);
	trgsleep();
	trgscene().background(-1);
	trgsound().playSfx(11);
	trgmsg(18747);
	trgscene().fade(255);

	trgmgr().setLastRunTime(114, Scenario().getDayCount());

	var0.addKouseki(200);
	var1.addKouseki(2000);
	var1.addLoyalty(2 + (2 * var1.의리));

	return true;
}

/** 중상모략 */
bool PK_범용이벤트77(bool cond)
{
	if (cond)
	{
		if (!trgevent().getPerson().isIdle())
			return false;

		if (!randbool(5))
			return false;

		if (360 > Scenario().getElapsedDays())
			return false;

		int month = Scenario().월;
		if (month != 4 && month != 6 && month != 12)
			return false;

		if (Force(trgevent().getPerson().getForceId()).작위 >= 작위_주목)
			return false;

		if (5 > Force(trgevent().getPerson().getForceId()).도시수)
			return false;

		trglist<Person>()(0).init(무장속성_세력, trgevent().getPerson().getForceId());
		trglist<Person>()(0).remove(trgevent().getPerson());
		if (trglist<Person>()(0).size() < 20)
			return false;

		trglist<Person>()(1).init(무장속성_세력, trgevent().getPerson().getForceId());
		trglist<Person>()(1).remove(trgevent().getPerson());
		trglist<Person>()(1).remove_all_but(무장속성_유휴, true);
		trglist<Person>()(1).remove_all_but(무장속성_신분, 신분_일반);
		trglist<Person>()(1).remove_all_but(무장속성_의리, 의리_낮음, 연산자_작거나같음);
		trglist<Person>()(1).remove_all_but(무장속성_충성도, 100, 연산자_보다작음);
		if (trglist<Person>()(1).size() <= 0)
			return false;

		trglist<Person>()(2).clear();
		trglist<Person>()(3).clear();
		trglist<Person>()(0).init(무장속성_세력, trgevent().getPerson().getForceId());
		trglist<Person>()(0).remove(trgevent().getPerson());
		trglist<Person>()(0).remove_all_but(무장속성_유휴, true);
		trglist<Person>()(0).remove_all_but(무장속성_공적, 10000, 연산자_크거나같음);

		for (auto i = trglist<Person>()(0).begin(); i; i++)
		{
			if (!i().isCloseWith(trgevent().getPerson().getId()))
				trglist<Person>()(2).push_back(i());
		}

		for (auto i = trglist<Person>()(2).begin(); i; i++)
		{
			bool var1 = false;
			for (auto j = trglist<Person>()(1).begin(); j; j++)
			{
				if (j() == i() || j().isCloseWith(i().getId()) || j().isLike(i().getId()) || i().isLike(j().getId()))
					var1 = true;
			}
			if (!var1)
				trglist<Person>()(3).push_back(i());
		}

		return 0 < trglist<Person>()(3).size();
	}

	Person var0 = trglist<Person>()(1).random();
	Person var1 = trglist<Person>()(3).random();

	trgmsg().setPerson(2, trgevent().getPerson());
	trgmsg().setPerson(3, var0);
	trgmsg().setPerson(4, var1);
	trgsound().playBgm(20);
	trgscene().move(Building(trgevent().getPerson().소속), 1000);
	trgsound().playSfx(601);
	trgmsg(18748, 무장_전령, trgevent().getPerson());
	trgmsg(18749, trgevent().getPerson(), 무장_전령);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(5);
	trgscene().eventStill(26);
	trgscene().fade(255);
	trgmsg(18750, trgevent().getPerson(), var0);
	trgmsg(18751, var0, trgevent().getPerson());
	trgmsg(18752, trgevent().getPerson(), var0);
	trgscene().closeEventStill();
	trgscene().effect(16);
	trgmsg(18753, var0, trgevent().getPerson());
	trgmsg(18754, trgevent().getPerson(), var0);
	trgmsg(18755, var0, trgevent().getPerson());

	trgdebate().init();
	trgdebate().setSlot(0, trgevent().getPerson(), true);
	trgdebate().setSlot(1, var0, false);
	trgdebate().run();
	bool var2 = trgdebate().getWinner() == 0;

	if (var2)
	{
		trgscene().fade(0);
		trgsleep();
		trgscene().background(5);
		trgscene().fade(255);
		trgmsg(18756, trgevent().getPerson(), var0);
		trgmsg(18757, var0, trgevent().getPerson());
		trgscene().effect(13);
		trgmsg(18758, trgevent().getPerson(), var0);
	}
	else
	{
		trgscene().fade(0);
		trgsleep();
		trgscene().background(5, 0);
		trgscene().fade(255);
		trgmsg(18759, trgevent().getPerson(), var0);
		trgscene().effect(17);
		trgmsg(18760, var0, trgevent().getPerson());
		trgscene().fade(0);
		trgsleep();
		trgscene().background(2, 0);
		trgscene().fade(255);
		trgmsg(18761, var1, trgevent().getPerson());
		trgsound().playSfx(610, 100);
		trgmsg(18762, trgevent().getPerson(), var1);
		trgmsg(18763, var1, trgevent().getPerson());
		trgscene().effect(13);
		trgmsg(18764, trgevent().getPerson(), var1);
		trgmsg(18765, var1, trgevent().getPerson());
	}

	trgmgr().setLastRunTime(115, Scenario().getDayCount());

	if (var2)
	{
		var1.addLoyalty(2 + (2 * var1.의리));
	}
	else
	{
		var0.addKouseki(200);
		var0.addLoyalty(2 + (2 * var0.의리));
		var1.addLoyalty(-5 - (2 * var1.의리));
	}

	return true;
}

/** 문관 수련 */
bool PK_범용이벤트81(bool cond)
{
	if (cond)
	{
		if (trgmgr().getElapsedDays(112) <= 90 && 1 <= trgmgr().getElapsedDays(112))
			return false;

		trglist<Person>()(1).clear();
		trglist<Person>()(0).init(무장속성_세력, trgevent().getPerson().getForceId());
		trglist<Person>()(0).remove_all_but(무장속성_신분, 신분_군주, 연산자_같지않음);
		for (auto i = trglist<Person>()(0).begin(); i; i++)
		{
			switch (i().육성중인능력)
			{
			case 능력종류2_지력:
			case 능력종류2_정치:
			case 능력종류2_매력:
			case 능력종류2_병기:
			case 능력종류2_수군:
				if (Force(trgevent().getPerson().getForceId()).군사 == i().getId())
					break;
				if (i().isDislike(Force(trgevent().getPerson().getForceId()).군사))
					break;
				if (Person(Force(trgevent().getPerson().getForceId()).군사).isDislike(i().getId()))
					break;
				trglist<Person>()(1).push_back(i());
				break;
			}
		}

		if (trglist<Person>()(1).size() <= 0)
			return false;

		if (!Person(Force(trgevent().getPerson().getForceId()).군사).isIdle())
			return false;

		return randbool(10);
	}

	trglist<Person>()(1).sort(무장속성_공적, 정렬_내림차순);

	Person var0 = trglist<Person>()(1)[0];

	trgmsg().setPerson(2, var0);
	trgmsg().setPerson(3, Force(trgevent().getPerson().getForceId()).군사);
	trgmsg().setCity(0, var0.소속도시);
	trgsound().playBgm(18);
	trgscene().move(Building(var0.소속));
	trgmsg(18814);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(5);
	trgscene().eventStill(23);
	int var1 = trgsound().playSfxLoop(614);
	trgscene().fade(255);
	trgmsg(18815, Force(trgevent().getPerson().getForceId()).군사, var0);
	trgmsg(18816, var0, Force(trgevent().getPerson().getForceId()).군사);
	trgscene().closeEventStill();
	trgscene().effect(17);
	trgmsg(18817, Force(trgevent().getPerson().getForceId()).군사, var0);
	trgsound().stopSfxLoop(var1);

	trgdebate().init();
	trgdebate().setSlot(0, var0, true);
	trgdebate().setSlot(1, Force(trgevent().getPerson().getForceId()).군사, false);
	trgdebate().run();
	bool var2 = trgdebate().getWinner() == 0;

	if (var2)
	{
		trgscene().fade(0);
		trgsleep();
		trgscene().background(5);
		trgscene().fade(255);
		trgmsg(18818, Force(trgevent().getPerson().getForceId()).군사, var0);
		trgsound().playSfx(11);
		trgmsg(18819, var0, Force(trgevent().getPerson().getForceId()).군사);
		trgscene().fade(0);
		trgsleep();
		trgscene().background(-1);
		trgsound().playSfx(10);
		trgmsg(18820);
		trgscene().fade(255);
	}
	else
	{
		trgscene().fade(0);
		trgsleep();
		trgscene().background(5);
		trgscene().fade(255);
		trgmsg(18821, Force(trgevent().getPerson().getForceId()).군사, var0);
		trgsound().playSfx(12);
		trgmsg(18822, var0, Force(trgevent().getPerson().getForceId()).군사);
		trgscene().fade(0);
		trgsleep();
		trgscene().background(-1);
		trgsound().playSfx(10);
		trgmsg(18823);
		trgscene().fade(255);
	}

	trgmgr().setLastRunTime(112, Scenario().getDayCount());

	if (var2)
	{
		var0.addKouseki(1000);
		var0.addStatExp(무장능력_지력, 50);
		var0.addStatExp(무장능력_정치, 50);
		var0.addStatExp(무장능력_매력, 50);
	}
	else
	{
		var0.addStatExp(무장능력_지력, 10);
		var0.addStatExp(무장능력_정치, 10);
		var0.addStatExp(무장능력_매력, 10);
	}
	return true;
}

/** 무관 수련 */
bool PK_범용이벤트82(bool cond)
{
	if (cond)
	{
		if (trgmgr().getElapsedDays(113) <= 90 && 1 <= trgmgr().getElapsedDays(113))
			return false;

		trglist<Person>()(1).clear();
		trglist<Person>()(0).init(무장속성_세력, trgevent().getPerson().getForceId());
		trglist<Person>()(0).remove_all_but(무장속성_신분, 신분_군주, 연산자_같지않음);
		for (auto i = trglist<Person>()(0).begin(); i; i++)
		{
			switch (i().육성중인능력)
			{
			case 능력종류2_통솔:
			case 능력종류2_무력:
			case 능력종류2_창병:
			case 능력종류2_극병:
			case 능력종류2_노병:
			case 능력종류2_기병:
				if (Force(trgevent().getPerson().getForceId()).군사 == i().getId())
					break;
				if (i().isDislike(Force(trgevent().getPerson().getForceId()).군사))
					break;
				if (Person(Force(trgevent().getPerson().getForceId()).군사).isDislike(i().getId()))
					break;
				trglist<Person>()(1).push_back(i());
				break;
			}
		}

		if (trglist<Person>()(1).size() <= 0)
			return false;

		trglist<Person>()(2).clear();
		trglist<Person>()(0).init(무장속성_재야, true);
		trglist<Person>()(0).remove_all_but(무장속성_능력 + 무장능력_무력, 70, 연산자_크거나같음);
		trglist<Person>()(0).remove_all_but(무장속성_유휴, true);
		trglist<Person>()(0).remove_all_but(무장속성_친밀, false, trgevent().getPerson().군주);
		for (auto i = trglist<Person>()(0).begin(); i; i++)
		{
			for (auto j = trglist<Person>()(1).begin(); j; j++)
			{
				if (j().isCloseWith(i().getId()))
					continue;
				if (j().isDislike(i().getId()))
					continue;
				if (i().isDislike(j().getId()))
					continue;
				if (j().혈연 == i().혈연)
					continue;
				trglist<Person>()(2).push_back(i());
			}
		}

		if (trglist<Person>()(2).size() <= 0)
			return false;

		if (!Person(Force(trgevent().getPerson().getForceId()).군사).isIdle())
			return false;

		if (!randbool(10))
			return false;
		return true;
	}

	trglist<Person>()(1).sort(무장속성_공적, 정렬_내림차순);

	Person var0 = trglist<Person>()(1)[0];
	Person var1 = trglist<Person>()(2).random();

	trgmsg().setPerson(2, var0);
	trgmsg().setPerson(3, var1);
	trgmsg().setCity(0, var0.소속도시);
	trgsound().playBgm(18);
	trgscene().move(Building(var0.소속), 1000);
	trgmsg(18824);
	trgscene().fade(0);
	trgsleep();
	trgscene().background(3);
	int var2 = trgsound().playSfxLoop(608);
	trgscene().fade(255);
	trgsound().playSfx(606);
	trgsound().playSfx(606);
	trgmsg(18825, var0);
	trgsound().playSfx(601);
	trgscene().effect(20);
	trgmsg(18826, var0);
	trgmsg(18827, var1, var0, 15093);
	trgmsg(18828, var0, var1);
	trgsound().playSfx(610, 100);
	trgmsg(18829, var1, var0, 15093);
	trgmsg(18830, var0, var1);
	trgmsg(18831, var1, var0);
	trgscene().effect(17);
	trgmsg(18832, var0, var1);
	trgsound().stopSfxLoop(var2);

	trgduel().init();
	trgduel().setSlot(0, 0, var0);
	trgduel().setSlot(1, 0, var1);
	trgduel().setControl(0, 0);
	trgduel().run(1);
	bool var3 = trgduel().getWinner() == 0;

	if (var3)
	{
		trgscene().fade(0);
		trgsleep();
		trgscene().background(3);
		trgscene().fade(255);
		trgmsg(18833, var1, var0);
		trgsound().playSfx(11);
		trgmsg(18834, var0, var1);
		trgscene().fade(0);
		trgsleep();
		trgscene().background(-1);
		trgsound().playSfx(10);
		trgmsg(18835);
		trgscene().fade(255);
	}
	else
	{
		trgscene().fade(0);
		trgsleep();
		trgscene().background(3);
		trgscene().fade(255);
		trgmsg(18836, var1, var0);
		trgsound().playSfx(12, 100);
		trgmsg(18837, var0, var1);
		trgscene().fade(0);
		trgsleep();
		trgscene().background(-1);
		trgsound().playSfx(10);
		trgmsg(18838);
		trgscene().fade(255);
	}

	trgmgr().setLastRunTime(113, Scenario().getDayCount());

	if (var3)
	{
		var0.addKouseki(200);
		var0.addStatExp(무장능력_통솔, 25);
		var0.addStatExp(무장능력_무력, 25);
		var0.addWeaponExp(병기_창, 25);
		var0.addWeaponExp(병기_극, 25);
		var0.addWeaponExp(병기_노, 25);
		var0.addWeaponExp(병기_군마, 25);
		var1.setLocation(var0.소속);
		var1.changeForce(trgevent().getPerson().getForceId(), var0, 0);
		var1.addKouseki(200);
		var1.setLoyalty(var0.충성도);
	}
	else
	{
		var0.addStatExp(무장능력_통솔, 10);
		var0.addStatExp(무장능력_무력, 10);
		var0.addWeaponExp(병기_창, 10);
		var0.addWeaponExp(병기_극, 10);
		var0.addWeaponExp(병기_노, 10);
		var0.addWeaponExp(병기_군마, 10);
	}

	return true;
}