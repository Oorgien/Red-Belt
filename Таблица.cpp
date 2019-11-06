#include "test_runner.h"
#include <vector>
#include <tuple>

using namespace std;
template <typename T>
struct Table {
public:
	Table(const size_t& columns, const size_t& lines) :lines_(lines), columns_(columns) {
		values.resize(columns);
		for (auto& item : values) {
			item.resize(lines);
		}
	}
	vector<vector<T>> values;

	vector<T>& operator[](size_t index) {
		return values[index];
	}

	const vector<T>& operator[](size_t index) const {
		return values[index];
	}

	void Resize(const size_t& new_columns, const size_t& new_lines) {
		values.resize(new_columns);
		for (auto& item : values) {
			item.resize(new_lines);
		}
	}
	pair<size_t, size_t> Size() const{
		size_t MAX=0;
		for (auto item : values) {
			if (item.size() > MAX) MAX = item.size();
		}
		return {values.size(),MAX};
	}


private:
	size_t columns_, lines_;
};


void TestTable() {
	Table<int> t(2, 1);
	ASSERT_EQUAL(t.Size().first, 2u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestTable);
	return 0;
}