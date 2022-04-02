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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        //可以学习参考这个高票代码用指针代替头结点的做法。
        // ListNode** t1 = &head, *t2 = head;
        // for(int i = 1; i < n; ++i)
        // {
        //     t2 = t2->next;
        // }
        // while(t2->next != NULL)
        // {
        //     t1 = &((*t1)->next);
        //     t2 = t2->next;
        // }
        // *t1 = (*t1)->next;
        // return head;

        ListNode preHead(0, head);
        ListNode* fst = &preHead;
        ListNode* sec = head;
        for(int i=1;i<n; ++i){
            sec = sec->next;
        }
        while(sec->next)
        {
            fst = fst->next;
            sec = sec->next;
        };
        fst->next = fst->next->next;
        return preHead.next;
    }
};