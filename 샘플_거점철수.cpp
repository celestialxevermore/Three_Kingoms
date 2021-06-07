namespace 샘플_거점철수 {

Main main;

class Main {
	Main() {
		regai(AICallbackType(callback));
	}

	bool callback(Force force) {
		locktrg(이벤트2_부대생성);

		// 플레이어, 이민족 세력은 제외.
		if (force.isPlayer() || !force.isNormalForce()) {
			unlocktrg(이벤트2_부대생성);
			return false;
		}

		int force_id = force.getId();
		for (int i = 0; i < 거점_끝; i++) {
			Building building(i);
			if (building.getForceId() == force_id && needRetreat(building))
				retreat(building);
		}

		unlocktrg(이벤트2_부대생성);
		return false;
	}

	/** 철수가 필요한 거점인지 판단 */
	bool needRetreat(Building building) {
		NeedRetreatHelper helper(building);
		return helper.result;
	}

	/** 철수 명령 */
	bool retreat(Building building) {
		List<Person> officers = building.명령가능무장;
		if (officers.empty())
			return false;
		int target = getNearestBase(building);
		if (target == -1)
			return false;
		officers.sort(무장속성_능력 + 무장능력_통솔, 정렬_내림차순);
		array<int> member = { officers[0].getId() };
		int unit_id = Controller().transport(building, member, building.금, building.병량, building.병력, getWeaponsArray(building), 부대임무_이동, Building(target).getPos());
		if (unit_id != -1)
			Unit(unit_id).행동완료 = true;
		return true;
	}

	array<int> getWeaponsArray(Building building) {
		array<int> buf;
		for (int i = 0; i < 병기_끝; i++)
			buf.push_back(building.병기[i]);
		return buf;
	}

	/** 가장 가까운 아군 거점을 얻음. 일단은 도시만 확인. */
	int getNearestBase(Building src) {
		int best_dst = -1;
		int best_distance = 0;
		for (int i = 0; i < 거점_끝; i++) {
			Building dst(i);
			if (src.getId() == i || src.getForceId() != dst.getForceId() || dst.시설 != 시설_도시)
				continue;
			int distance = Path().getDistance(src.getId(), i, src.getForceId());
			if (distance < best_distance || best_dst == -1) {
				best_dst = i;
				best_distance = distance;
			}
		}
		return best_dst;
	}
};

class NeedRetreatHelper {
	Building building;
	bool result;
	int own_transport;
	int enemy_unit1;		// 근접 적 전투부대
	int enemy_unit3;		// 3칸이하 적 전투부대
	int enemy_troops3;		// 3칸이하 적 전투부대병력

	NeedRetreatHelper(Building building) {
		this.building = building;
		result = false;
		own_transport = 0;
		enemy_unit1 = 0;
		enemy_unit3 = 0;
		enemy_troops3 = 0;

		Map().range(building.getPos(), 1, 4 + (building.시설 == 시설_도시 ? 1 : 0), RingCallbackType(callback));

		result = test();
	}

	bool callback(Hex hex, Point pos) {
		Unit unit(hex.getUnit());
		if (isalive(unit)) {
			int distance = Map().getDistance(building.getPos(), pos);
			if (building.isEnemy(unit)) {
				if (distance <= 1) {
					enemy_unit1++;
				}
				if (distance <= 3) {
					enemy_unit3++;
					enemy_troops3 += unit.병력;
				}
			}
			else {
			}
		}
		return false;
	}

	bool test() {
		if (enemy_unit1 == 6)
			return false;
		// 잔여 내구가 아슬아슬한 경우
		if (building.병력 < enemy_troops3 * 0.8 && building.내구 < building.최대내구 * 0.5 && building.내구 < enemy_troops3 * 0.04)
			return true;
		// 잔여 병력이 아슬아슬한 경우
		if (building.병력 < enemy_troops3 * 0.8 && building.병력 < enemy_troops3 * 0.06)
			return true;
		return false;
	}
};

} // namespace