#include <iostream>
#include <vector>
#include <map>
#include <fstream>
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
	Order(ifstream& in) {
		getline(in, this->goods);
		getline(in, this->date);
		in >> this->number;
		in >> this->price;
		cin.ignore(INT_MAX, '\n');
		bool b = 1;
		cin >> b;
		this->status = (b == 1) ? "done" : "inProgress";
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
	void writeToFile(ofstream& of) {
		of << this->goods <<endl<< this->date << endl<< this->price << endl << this->number << endl << this->status << endl;
	}
};

class Storage {
	int n;
	map < string, pair <vector <Order>, vector <Order> > > clients;
public:
	Storage() {
		n = 0;
	}
	void addOrder(string snp,Order o) {
		n += 1;
		if (o.getStatus() == "done")  clients[snp].first.push_back(o); 
		else
			clients[snp].second.push_back(o);
	}
	void getInfo() {
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
	void WriteToFile() {
		char filename[256];
		cout << "Enter path to file\n";
		cin.ignore(INT_MAX, '\n');
		gets_s(filename);
		ofstream file(filename);
		if (!file) {
			cout << "Error!";
			exit(1);
		}
		file << clients.size() << endl;
		for (pair < string, pair <vector <Order>, vector <Order> > > client : clients) {
			cout << client.first << endl;
			cout << client.second.first.size() + client.second.second.size() << endl; 
			for (int i = 0; i < client.second.first.size(); i += 1) {
				client.second.first[i].writeToFile(file);
			}
			for (int i = 0; i < client.second.second.size(); i += 1) {
				client.second.second[i].writeToFile(file);
			}
		}
	}
	void readFromFile() {
		char filename[256];
		cout << "Enter path to file\n";
		cin.ignore(INT_MAX, '\n');
		gets_s(filename);
		ifstream file(filename);
		if (!file) {
			cout << "Error!";
			exit(1);
		}
		file >> this->n;
		string snp;
		int m;
		for (int i = 1; i <= n; i++) {
			getline(file, snp);
			file >> m;
			for (int j = 1; j <= m; j++) {
				Order o(file);
				this->addOrder(snp,o);
			}
		}
	}
};

int main() {
	Storage s;
	int cmd;
	string name;
	Order o;
	bool run = 1;
	while (run) {
		cout << "Enter 1 to make new order\n";
		cout << "Enter 2 to show all orders\n";
		cout << "Enter 3 to read orders from the file\n";
		cout << "Enter 4 to write orders to the file\n";
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
		case(3):
			s.readFromFile();
			break;
		case(4):
			s.WriteToFile();
			break;
		default:
			run = 0;
			break;
		}
	}
}