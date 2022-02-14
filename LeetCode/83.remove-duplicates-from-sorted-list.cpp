/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* curr = head;
        ListNode* rear = head;
        if(!curr) return nullptr;
        if(!curr->next) return head;
        while(rear){
            if(curr->val != rear->val){
                curr->next = rear;
                curr = curr->next;
            }
            rear = rear->next;
        }
        curr->next = nullptr;
        return head;
    }
};