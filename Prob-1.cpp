#include<iostream>
#include<string>
#include<vector>
using namespace std;

class MaxHeap {
	vector<int> v;
	vector<string> ans;
public:
	MaxHeap() {}
	bool isEmpty() {return v.size() == 0;}
	int getParentIndex(int index) { return (index - 1) / 2; }
	int getLeftIndex(int index) { return index * 2 + 1; }
	int getRightIndex(int index) { return index * 2 + 2; }

	int getParentKey(int index) { return v[(index - 1) / 2]; }
	int getLeftKey(int index) { return v[index * 2 + 1]; }
	int getRightKey(int index) { return v[index * 2 + 2]; }

	void insert(int key) {
		v.push_back(key);
		int insertIndex = v.size() - 1;
		while (insertIndex != 0 && key > getParentKey(insertIndex)) {
			int tmp = getParentKey(insertIndex);
			v[getParentIndex(insertIndex)] = key;
			v[insertIndex] = tmp;
			insertIndex = getParentIndex(insertIndex);
		}
	}
	void removeMax() {
		if (isEmpty()) {
			return;
		}
		int lastKey = v[v.size() - 1];
		int parent = 0;
		int child = 1;
		while (child <= v.size() - 1) {
			if (child < v.size() - 2 && getLeftKey(parent) < getRightKey(parent)) {
				child++;
			}
			if (lastKey >= v[child]) {
				break;
			}
			v[parent] = v[child];
			parent = child;
			child = getLeftIndex(child);
		}
		v[parent] = lastKey;
		v.pop_back();
		return;
	}
	void insertAns(int many) {
		string out = "";
		if (many < v.size()) {
			removeMax();
		}
		for (int i = 0; i < v.size(); i++) {
			out += to_string(v[i]);
			out += " ";
		}
		ans.push_back(out);
	}
	void display() {
		for (int i = 0; i < ans.size(); i++) {
			cout << ans[i] << endl;
		}
	}
};

void doit() {
	MaxHeap hjp;
	string num_str;
	getline(cin, num_str);
	int many = stoi(num_str);
	while (true) {
		string input;
		getline(cin, input);
		if (input == "EXIT") {
			break;
		}
		int input_int = stoi(input);
		hjp.insert(input_int);
		hjp.insertAns(many);
	}
	hjp.display();
}

int main() {
	doit();
}