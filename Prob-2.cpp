#include<iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;

class entry {
	string key;
	string value;
public:
	entry(string key, string value) : key(key), value(value) {}
	string getKey() {return key;}
	string getValue() {	return value;}
};


class hashTable {
	vector<vector<entry>>* table;
	vector<string> ans;
	int tableSize;
	float loadFactor;
	int entryCount;
public:
	hashTable(int setSize=10) {
		table = new vector<vector<entry>>(setSize);
		tableSize = setSize;
		loadFactor = float(entryCount) / float(tableSize);
		entryCount = 0;
	}

	int getTableSize() { return tableSize; }
	float getLoadFactor() { return loadFactor; }
	int getEntryCount() { return entryCount; }

	int hashFunction(string key) {
		return key.length() % tableSize;
	}

	void size_display() {
		string out = "";
		out = to_string(getEntryCount()) + " " + to_string(getTableSize()) + " " + to_string(getLoadFactor());
		ans.push_back(out);
	}


	void search(string key) {
		int hashValue = hashFunction(key);
		vector<entry>* v = &(table->at(hashValue));
		for (int i = 0; i < v->size(); i++) {
			if (v->at(i).getKey() == key) {
				ans.push_back(v->at(i).getValue());
				return;
			}
		}
		ans.push_back("NOT FOUND");
	}
	
	void rehashing() {
		hashTable new_hashTable(tableSize * 2);
		for (int i = 0; i < table->size(); i++) {
			for (int j = 0; j < table->at(i).size(); j++) {
				new_hashTable.add(this->table->at(i).at(j));
			}
		}
		this->tableSize *= 2;
		this->loadFactor = float(entryCount) / float(tableSize);
		this->table = new_hashTable.table;
		ans.push_back("REHASHING");
	}

	void add(entry e) {
		int hashValue = hashFunction(e.getKey());
		vector<entry>* v = &(table->at(hashValue));
		for (int i = 0; i < v->size(); i++) {
			if (v->at(i).getKey() == e.getKey()) {
				v->at(i) = e;
				return;
			}
		}
		v->push_back(e);
		entryCount++;
		loadFactor = float(entryCount) / float(tableSize);
		if (loadFactor >= 0.5) {
			rehashing();
		}
	}

	void erase(string key) {
		int hashValue = hashFunction(key);
		vector<entry>* v = &(table->at(hashValue));
		for (int i = 0; i < v->size(); i++) {
			if (v->at(i).getKey() == key) {
				v->erase(v->begin() + i);
				entryCount--;
				return;
			}
		}
		ans.push_back("NOT FOUND");
	}

	void display() {
		for (int i = 0; i < ans.size(); i++) {
			cout << ans[i] << endl;
		}
	}
};

void doit() {
	hashTable hjp;
	while (true) {
		string input_getline;
		getline(cin, input_getline);
		stringstream input_ss(input_getline);
		string input;
		input_ss >> input;
		if (input == "EXIT") {
			break;
		}
		else if (input == "SIZE") {
			hjp.size_display();			
		}
		else if (input == "PUT") {
			string key;
			string value;
			input_ss >> key;
			input_ss >> value;
			entry e(key, value);
			hjp.add(e);			
		}
		else if (input == "FIND") {
			string key;
			input_ss >> key;
			hjp.search(key);
		}
		else if (input == "ERASE") {
			string key;
			input_ss >> key;
			hjp.erase(key);
		}
	}
	hjp.display();
}

int main() {
	doit();
}