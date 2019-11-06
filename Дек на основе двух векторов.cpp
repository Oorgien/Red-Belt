//#include "test_runner.h"
#include <vector>
#include <iostream>
#include <exception>

using namespace std;
template <typename T>
struct Deque {
public:
	Deque(){
		Front_.resize(0);
		Back_.resize(0);
	}
	bool Empty() const{
		return Front_.empty() && Back_.empty();
	}
	size_t Size() const {
		return Front_.size() + Back_.size();
	}
	T& operator[](size_t index) {
		if (index + 1 > Front_.size()) return Back_[index - Front_.size()];
		return Front_[Front_.size() - index - 1];
	}
	const T& operator[](size_t index) const {
		if (index + 1 > Front_.size()) return Back_[index - Front_.size()];
		return Front_[Front_.size() - index - 1];
	}
	T& Front() {
		if (!Front_.empty()) return Front_[Front_.size() - 1];
		else return Back_[0];
	}
	const T& Front() const{
		if (!Front_.empty()) return Front_[Front_.size() - 1];
		else return Back_[0];
	}
	T& Back() {
		if (!Back_.empty()) return Back_[Back_.size()-1];
		else return Front_[0];
	}
	const T& Back() const {
		if (!Back_.empty()) return Back_[Back_.size() - 1];
		else return Front_[0];
	}
	void PushFront(const T& x) {
		Front_.push_back(x);
	}
	void PushBack(const T& x) {
		Back_.push_back(x);
	}
	T& At(size_t index) {
		if (index >= Front_.size() + Back_.size()) throw out_of_range("out of range");
		if (index + 1 > Front_.size()) return Back_[index - Front_.size()];
		return Front_[Front_.size() - index - 1];
		
		
	}
	const T& At(size_t index) const {
		if (index >= Front_.size() + Back_.size()) throw out_of_range("out of range");
		if (index + 1 > Front_.size()) return Back_[index - Front_.size()];
		return Front_[Front_.size() - index - 1];
	}
		
private:
	vector<T> Front_, Back_;
};



