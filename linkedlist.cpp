#include <iostream>
#include <vector>

using namespace std;

class ListNode {
public:
	int value;
	ListNode* next;
	ListNode(int a):value(a), next(nullptr){};
};

class LinkedList {
public:

	// function: find the end of linkedlist
	ListNode* findEndNode(ListNode* head){
		ListNode* current = head;
		while(current->next != nullptr){
			current = current->next;
		}
		return current;
	}

	// function: get the Xth node of linkedlist
	ListNode* findNumNode(ListNode* head, int num){
		ListNode* current = head;
		for(int i = 0; i < num; i++){
			current = current->next;
		}
		return current;
	}

	// function: add new node in the end of linkedlist
	void addNode(int value, ListNode* head){
		//cout << endl;
		ListNode* current = head;
		ListNode* NewListNode = new ListNode(value);
		current = findEndNode(current);
		current->next = NewListNode;
		//cout << current->value << endl;
	}

	// https://thispointer.com/create-a-singly-linked-list-from-an-array/?fbclid=IwAR0yYkYuIVgHtZYY1hVZIfIluHmfiBZlBLrvaPFOOGSjFXwla9UvffKITbk
	// function: 靠lastNodePtr->next = nodePtr & lastNodePtr = nodePtr在連結，nodePtr = nodePtr->next在traversal
	ListNode* vecToLinkedList(vector<int> input){
	    ListNode* nodePtr = nullptr;
	    ListNode* rootNodePtr = nullptr;
	    ListNode* lastNodePtr = nullptr;
	    for(int i = 0 ; i < input.size(); i++)
	    {
	        if(!nodePtr)
	        {
	            nodePtr = new ListNode(input[i]);
	            if(!rootNodePtr)					// in i = 0, set rootNodePtr
	                rootNodePtr = nodePtr;    
	            if(lastNodePtr)    
	                lastNodePtr->next = nodePtr;	// in i != 0, setting for linking the linkedlist
	        }
	        lastNodePtr = nodePtr;					// setting for linking the linkedlist
	        nodePtr = nodePtr->next;				// traversal: I want to point nodePtr->next to New ListNode when the next for count
	    }
	    return rootNodePtr;
	}

	// function: make circle linkedlist with assigned number
	// Input:
	//		StartNum: can assigned the first circle node
	void makeCircleLinkedList(ListNode *head, int StartNum){
		ListNode* current = head;
		ListNode* current2 = head;
		current = findEndNode(current);
		current2 = findNumNode(current2, StartNum);
		cout << "end: " << current->value << " num: " << current2->value << endl;
		current->next = current2;
	}

	void printLinkedList(ListNode *head){
		while(head!=nullptr){
			cout << head->value << endl;
			head = head->next;
		}
	}
	// Time:  O(n)
	// Space: O(1)
	// function: 
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;

        while (fast && fast->next) {
            slow = slow->next, fast = fast->next->next;
            if (slow == fast) {  // There is a cycle.
                slow = head;
                // Both pointers advance at the same time.
                while (slow != fast) {
                    slow = slow->next, fast = fast->next;
                }
                return slow;  // slow is the begin of cycle.
            }
        }
        return nullptr;  // No cycle.
    }

	// Time:  O(n)
	// Space: O(1)
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;

        while (fast && fast->next) {
            slow = slow->next, fast = fast->next->next;
            if (slow == fast) {  // There is a cycle.
                return true;
            }
        }
        return false;  // No cycle.
    }
};

int main(){
	vector<int> TestVec{1,3,5,2,7,8,9,6};
	LinkedList L;
	ListNode* HeadLinkedList = L.vecToLinkedList(TestVec);
	L.addNode(13, HeadLinkedList);
	L.printLinkedList(HeadLinkedList);
	cout << "hasCycle(before makeCircle): " << L.hasCycle(HeadLinkedList) << endl;
	if(L.hasCycle(HeadLinkedList)){
		cout << "detectCycle: " << L.detectCycle(HeadLinkedList)->value << endl;
	}
	L.makeCircleLinkedList(HeadLinkedList, 4);
	cout << "hasCycle(after makeCircle): " << L.hasCycle(HeadLinkedList) << endl;
	if(L.hasCycle(HeadLinkedList)){
		cout << "detectCycle: " << L.detectCycle(HeadLinkedList)->value << endl;
	}
	return 0;
}