namespace std {

const int8 INT8_MIN = -128;
const int16 INT16_MIN = -32768;
const int INT32_MIN = -2147483648;
const int64 INT64_MIN = -9223372036854775808;
const int8 INT8_MAX = 0x7f;
const int16 INT16_MAX = 0x7fff;
const int INT32_MAX = 0x7fffffff;
const int64 INT64_MAX = 0x7fffffffffffffff;
const uint8 UINT8_MAX = 0xff;
const uint16 UINT16_MAX = 0xffff;
const uint UINT32_MAX = 0xffffffff;
const uint64 UINT64_MAX = 0xffffffffffffffff;

int min(int a, int b) { return (a > b) ? b : a; }
int min(int a, int b, int c) { return min(min(a, b), c); }
int min(int a, int b, int c, int d) { return min(min(min(a, b), c), d); }

int max(int a, int b) { return (a > b) ? a : b; }
int max(int a, int b, int c) { return max(max(a, b), c); }
int max(int a, int b, int c, int d) { return max(max(max(a, b), c), d); }

float min(float a, float b) { return (a > b) ? b : a; }

float max(float a, float b) { return (a > b) ? a : b; }

int rounddown(int n, int p) {
	if (p >= 0)
		return n;
	int v = 1;
	while (p++ < 0)
		v *= 10;
	return n - (n % v);
}

const float PI = 3.141592654f;

float radians(float degree) { return degree * (PI / 180.0f); }
float degrees(float radian) { return radian * (180.0f / PI); }

class Random {
	Random() { seed_ = 0; }
	Random(uint seed) { seed_ = seed; }

	void seed(uint seed) { seed_ = seed; }

	int opCall() { return ((seed_ = seed_ * 0x343fd + 0x269ec3) >> 0x10) & 0x7fff; }
	int opCall(int max) { return this(0, max); }
	int opCall(int min, int max) {
		if (min == max) {
			return min;
		}
		else if (min > max) {
			int i = min;
			min = max;
			max = i;
		}
		return min + (this() % (max - min));
	}

	private uint seed_;
};

} // namespace std