namespace 수상부대휩쓸림 {

Main main;

class Main {
	Main() {
		regtrg(이벤트_일, 트리거_필수이벤트, TriggerCallbackType2(callback));
	}

	bool callback(trgevent2 e) {
		for (auto i = Scenario().부대.begin(); i; i++) {
			if (!i().isInWater() || i().적성 >= 적성_S)
				continue;
			int n = rand(적성_S - i().적성);
			if (n == 0)
				continue;
			array<Point> step;
			Point pos = i().getPos();
			for (int j = 0; j < n; j++) {
				pos = Map().getNeighbor(pos, Hex(pos).방향);
				if (!Map().isValidPos(pos) || Hex(pos).건물존재 || Hex(pos).부대존재 || !(Hex(pos).지형 == 지형_강 || Hex(pos).지형 == 지형_바다) || !i().isLocationable(pos))
					break;
				step.insertLast(pos);
			}
			if (step.length() == 0)
				continue;
			switch (rand(2)) {
			case 0: MessageBox().balloon("당황하지마라!", i().주장, i()); break;
			case 1: MessageBox().balloon("키가 생각대로 움직이지 않는다!", i().주장, i()); break;
			}
			i().move(step);
		}
		return false;
	}
};

} // namespace