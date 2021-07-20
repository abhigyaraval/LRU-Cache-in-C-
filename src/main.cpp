/*
LRU Cache in Cpp -> main.cpp
Least recently used cache- Maintains a given size cache for fast O(1) lookup, addition and removal of data.
Author: Abhigya Raval- abhigyaraval@gmail.com
*/

#include <iostream>
#include <iterator>
#include <unordered_map>
#include <string>
#include <list>

using namespace std;


// LRU_cache class
class LRU_cache
{
    public:
    int capacity;

    LRU_cache(int in_capacity)  // Constructor
    {
        if (in_capacity > 0){
            capacity = in_capacity;
        }
        else{
            capacity = 0;
            cout << "Please enter a capacity greater than 0! " << endl;
        }
        
        num_elements = 0;
    }

    void set(string value);
    string get(string value);

    private:

    int num_elements;   // Number of elements in cache at a given time

    // Define a queue and a map for getting O(1) lookup
    list <string> cache;
    unordered_map <string, list<string>::iterator> cache_table;

};

void LRU_cache::set(string value){
    // Check if key is not in cache
    if (cache_table.find(value) == cache_table.end()){
        if (cache.size() == capacity){  // Cache is full
            string last = cache.back();    // Least used item
            list<string>::iterator i = cache.end(); i--;// Get the last element iterator
            cache.pop_back();           // Remove item from back
            cache_table.erase(last);     // Removing entry from map
        }
        else{
            num_elements += 1;
        }
        // Sketchy
        cache.push_front(value);
        cache_table[value] = cache.begin();
    }
    else{
        cache.erase(cache_table[value]);
        cache.push_front(value);
        cache_table[value] = cache.begin();
        cache_table.erase(value);
    }
}

string LRU_cache::get(string key){
    if (cache_table.find(key) == cache_table.end()){
        cout << "Requested value \"" << key << "\" not found in cache!" << endl;
        return "VALUE NOT FOUND!";
    }
    else{
        cout << "Requested value \"" << key << "\" found in cache!" << endl;
        string get_value = *cache_table[key];
        // cout << "Before: " << get_value << endl;
        cache.erase(cache_table[key]);
        cache.push_front(get_value);
        cache_table[key] = cache.begin();
        // cout << "After: "<<*cache_table[key] << endl;
        return get_value;
    }
}


int main(int argc, char **argv){
    
    LRU_cache cache1(3);
    cache1.set("One");
    cache1.set("Two");
    string val = cache1.get("One"); // Should move "One" to the front
    cache1.set("Three");
    cache1.set("Four");
    val = cache1.get("One"); // One should be there in the cache
    val = cache1.get("Two"); // Two should not be there since cache is full and "Two" is the last least used
    cache1.set("Five");
    


//------------------------------------------------------------------------------------------------------
    cout << "----------END OF MAIN----------" << endl << endl;
    return 0;
}