#include <iostream>
#include <vector>
#include <map>
#include <string>
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
	Order makeOrder(){
		Order o;
		cout << "Enter name of goods: ";
		getline(cin, o.goods);
		cout << "Enter number of goods: ";
		cin >> o.number;
		cout << "Enter price of goods: ";
		cin >> o.price;
		cout << "Enter date of order: ";
		cin.ignore(INT_MAX, '\n');
		getline(cin, o.date);
		bool b = 1;
		cout << "Enter 1 if you paid for it else 0"<<endl;
		cin >> b;
		o.status = (b == 1) ? "done" : "inProgress";
		return o;
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
	int cmd;
	string name;
	Order o;
	while (1) {
		cout << "Enter 1 to make new order\n";
		cout << "Enter 2 to show all orders\n";
		cout << "Enter anything else to exit\n";
		cin >> cmd;
		switch (cmd)
		{
		case(1):
			cout << "Enter client's name\n";
			cin.ignore(INT_MAX, '\n');
			getline(cin, name);
			s.addOrder(name, o.makeOrder());
			break;
		case(2):
			s.getInfo();
		default:
			break;
		}
	}
}