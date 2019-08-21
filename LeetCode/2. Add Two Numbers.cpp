/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
       ListNode* head = new ListNode(-1);
        ListNode* rear = head;
        int carry = 0;
        while(l1 || l2){
            int num = (l1?l1->val:0) + (l2?l2->val:0) + carry;
            carry = num / 10;
            rear->next = new ListNode(num % 10);
            rear = rear -> next;
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }
        if(carry){
            rear->next = new ListNode(carry);
        }
        //rear = head->next;
        //delete head;
        return head->next;
    }
};
// 测试程序
/*
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
 
class Solution {
public:
    static ListNode *createList(size_t x){
        ListNode *beg ,*ptr;
        beg = new ListNode(x%10);
        ptr = beg;
        x/=10;
        while(x){
            ptr->next = new ListNode(x%10);
            ptr = ptr->next;
            x/=10;
        }
        return beg;
    }
    static ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode(-1);
        ListNode* rear = head;
        int carry = 0;
        while(l1 || l2){
            int num = (l1?l1->val:0) + (l2?l2->val:0) + carry;
            carry = num / 10;
            rear->next = new ListNode(num % 10);
            rear = rear -> next;
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }
        if(carry){
            rear->next = new ListNode(carry);
        }
        rear = head->next;
        delete head;
        return rear;
    }
    
    static void rrread(ListNode* c){
        while(c!=NULL){
            cout<<c->val<<" ";
            c=c->next;
        }
        return;
    }
    
};
int main(){
    ListNode* a = Solution::createList(342);
    cout<<"L1: ";
    Solution::rrread(a);
    ListNode* b = Solution::createList(465);
    cout<<"\nL2: ";
    Solution::rrread(b);
    ListNode* c = Solution::addTwoNumbers(a,b);
    cout<<"\nSUM: ";
    Solution::rrread(c);


    return 0;
}
*/