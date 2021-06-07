namespace 샘플_평정 {

// Main main;

class Main
{
	Main()
	{
		regtrg(이벤트2_키놓음, 트리거_필수이벤트, TriggerCallbackType2(keyup), true);
	}

	bool keyup(trgevent2 e)
	{
		if (e.getNum() == win32api::VK_F5)
		{
			// 간단한 예제입니다.
			int prev_time = game().대사속도;
			game().대사속도 = 100;

			trgcouncil().run(무장_헌제, 무장_유비, 무장_여포, 무장_조조, -1, -1, -1, CouncilCallbackType(sample1));
			
			game().대사속도 = prev_time;
		}
		else if (e.getNum() == win32api::VK_F6)
		{
			// 설전이나 일기토를 사용해야할 경우의 예제입니다.
			// 화면 전환과 관련된 문제로 조금 복잡한 과정을 필요로 합니다.
			int prev_time = game().대사속도;
			game().대사속도 = 100;

			step2_ = 0;
			trgcouncil().run(-1, -1, -1, -1, -1, -1, -1, CouncilCallbackType(sample2));

			game().대사속도 = prev_time;
		}
		else if (e.getNum() == win32api::VK_F7)
		{
			// 인터넷에 떠돌던 형주 반환에 대한 제갈량과 노숙의 이야기의 영화 타짜 버전을 만들어본 예제입니다. 
			int prev_time = game().대사속도;
			game().대사속도 = 100;

			trgscene().move(City(도시_건업), 2000);
			trgdiplomacy().run(무장_손권, -1, 무장_노숙, CouncilCallbackType(scene1));
			trgscene().move(City(도시_강릉), 2000);
			trgcouncil().run(무장_유비, 무장_노숙, 무장_제갈량, -1, -1, -1, -1, CouncilCallbackType(scene2));
			trgscene().effect(18); // 이 줄은 scene 함수에 들어가도 되지만 유기를 중간에 추가할 수 없기 때문에 이 곳에 두는게 자연스러워 보였습니다.
			trgcouncil().run(무장_유비, 무장_노숙, 무장_제갈량, -1, 무장_유기, -1, -1, CouncilCallbackType(scene3));

			game().대사속도 = prev_time;
		}
		return false;
	}

	void sample1()
	{
		trgcouncil().animation(700, 무장_헌제, 0x37);
		MessageBox().talk("회의를 시작하도록 하지.", 무장_헌제);

		trgcouncil().animation(0, 무장_여포, 0x48);
		MessageBox().talk("빼애액!", 무장_여포);

		trgcouncil().animation(0, 무장_유비, 0x4f);
		MessageBox().talk("(절레절레)", 무장_유비);
	}

	private int step2_ = 0;
	void sample2()
	{
		step2_++;
		MessageBox().talk(format("step: {}", step2_));
		if (step2_ == 1)
		{
			trgdebate().init();
			trgdebate().setSlot(0, 850, true); // 신무장
			trgdebate().setSlot(1, 0xcf, false); // 올돌골(지력1)
			// 설전을 보는 경우 종료.(설전이 끝나면 sample2 함수가 다시 호출됩니다.)
			if (trgdebate().run())
				return;
			// 설전을 보지 않는다면 이쪽으로.
			step2_++;
			// 이 곳에는 다른 코드를 추가하지 마세요.
		}
		if (step2_ == 2)
		{
			trgduel().init();
			trgduel().setSlot(0, 0, 850); // 신무장
			trgduel().setSlot(1, 0, 0x15d); // 조방(무력3)
			trgduel().setControl(0, 0);
			if (trgduel().run(1))
				return;
			step2_++;
		}
	}

	void scene1()
	{
		trgdiplomacy d;
		MessageBox m;
		d.animation(100, 무장_노숙, 0x5b);
		m.talk("맡겨만 주쇼잉. 나가 유비 패거리 그 시벌롬들을 확 젓어불고 올랑게", 무장_노숙);
	}

	void scene2()
	{
		trgcouncil c;
		MessageBox m;
		m.talk("(싸늘하다)", 무장_제갈량);
		m.talk("(가슴에 노숙의 시선이 날아와 꽂힌다)", 무장_제갈량);
		m.talk("(하지만 걱정하지 마라)", 무장_제갈량);
		m.talk("(내 계산은 주유보다 빠르니까)", 무장_제갈량);
		c.animation(0, 무장_제갈량, 0x3a);
		m.talk("저희 형주를 살펴보신 소감은\n어떻습니까\n자경께서 보시기에 불만족스럽지는 않...", 무장_제갈량);
		c.animation(0, 무장_노숙, 0x82);
		m.talk("동작그만, 방 안 빼냐?", 무장_노숙);
		c.animation(0, 무장_제갈량, 0x4f);
		m.talk("뭐야", 무장_제갈량);
		m.talk("아예 형주에 눌러 앉을 생각이지?", 무장_노숙);
		c.animation(0, 무장_노숙, 0x5c);
		m.talk("오나라가 빙다리 핫바지로 보이냐 이 새끼야?", 무장_노숙);
		c.animation(0, 무장_유비, 0x37);
		m.talk("형주가 내 땅이 될 수 없다는 증거 있어?", 무장_유비);
		c.animation(0, 무장_노숙, 0x81);
		m.talk("증거? 증거 있지", 무장_노숙);
		c.animation(0, 무장_노숙, 0x37);
		m.talk("너는 우리 오나라에 \'동맹맺어 조조군을 막자\'고 바람을 넣었을 것이여", 무장_노숙);
		m.talk("그런데 정작 동맹이란 니들은 뒤에서 꿀만 빨고 오나라가 조빠지게 싸워서 조조를 물리쳤으니", 무장_노숙); // 늬, 좆
		c.animation(0, 무장_노숙, 0x41);
		m.talk("당연히 형주는 오나라땅 되는 거 아니겠어?", 무장_노숙); // 겄
		c.animation(0, 무장_제갈량, 0x3f);
		m.talk("시나리오 쓰고 있네 우리 아니었음 항복했을 미친 새끼가", 무장_제갈량);
		c.animation(0, 무장_노숙, 0x81);
		m.talk("으허허허허허허허허허허허허허허허허", 무장_노숙);
		c.animation(0, 무장_제갈량, 0x37);
		m.talk("유황숙의 조카 유기의 땅을 되찾아 준 거라고 하면 어쩔건데?", 무장_제갈량);
		c.animation(0, 무장_노숙, 0x3d);
		m.talk("유기는 지금 강하에 있지 형주에는 없어. 여기에 있지도 않은 조카 핑계로 형주를 먹겠다는거 아녀?", 무장_노숙);
		c.animation(0, 무장_제갈량, 0x41);
		m.talk("씨발 천하의 노숙이 혀바닥이 왜이렇게 길어...\n후달리냐?", 무장_제갈량); // 혓
		c.animation(0, 무장_노숙, 0x81);
		m.talk("후달려?\n어허허허허허허허허허", 무장_노숙);
		c.animation(0, 무장_노숙, 0x3f);
		m.talk("오냐 내 돈 모두하고 내 손모가질 건다", 무장_노숙);
		m.talk("준비됐어? 까볼까?", 무장_노숙);
		c.animation(0, 무장_노숙, 0x3a);
		m.talk("자 지금부터 확인들어가겠습니다잉", 무장_노숙);
		m.talk("따라란~ 따라란 따 쿵작작 쿵작작\n다라리다라리", 무장_노숙);
	}

	void scene3()
	{
		trgcouncil c;
		MessageBox m;
		m.talk("...", 무장_유기);
		c.animation(0, 무장_유비, 0x81);
		m.talk("유기네.", 무장_유비);
		m.talk("유기야?", 무장_노숙);
		c.animation(0, 무장_노숙, 0x5c);
		m.talk("...내가 봤어\n이 씨발놈 강하에 있는 걸 똑똑히 봤다니께?", 무장_노숙);
		c.animation(0, 무장_제갈량, 0x44);
		m.talk("\'확실하지 않으면 승부를 걸지마라.\'\n이런 거 안배웠어?", 무장_제갈량);
		c.animation(0, 무장_유비, 0x37);
		m.talk("뭐해 형님 오나라로 안 돌아가고", 무장_유비);
	}
};

} // namespace