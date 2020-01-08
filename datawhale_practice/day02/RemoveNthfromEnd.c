/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
     struct ListNode* dummyHead = (struct ListNode *)malloc(sizeof(struct ListNode));
        dummyHead->next = head;

        struct ListNode* p = dummyHead;
        struct ListNode* q = dummyHead;
        for( int i = 0 ; i < n + 1 ; i ++ ){
            q = q->next;
        }

        while(q){
            p = p->next;
            q = q->next;
        }

        struct ListNode* delNode = p->next;
        p->next = delNode->next;
        free(delNode);

        struct ListNode* retNode = dummyHead->next;
        free(dummyHead);

        return retNode;

}