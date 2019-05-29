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


	ListNode* addNodeInNum(int value, ListNode* head, int num){
		ListNode* current = head;
		ListNode* temp = nullptr;
		ListNode* NewListNode = new ListNode(value);
		if(num == 0){
			NewListNode->next = head;
			head = NewListNode;
		} else{
			current = findNumNode(current, num-1);
			temp = current->next;
			current->next = NewListNode;
			NewListNode->next = temp;
		}
		return head;
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
			cout << head->value << " ";
			head = head->next;
		}
		cout << endl;
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

    ListNode *detectCycle2(ListNode *head) {
        ListNode *slow = head, *fast = head;

        while(slow){
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) break;
        }
        fast = head;
        while(fast){
            slow = slow->next;
            fast = fast->next;
            if(slow == fast) return slow;
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

    void insertElementWithSorted(ListNode *head, int value) {
        ListNode* NewListNode = new ListNode(value);
        ListNode* current = head;
        ListNode* pred = nullptr;
        while (current) {
            if(current->value > value){
                pred->next = NewListNode;
                NewListNode->next = current;
                break;
            }
            pred = current;
            current = current->next;
        }
    }


    // if we want to re-direction Nth "->"
    // step0: setting pre、cur、pas
    // step1: cancel pre->next
    // repeat
    // step2: re-direction cur->next
    // step3: "pre" move next
    // step4: "cur" move next
    // step5: "pas" move next
    // ......
    // until pas =nullptr;

    // 0: 1(pre) -> 50(cur) 	-> 30(pas)		-> 100
    // 1: 1(pre)    50(cur) 	-> 30(pas) 		-> 100
    // repeat
    // 2: 1(pre) <- 50(cur) 	   30(pas) 		-> 100
    // 3: 1	   	 <- 50(cur、pre)   30(pas) 		-> 100
    // 4: 1	  	 <- 50(pre)  	   30(pas、cur) -> 100
    // 5: 1	  	 <- 50(pre)  	   30(cur) 		-> 100(pas)
    // repeat
    // 6: 1		 <- 50(pre)		<- 30(cur)		   100(pas)
    // 7: 1		 <- 50			<- 30(cur、pre)	   100(pas)
    // 8: 1		 <- 50			<- 30(pre)		   100(cur、pas)	
    // 9: 1		 <- 50			<- 30(pre)		   100(cur)		(pas)
    // pas = nullptr, re-direction cur->next = pre

    ListNode* reverse(ListNode *head){
    	ListNode *current = head->next;
    	ListNode *previous = head;
    	ListNode *past = head->next->next;
    	previous->next = nullptr;
    	while (past != nullptr) {
    		current->next = previous;
    		previous = current;
    		current = past;
    		past = past->next;
    	}
    	current->next = previous;
    	return current;
    }

    // first loop
    // 1 -> 2 -> 3 -> 4 -> 5
    // c
    // 1 -> 2 -> 3 -> 4 -> 5
    // c    pas
    // 1    2 -> 3 -> 4 -> 5
    // c    pas
    // 1    2 -> 3 -> 4 -> 5
    // c,pr pas
    // 1    2 -> 3 -> 4 -> 5
    // pr   pas,c
    // 
    // 1    2 -> 3 -> 4 -> 5
    // pr	c    pas
    // 1 <- 2    3 -> 4 -> 5
    // pr 	c 	 pas
    // 1 <- 2    3 -> 4 -> 5
    //		c,prepas
    // 1 <- 2    3 -> 4 -> 5
    //		pre  pas,c
    // ...
    // ...
    // ...
    // secound loop
    // 3 -> 4 -> 5
    // ...
    // ...
    // 3 <- 4    5
    //      pre  pas,c
    // 
    // ...
    // ...
    // third loop
    // 5	 n/a
    // pre,c pas
    // 
    // return 5, and the head of second loop(3) will point to 5
    // return 4
    // and the head of first loop(1) will point to 4
    // 2 -> 1 -> 4 -> 3 -> 5

    // step1: only set head
    // step2: reverse
    // step3: recur, "xth head" will point to the "xth+1 pre",
    ListNode* reverseKNode(ListNode *head, int k){
    	// only set head
    	ListNode* current = head;
    	ListNode* past = nullptr;
    	ListNode* pre = nullptr;
    	int count = 0;

    	// update past(current->next)
    	// current re-direction
    	// update pre
    	// update currnet
    	while(current != nullptr && count < k){ // re-direction one group in once recur(count < k), if the num of element < k(current != nullptr)
    		past = current->next;
    		current->next = pre;
    		pre = current;
    		current = past;
    		count++;
    	}
    	// xth: times of recur
    	// "xth head" will point to the "xth+1 pre"
    	// (past != nullptr) means: it's not the last group
    	if (past != nullptr) head->next = reverseKNode(past, k);
    	return pre;
    }
    ListNode* removeKNode(ListNode* head, int k){
        ListNode* current = head;

        if(k == 1){
            head = head->next;
            return head;
        }
        int count = 1;
        ListNode* previous = current;
        current = current->next;
        while(current){
            count++;
            if(count == k){
                previous->next = current->next;
                current = current->next;
            }else{
                previous = current;
                current = current->next;
            }
        }
        return head;
    }
    // 7    6   5   4   3   2   1
    // slow         fast
    //              slow        fast
    ListNode* removeLastKNode(ListNode* head, int k){
        int count = 0;
        ListNode* slow = head;
        ListNode* fast = head;
        while(count < k){
            fast = fast->next;
            count++;
        }
        if(fast){
            while(fast->next){
                fast = fast->next;
                slow = slow->next;
            }
            slow->next = slow->next->next;
        }else{ // if kth node before first node
            head = head->next;
        }
        return head;
    }

    ListNode* mergeSort(ListNode* head){
        if(head == nullptr || head->next == nullptr) return head;
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* previous = head;
        while(fast != nullptr && fast->next != nullptr){
            previous = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        previous->next = nullptr;
        // 每次都把LList分一半
        return mergeLLists(mergeSort(head),mergeSort(slow));
    }

    ListNode* mergeLLists(ListNode* head, ListNode* head2){
        // 有兩個LList進來，每次return value小的那個node，並把
        // 這個小的node的next指向下一個小的node....依序
        if(head==nullptr) return head2;
        if(head2==nullptr) return head;
        if(head->value < head2->value){
            head->next = mergeLLists(head->next, head2);
            return head;
        }
        if(head->value > head2->value){
            head2->next = mergeLLists(head, head2->next);
            return head2;
        }
    }
};



int main(){
	vector<int> TestVec{10,6,1,2,9,4,5};
	LinkedList L;
	ListNode* HeadLinkedList = L.vecToLinkedList(TestVec);

    //vector<int> TestVec2{11,26,13,4,3,7,51};
    //LinkedList L2;
    //ListNode* HeadLinkedList2 = L.vecToLinkedList(TestVec2);

    HeadLinkedList = L.mergeSort(HeadLinkedList);
    //HeadLinkedList = L.removeLastKNode(HeadLinkedList, 5);
	//L.addNode(13, HeadLinkedList);
	//cout << "original: ";
	//L.printLinkedList(HeadLinkedList);
	//HeadLinkedList = L.addNodeInNum(20, HeadLinkedList, 0);
	//cout << "insert node: ";
	//L.printLinkedList(HeadLinkedList);
	//HeadLinkedList = L.reverse(HeadLinkedList);
	//cout << "reverse: ";
	//L.printLinkedList(HeadLinkedList);
    //L.printLinkedList(HeadLinkedList);
    //L.insertElementWithSorted(HeadLinkedList, 3);
    //L.printLinkedList(HeadLinkedList);

	//HeadLinkedList = L.reverseKNode(HeadLinkedList, 3);
	L.printLinkedList(HeadLinkedList);

	cout << "hasCycle(before makeCircle): " << L.hasCycle(HeadLinkedList) << endl;
	if(L.hasCycle(HeadLinkedList)){
		cout << "detectCycle: " << L.detectCycle(HeadLinkedList)->value << endl;
	}
	L.makeCircleLinkedList(HeadLinkedList, 2);
	cout << "hasCycle(after makeCircle): " << L.hasCycle(HeadLinkedList) << endl;
	if(L.hasCycle(HeadLinkedList)){
		cout << "detectCycle: " << L.detectCycle(HeadLinkedList)->value << endl;
        cout << "detectCycle2: " << L.detectCycle2(HeadLinkedList)->value << endl;
	}
	return 0;
}