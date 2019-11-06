#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <numeric>
#include <string>

using namespace std;

struct BookingInformation {
	int64_t time;
	string hotel_name;
	unsigned client_id;
	unsigned room_count;
};

class HotelManager {
public:
	HotelManager() : Bookings() {}
	void Book(const int64_t& time, const string& hotel_name, unsigned& client_id, unsigned& room_count) {
		BookingInformation b;
		b.time = time;
		b.hotel_name = hotel_name;
		b.client_id = client_id;
		b.room_count = room_count;
		Bookings.push(b);

		Clients_[hotel_name][client_id] += room_count;
		Rooms_[hotel_name] += room_count;

		current_time = time;
		Adjust();
	}
	unsigned Rooms(string& hotel_name) {
		return Rooms_[hotel_name];
	}
	size_t Clients(string& hotel_name) {
		return Clients_[hotel_name].size();
	}
private:
	int64_t DAY_SIZE = 86399;
	int64_t current_time = 0;

	queue<BookingInformation> Bookings;
	map<string, unsigned> Rooms_; //Hotels to rooms
	map<string, map<unsigned, unsigned>> Clients_; //Hotels to map of <client_id, number of bookings>

	void Adjust() {
		while (!Bookings.empty() && Bookings.front().time < current_time - DAY_SIZE) {
			string hotel_name_ = Bookings.front().hotel_name;
			unsigned client_ = Bookings.front().client_id;
			unsigned rooms_ = Bookings.front().room_count;
			
			Rooms_[hotel_name_] -= rooms_;
			if (Rooms_[hotel_name_] == 0) Rooms_.erase(hotel_name_);

			Clients_[hotel_name_][client_] -= rooms_;
			if (Clients_[hotel_name_][client_] == 0) Clients_[hotel_name_].erase(client_);

			Bookings.pop();
		}
	}
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	HotelManager hotel;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
	  string query_type;
	  cin >> query_type;
	
		if (query_type == "BOOK") {
			int64_t time;
			unsigned room_count, client_id;
			string hotel_name;
			cin >> time >> hotel_name >> client_id >> room_count;
			hotel.Book(time, hotel_name, client_id, room_count);
			 
		}
		else if (query_type == "CLIENTS") {
			string hotel_name;
			cin >> hotel_name;
			cout << hotel.Clients(hotel_name) << '\n';
		}
		else if (query_type == "ROOMS") {
			string hotel_name;
			cin >> hotel_name;
			cout << hotel.Rooms(hotel_name) << '\n';
		}
	}
	return 0;
}