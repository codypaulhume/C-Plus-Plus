#include <iostream>
#include <unordered_map>

using namespace std;

class Node{
    public:
        string value;
        // Need the key so we know what to remove from the map
        string key;
        Node* next;
        Node* prev;

    Node(string key, string value){
        this->key = key;
        this->value = value;
        next = nullptr;
        prev = nullptr;
    }
};

class DLL{
    public:
        Node* head;
        Node* tail;
        int length;

    DLL(){
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    ~DLL(){
        Node* temp = head;

        while(head){
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void addToFrontList(string key, string value){
        Node* newNode = new Node(key, value);
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if(length == 0){
            head = newNode;
            tail = newNode;

        }else{
            head->prev = newNode;
            newNode->next = head;
            head = head->prev;
        }
        //Update length
        length++;
        
    }

    void printDLL(){
        Node* temp = head;
        while(temp != nullptr){
            cout << temp->value << endl;
        }
    }

    void remove(string value){
        if(length == 0) return;

        Node* temp = head;
        while(temp->value != value){
            temp = temp->next;
        }

        if(length == 1){
            head = nullptr;
            tail = nullptr;
            delete temp;
        }


        if(length > 1){
            if(temp == head){
                head = head->next;
                head->prev = nullptr;
            }else if(temp == tail){
                tail = tail->prev;
                tail->next = nullptr;
            }else{
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
        }
        delete temp;
        length--;
    }

    void printList(){
        Node* temp = head;
        while(temp != nullptr){
            cout << temp->value << "->";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

};

class LRUcache{
    public:
        unordered_map<string, string> myMap;
        DLL* myDLL = new DLL();
        int capacity;

    LRUcache(int capacity){
        this->capacity = capacity;
    }

    void set(string key, string value){
        // If found
        if(myMap.find(key) != myMap.end()){
            // Update the value in the map
            myMap[key] = value;
            // Remove the node and add new node to the front
            myDLL->remove(value);
            myDLL->addToFrontList(key, value);
        }else{
            myMap[key] = value;
            myDLL->addToFrontList(key, value);

            // Updating both structures
            if(myMap.size() > capacity){
                Node* toDelete = myDLL->tail;
                // Remove from DLL
                myDLL->remove(toDelete->value);
                // Remove from map
                myMap.erase(toDelete->key);
            }
        }
    }

    void get(string key){
        // Note for next code sesh. If it exists, then I can return the value. So maybe change the function from void to string. 
        // If not found, return null or string that says not found.
        if(myMap.find(key) != myMap.end()){
            // Return the value
            string temp = myMap[key];
            cout << "Found value: " << temp << endl;
            // Update the DLL
            myDLL->remove(temp);
            myDLL->addToFrontList(key, temp);
        }else{
            cout << "Value not found. Run the set function to add." << endl;
        }
    }
};

int main(){
    LRUcache cache(3);

    cache.set("A", "apple");
    cache.set("B", "banana");
    cache.set("C", "cherry");
    cache.set("D", "strawberry");
    cache.set("E", "elderberry");

    cache.myDLL->printList();
    cache.get("C");

    cout << "After get..." << endl;
    cache.myDLL->printList();
    
}