namespace 군량탄원 {

Main main;

class Main
{
	Main()
	{
		regtrg(이벤트_플레이어턴종료, 트리거_필수이벤트, TriggerCallbackType2(callback), true);
	}

	bool callback(trgevent2 e)
	{
		Person kunshu = e.getPerson();
		City city = Building(kunshu.소속).toCity();

		if (city && city.병량 > 25000 && randbool(2 + (city.메뚜기 ? rand(3) : 0)))
		{
			trgscene().move(Building(kunshu.소속));
			trgscene().fade(0);
			trgsleep();
			trgscene().background(2);
			trgscene().fade(255);

			switch (rand(3))
			{
			case 0: MessageBox().talk(format("\x1b[1x{}\x1b[0x님의 자비가 없이는 살아갈 수 없습니다. 뭔가 먹을 것을 주십시오.", kunshu.이름), 무장_농민); break;
			case 1: MessageBox().talk(format("내일 먹을 것도 없는 형편이라... \x1b[1x{}\x1b[0x님, 도와주십시오.", kunshu.이름), 무장_농민); break;
			case 2: MessageBox().talk("부탁입니다...뭔가...뭔가 먹을 것을...", 무장_농민); break;
			}

			array<int> food = { 0, std::rounddown(city.병량 / 5, -3), std::rounddown(city.병량 / 4, -3), std::rounddown(city.병량 / 3, -3) };
			int tp = 0;
			array<string> items = { "주지 않는다", format("군량 {}을 준다", food[1]), format("군량 {}을 준다", food[2]), format("군량 {}을 준다", food[3]) };
			int i = MessageBox().choose(items, "군량을 주겠습니까?");

			switch (i)
			{
			case 0:
				switch (rand(2))
				{
				case 0: MessageBox().talk("우리에게도 여유가 없소. 용서해 주시오.", kunshu); break;
				case 1: MessageBox().talk("거짓말하지 마시오. 안색도 좋은 것 같은데.", kunshu); break;
				}

				switch (rand(3))
				{
				case 0: MessageBox().talk("...사람도 아니다...", 무장_농민); break;
				case 1: MessageBox().talk("아아... 저더러 죽으라는 말씀이군요...", 무장_농민); break;
				case 2: MessageBox().talk(format("이런... \x1b[1x{}\x1b[0x님만을 의지했건만...", kunshu.이름), 무장_농민); break;
				}
				
				tp = (rand(6) + 1) * 500;
				MessageBox().talk(format("기교 포인트가 \x1b[1x{}\x1b[0x만큼 감소했습니다.", tp));
				Force(kunshu.getForceId()).addTP(-tp, city.getPos());
				break;

			case 1:
			case 2:
			case 3:
				switch (rand(2))
				{
				case 0: MessageBox().talk(format("알았소. 서둘러 군량 {}을 준비시키겠소.", food[i]), kunshu); break;
				case 1: MessageBox().talk(format("그것 참 안됐군. 군량 {}을 주겠소.", food[i]), kunshu); break;
				}

				switch (rand(3))
				{
				case 0: MessageBox().talk("감사합니다. 이 은혜는 잊지 않겠습니다.", 무장_농민); break;
				case 1: MessageBox().talk(format("아아, \x1b[1x{}\x1b[0x님은 생명의 은인입니다. 이 은혜는 꼭 갚겠습니다.", kunshu.이름), 무장_농민); break;
				case 2: MessageBox().talk("감사합니다... 이것으로 어떻게든 연명할 수 있을 것 같습니다.", 무장_농민); break;
				}

				tp = (rand(6) + 1) * 100;
				MessageBox().talk(format("기교 포인트가 \x1b[1x{}\x1b[0x만큼 증가했습니다.", tp));
				Force(kunshu.getForceId()).addTP(tp, city.getPos());
				city.addFood(-food[i], true);
				break;
			}

			trgscene().fade(0);
			trgsleep();
			trgscene().background(-1);
			trgscene().fade(255);
		}

		return false;
	}
};

} // namespace