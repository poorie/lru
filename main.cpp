/*
 * main.cpp
 *
 *  Created on: Sep 13, 2019
 *      Author: poorie
 */

#include <iostream>
#include <unordered_map>
#include <utility> //pair

using namespace std;

class LRUCache {
    //<lru-key, pair<lru-value, lru-key's priority>>
    unordered_map<int,pair<int,unsigned int>> lru;
    //<lru.key's priority, lru.key>
    unordered_map<unsigned int, int> priority;
    //size
    unsigned int LRUCapacity;
    unsigned int topPriority;
    unsigned int lowestPriority;
public:
    LRUCache(int capacity): LRUCapacity(capacity), topPriority(0), lowestPriority(0) {}

    void printLRU(){
        //Print the current lru cache
        cout << "LRUCache contents: " << endl;
        for(auto i = this->lru.begin(); i != this->lru.end(); i++)
        	cout << "Key: " << i->first << " Value: " << i->second.first << " Priority: " << i->second.second << endl;
        cout << endl;
        //Print the current priority
        cout << "Priority contents: " << endl;
        for(auto i = this->priority.begin(); i != this->priority.end(); i++)
        	cout << "Priority: " << i->first << " LRUCache.key: " << i->second << endl;
        cout << endl;
    }

    void applyEvictionPolicy() {
    	//Check if there a priority lower than topPriority minus LRUCapacity
    	int lowerPriorityToRemove = this->topPriority - this->LRUCapacity;
    	if(this->priority.find(lowerPriorityToRemove) != this->priority.end()) {
    		if(this->LRUCapacity < this->lru.size()) {
        		//Find the lru-key for this priority
        		int keyToRemove = this->priority[lowerPriorityToRemove];
        		//Remove this key in lru map
        		lru.erase(keyToRemove);
    		}
    		//Remove this priority and key in the priority map
    		this->priority.erase(lowerPriorityToRemove);
    	}
    	//Else do nothing
        cout << "[EVICT] " << endl;
        printLRU();
    }

    int get(int key) {
    	if(this->lru.find(key) != this->lru.end()) {
    		//If the value is at topPriority
    		if(key == priority[topPriority]){
    			//Don't do anything
    		} else {
        		//Key exists
        		cout << "This key exists at priority: " << this->lru[key].second << endl;
        		unsigned int priorityToRemove = this->lru[key].second;
        		this->priority.erase(priorityToRemove);

        		//Update the priority map < new priority, key>
        		this->topPriority++;
        		//Find this key and update it's priority
        		this->priority[this->topPriority] = key;

        		//Update lru to match priority
        		this->lru[key].second = this->topPriority;
    		}

    		//Print the current lru cache
    		cout << "[GET]" << endl;
    		printLRU();

    		return lru[key].first;
    	}
    	return -1;
    }

    void put(int key, int value) {
    	if(this->lru.find(key) != this->lru.end()) {
    		if(key == priority[topPriority]) {
    			lru[key].first = value;
    			return;
    		}
    		cout << "This key already exists at priority: " << this->lru[key].second << endl;
    		unsigned int priorityToRemove = this->lru[key].second;
    		this->priority.erase(priorityToRemove);
    	}
    	this->topPriority++;
    	//<lru-value, lru-key's priority>
    	pair<int, unsigned int> temp;
    	temp = make_pair(value, this->topPriority);
    	//Adding a new value
        this->lru[key] = temp;
        //Update the priority map < new priority, key>
        this->priority[this->topPriority] = key;

        //Print the current lru cache
        cout << "[PUT]" << endl;
        printLRU();

        //Evict lower priority items if we have more than "LRUCapacity" number of items
        if((this->LRUCapacity < this->lru.size()) || (this->LRUCapacity < this->priority.size())) {
        	cout << "Max LRUCapacity: " << this->LRUCapacity << endl;
        	cout << "Current LRU Size: " << this->lru.size() << endl;
        	cout << "Current priority Size:: " << this->priority.size() << endl;
        	applyEvictionPolicy();
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
#if (0)
	//["LRUCache","put","put","get","put","get","put","get","get","get"]
	//	[[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]
	int capacity = 2;
	LRUCache* obj = new LRUCache(capacity);
	cout << "Put value for (1,1)" << endl;
	obj->put(1,1);

	cout << "Put value for (2,2)" << endl;
	obj->put(2,2);

	int param_1 = obj->get(1);
	cout << "Value at key 1: " << param_1 << endl;

	cout << "Put value for (3,3)" << endl;
	obj->put(3,3);

	param_1 = obj->get(2);
	cout << "Value at key 2: " << param_1 << endl;

	cout << "Put value for (4,4)" << endl;
	obj->put(4,4);

	param_1 = obj->get(1);
	cout << "Value at key 1: " << param_1 << endl;

	param_1 = obj->get(3);
	cout << "Value at key 3: " << param_1 << endl;

	param_1 = obj->get(4);
	cout << "Value at key 4: " << param_1 << endl;
#else
//"get","put","get","get","put","get","put","put","put","get","put","get","get","get","get","put","put","get","get","get","put","put","get","put","get","put","get","get","get","put","put","put","get","put","get","get","put","put","get","put","put","put","put","get","put","put","get","put","put","get","put","put","put","put","put","get","put","put","get","put","get","get","get","put","get","get","put","put","put","put","get","put","put","put","put","get","get","get","put","put","put","get","put","put","put","get","put","put","put","get","get","get","put","put","put","put","get","put","put","put","put","put","put","put"]
//[13],[2,19],[2],[3],[5,25],[8],[9,22],[5,5],[1,30],[11],[9,12],[7],[5],[8],[9],[4,30],[9,3],[9],[10],[10],[6,14],[3,1],[3],[10,11],[8],[2,14],[1],[5],[4],[11,4],[12,24],[5,18],[13],[7,23],[8],[12],[3,27],[2,12],[5],[2,9],[13,4],[8,18],[1,7],[6],[9,29],[8,21],[5],[6,30],[1,12],[10],[4,15],[7,22],[11,26],[8,17],[9,29],[5],[3,4],[11,30],[12],[4,29],[3],[9],[6],[3,4],[1],[10],[3,29],[10,28],[1,20],[11,13],[3],[3,12],[3,8],[10,9],[3,26],[8],[7],[5],[13,17],[2,27],[11,15],[12],[9,19],[2,15],[3,16],[1],[12,17],[9,1],[6,19],[4],[5],[5],[8,1],[11,7],[5,2],[9,28],[1],[2,2],[7,4],[4,22],[7,24],[9,26],[13,28],[11,26]]
	int capacity = 10;
	LRUCache* obj = new LRUCache(capacity);
	cout << "Put value for (10,13)" << endl;
	obj->put(10,13);

	cout << "Put value for (3,17)" << endl;
	obj->put(3,17);

	cout << "Put value for (6,11)" << endl;
	obj->put(6,11);

	cout << "Put value for (10,5)" << endl;
	obj->put(10,5);

	cout << "Put value for (9,10)" << endl;
	obj->put(9,10);

	int param_1 = obj->get(13);
	cout << "Value at key 13: " << param_1 << endl;

	cout << "Put value for (2, 19)" << endl;
	obj->put(2,19);

	param_1 = obj->get(2);
	cout << "Value at key 2: " << param_1 << endl;
#endif
	return 0;
}
