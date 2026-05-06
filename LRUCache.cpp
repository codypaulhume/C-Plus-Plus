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

    void addToFrontList(Node* node){

        if(length == 0){
            head = node;
            tail = node;

        }else{
            head->prev = node;
            node->next = head;
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

    void remove(Node* node){
        if(length == 0) return;

        Node* temp = head;
        while(temp != node){
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
        unordered_map<string, Node*> myMap;
        DLL* myDLL = new DLL();
        int capacity;

    LRUcache(int capacity){
        this->capacity = capacity;
    }

    void set(string key, string value){

        // If found
        if(myMap.find(key) != myMap.end()){
            // Update the value in the map
            myMap[key]->value = value;
            // Remove the node and add new node to the front
            myDLL->remove(myMap[key]);
            myDLL->addToFrontList(myMap[key]);
        }else{
            // Create node here and set it in the map
            Node* newNode = new Node(key, value);
            newNode->next = nullptr;
            newNode->prev = nullptr;

            myMap[key] = newNode;
            myDLL->addToFrontList(newNode);

            // Updating both structures
            if(myMap.size() > capacity){
                // Get LRU node (the tail)
                Node* LRU = myDLL->tail;
                myDLL->remove(LRU);
                myMap.erase(LRU->key);
            }
        }
    }

    void get(string key){
        // Note for next code sesh. If it exists, then I can return the value. So maybe change the function from void to string. 
        // If not found, return null or string that says not found.
        if(myMap.find(key) != myMap.end()){
            // Return the node
            Node* temp = myMap[key];
            cout << "Found value: " << temp->value << endl;
            // Update the DLL
            myDLL->remove(temp);
            myDLL->addToFrontList(temp);
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