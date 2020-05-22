#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Order {
	string goods;
	string date;
	int price;
	int number;
	string status;
public:
	Order() {

	}
	Order(string goods, string date, int price,int number, string status) {
		this->goods = goods;
		this->date = date;
		this->price = price;
		this->number = number;
		this->status = status;
	}
	string getStatus() {
		return this->status;
	}
	void out() {
		cout << "+++++++++++++++++++++++++++++++++++\n";
		cout << "Good's name: " << goods << endl;
		cout << "Good's number: " << number << endl;
		cout << "Good's price: " << price << " UAH" << endl;
		cout << "Data of order: " << date << endl;
		cout << "Status of payment: " << status << endl;
	}
};

class Storage {
	map < string, pair <vector <Order>, vector <Order> > > clients;
public:
	void addOrder(string snp,Order o) {
		if (o.getStatus() == "done")  clients[snp].first.push_back(o); 
		else
			clients[snp].second.push_back(o);
	}
	void getInfo() {
		//if (clients.size() == 0) { cout << "Storage is empty!\n"; return; }
		for (pair < string, pair <vector <Order>, vector <Order> > > client : clients) {
			cout << "==========================================\n";
			cout << "Snp: " << client.first << endl;
			cout << "Number of orders: " << client.second.first.size() + client.second.second.size() << endl;
			cout << "Paid orders " << client.second.first.size()<<endl;
			cout << "Payment in progress orders: " << client.second.second.size() << endl;
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
			cout << "Paid orders\n";
			if (client.second.first.size() == 0) { cout << "No orders\n"; }
			for (int i = 0; i < client.second.first.size(); i += 1) {
				client.second.first[i].out();
			}
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
			cout << "Payment in progress orders" << endl;
			if (client.second.second.size() == 0) { cout << "No orders\n"; }
			for (int i = 0; i < client.second.second.size(); i += 1) {
				client.second.second[i].out();
			}
		}
	}
};

int main() {
	Storage s;
	Order o("Phones", "20.09.2019", 100000, 10, "done");
	s.addOrder("Client1", o);
	o = Order("Laptops", "30.10.2019", 200000, 10, "done");
	s.addOrder("Client1", o);
	o = Order("Gun", "30.01.2020", 50000, 2, "inProgress");
	s.addOrder("Mafia", o);
	o = Order("Drugs", "30.01.2020", 50000, 10, "inProgress");
	s.addOrder("Mafia", o);
	o = Order("Ammo", "30.01.2020",50000,10000,"inProgress");
	s.addOrder("Mafia", o);
	o = Order("CopiedDollars", "31.01.2020", 50000, 5000, "done");
	s.addOrder("AnotherMafia", o);
	o = Order("Gold","01.02.2020",500000,100,"done");
	s.addOrder("AnotherMafia", o);
	o = Order("Bomb", "02.02.2020", 50000, 10, "done");
	s.addOrder("USAGovernment", o);
	s.getInfo();
}