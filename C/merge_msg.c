#include <stdlib.h>
#include <string.h>

typedef struct msg {
    char* text;
    struct msg* next;
} Msg;

void merge_msg(Msg* books) {
    if (books == NULL) {
        return;
    }
    Msg* cur = books;
    while (cur->next != NULL) {
        Msg* left = cur;
        Msg* right = cur->next;
        int new_len = strlen(left->text) + strlen(right->text) + 1;
        char* new_text = malloc(new_len);
        strcpy(new_text, left->text);
        strcat(new_text, right->text);
        free(left->text);
        free(right->text);
        left->text = new_text;
        left->next = right->next;
        free(right);
        cur = left->next;
    }
}

int main() {
    char* arr[3] = {"CSE", "333", "\n"};
    Msg* msgs;
    Msg* cur = msgs;
    for (int i = 0; i < 3; i++) {
        cur = (Msg*) malloc(sizeof(Msg));
        cur->text = (char*) malloc(strlen(arr[i]) + 1);
        strcpy(cur->text, arr[i]);
        cur = cur->next;
    }
    merge_msg(msgs);
    // free list
}