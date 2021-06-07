namespace 세력재배치 {

Main main;

class Main
{
	Main()
	{
		regtrg(이벤트2_게임초기화, 트리거_필수이벤트, TriggerCallbackType2(callback));
	}

	bool callback(trgevent2 e)
	{
		if (!Scenario().불러오기 && Scenario().번호 == 7)
		{
			array<string> items = { "예", "아니오" };
			if (MessageBox().choose(items, "세력을 재배치 하시겠습니까?") != 0)
				return false;
		}
		else
		{
			return false;
		}

		List<Force> forces;
		array<int> count;
		std::Random random(win32api::GetTickCount());

		forces.init();
		forces.shuffle();
		for (auto force = forces.begin(); force; force++)
			count.insertLast(force().도시수);

		// 도시 재배치
		Partition partition(count);
		for (int i = 0; i < forces.size(); i++)
		{
			List<City> a(도시속성_세력, forces[i].getId()); // 불필요한 도시
			List<City> b; // 필요한 도시

			for (int j = 0; j < 도시_끝; j++)
			{
				if (partition.result[j] == i)
				{
					if (a.find(j))
						a.erase(j);
					else
						b.push_back(j);
				}
			}

			a.shuffle();
			b.shuffle();

			for (int j = 0; j < a.size(); j++)
			{
				Building ab = a[j].toBuilding();
				Building bb = b[j].toBuilding();
				BuildingContext ac(ab);
				BuildingContext bc(bb);
				ac.move(bb);
				bc.move(ab);

				// 황제 재설정
				if (i == 0 && j == 0)
				{
					int building_id = bb.getId();

					Person(무장_영제).setService(building_id);
					Person(무장_영제).setLocation(building_id);
					Person(무장_영제).setMibun(신분_사망);

					Person(무장_소제).setService(building_id);
					Person(무장_소제).setLocation(building_id);
					Person(무장_소제).setMibun(신분_사망);

					Person(무장_헌제).setService(building_id);
					Person(무장_헌제).setLocation(building_id);
					Person(무장_헌제).setMibun(신분_사망);

					switch (random(3))
					{
					case 0: Person(무장_영제).setMibun(-1); Scenario().setEmperor(무장_영제); break;
					case 1: Person(무장_소제).setMibun(-1); Scenario().setEmperor(무장_소제); break;
					case 2: Person(무장_헌제).setMibun(-1); Scenario().setEmperor(무장_헌제); break;
					}
				}
			}
		}

		// 관문, 항구 재설정
		for (int i = 0; i < 도시_끝; i++)
		{
			City city(i);
			for (int j = 0; j < 5; j++)
			{
				if (city.관문[j] == -1)
					continue;
				Building building(city.관문[j]);
				if (city.getForceId() == -1)
				{
					BuildingContext context;
					context.move(building);
				}
				else
				{
					BuildingContext context;
					context.force_id = city.getForceId();
					context.district_id = city.getDistrictId();
					context.gold = city.금 / 10;
					context.food = city.병량 / 10;
					context.troops = city.병력 / 10;
					context.energy = city.기력;
					context.weapons[random(병기_창, 병기_군마)] = context.troops;
					context.move(building);
				}
			}
		}

		return false;
	}
};

class Partition
{
	array<int> result(도시_끝);
	array<int> start;
	std::Random random(win32api::GetTickCount());

	/**
		@param count 도시 수 배열
	*/
	Partition(const array<int> &in count)
	{
		// 시작 도시(start)를 무작위로 선정해 이웃 도시를 무작위로 count 수만큼 선택. 성공할때까지 반복.
		// 무식한 방법이지만 도시가 42개가 밖에 안되기 때문에 느리지 않음.
		bool retry = true;
		do {
			// 초기화
			this.start.resize(도시_끝);
			for (int i = 0; i < 도시_끝; i++)
			{
				this.start[i] = i;
				this.result[i] = -1;
			}

			// 시작 도시 섞기
			this.shuffle(this.start);

			retry = false;
			for (int i = 0; i < count.length(); i++)
			{
				// 실패했다면 처음부터 다시
				if (this.spread(this.start[0], count[i], i) != 0)
				{
					retry = true;
					break;
				}
			}
		} while (retry);
	}

	/**
		city_id 도시를 기준으로 n 개의 도시만큼 선택
		@return 남은 개수
	*/
	int spread(int city_id, int n, int index)
	{
		// 끝났거나 이미 다른 세력의 도시인 경우 리턴.
		if (n <= 0 || this.result[city_id] != -1)
			return n;

		this.result[city_id] = index;
		n -= 1;

		int pos = this.start.find(city_id);
		if (pos >= 0)
			this.start.removeAt(pos);

		// 이웃도시 섞기.
		City city(city_id);
		array<int> neighbor_city_id(6);
		for (int i = 0; i < 6; i++)
			neighbor_city_id[i] = city.이웃[i];
		this.shuffle(neighbor_city_id);

		for (int i = 0; i < 6; i++)
		{
			if (neighbor_city_id[i] != -1 && this.result[neighbor_city_id[i]] == -1)
				n = this.spread(neighbor_city_id[i], n, index);
			if (n == 0)
				break;
		}

		// 남은 도시 수를 리턴
		return n;
	}

	/***/
	void shuffle(array<int>& arr)
	{
		int n = arr.length();
		for (int i = 0; i < n; i++)
		{
			int j = this.random(n);
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
};

class BuildingContext
{
	int force_id = -1;
	int district_id = -1;
	List<Person> officers;
	int gold = 0;
	int food = 0;
	int hp = 0;
	int public_order = 0;
	int troops = 0;
	int energy = 0;
	array<int> weapons(병기_끝, 0);
	private Building target;

	BuildingContext() {}

	BuildingContext(Building building)
	{
		int building_id = building.getId();
		force_id = building.getForceId();
		district_id = building.getDistrictId();
		if (세력Id_isValid(force_id))
		{
			officers.init(무장속성_세력, force_id);
			officers.remove_all_but(무장속성_소속, building.getId());
		}
		gold = building.금;
		food = building.병량;
		// hp = building.내구;
		if (building_id >= 0 && building_id < 도시_끝)
			public_order = building.toCity().치안;
		troops = building.병력;
		energy = building.기력;
		for (int i = 0; i < 병기_끝; i++)
			weapons[i] = building.병기[i];
	}

	void move(Building building)
	{
		target = building;
		int building_id = building.getId();
		if (force_id != -1)
		{
			if (building_id >= 건물_도시_시작 && building_id < 건물_도시_끝)
				building.toCity().군단 = district_id;
			if (building_id >= 건물_관문_시작 && building_id < 건물_관문_끝)
				building.toGate().군단 = district_id;
			if (building_id >= 건물_항구_시작 && building_id < 건물_항구_끝)
				building.toPort().군단 = district_id;
		}
		for (auto officer = officers.begin(); officer; officer++)
		{
			officer().setService(building_id);
			officer().setLocation(building_id);
		}
		building.setGold(gold);
		building.setFood(food);
		// building.setHP(hp);
		if (building_id >= 0 && building_id < 도시_끝)
			building.toCity().setPublicOrder(public_order);
		building.setTroops(troops);
		building.setEnergy(energy);
		for (int i = 0; i < 병기_끝; i++)
			building.setWeapons(i, weapons[i]);
	}

	// 이 작업을 move 함수에서 하면 안됨.
	~BuildingContext()
	{
		if (target)
		{
			if (force_id == -1)
			{
				target.neutralize();

				/*
				int building_id = target.getId();
				if (building_id >= 건물_도시_시작 && building_id < 건물_도시_끝)
					target.toCity().군단 = district_id;
				if (building_id >= 건물_관문_시작 && building_id < 건물_관문_끝)
					target.toGate().군단 = district_id;
				if (building_id >= 건물_항구_시작 && building_id < 건물_항구_끝)
					target.toPort().군단 = district_id;
				*/
			}
			else
			{
				target.updateTaishu();
			}
		}
	}
};

} // namespace