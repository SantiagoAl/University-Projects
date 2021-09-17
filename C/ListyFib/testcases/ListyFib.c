// Alex Santiago
// NID: al625608
// COP 3502, Summer 2018

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListyFib.h"
#include <limits.h>

ListyInt *new_linked_list(void);
Node *new_node(int data);
Node *destroy_linked_list(Node *head);
void insert(ListyInt *listy, int data);

// This functions takes two linked lists that represent integers in reverse order, adds them together
// and returns a pointer to the resultant linked list, which is also in reverse order.
ListyInt *listyAdd(ListyInt *p, ListyInt *q){
    
    ListyInt *sum_list = NULL;
    Node *temp1, *temp2, *tail;
    int count, carry, sum, i;
    
    if(p == NULL || q == NULL){
        return NULL;
    }
    
    sum_list = new_linked_list();
    
    if(sum_list == NULL){
        return NULL;
    }
    
    temp1 = p->head;
    temp2 = q->head;
    
    carry = 0;
    count = 0;
    
    // This loops adds each digit in the list together, it accounts for the lists possibly not being
    // the same length. While it loops it also accounts for carry after the addition of two digits,
    // as well as incrementing the counter each time which will be the length of our new linked list.
    while((temp2 != NULL) || temp1 != NULL){
        sum = carry + (temp1? temp1->digit: 0) + (temp2? temp2->digit: 0);
        
        carry = (sum >= 10) ? 1 : 0;
        sum %= 10;
        
        if(sum_list->head == NULL){
            sum_list->head = tail = new_node(sum);
        }else{
            tail->next = new_node(sum);
            tail = tail->next;
        }
        
        if(temp1) temp1 = temp1->next;
        if(temp2) temp2 = temp2->next;
        
        count++;
    }
    
    if(carry > 0){
        tail->next = new_node(carry);
        tail = tail->next;
        count++;
    }
    
    sum_list->length = count;
    
    return sum_list;
}

// This functions sends the head of the list to another function to destroy all the nodes, once
// that is complete it comes back and frees it.
ListyInt *destroyListyInt(ListyInt *listy){
    
    if(listy == NULL){
        return NULL;
    }
    
    destroy_linked_list(listy->head);
    
    free(listy);
    
    return NULL;
}

// This function takes a string as an input, turns it into a dynamically allocated linked list and
// returns a pointer to the struct.
ListyInt *stringToListyInt(char *str){
    
    int length, i, n, counter;
    ListyInt *str_to_int;
    Node *temp;
    char *empty_string = " ";
    
    if(str == NULL){
        return NULL;
    }
    
    str_to_int = new_linked_list();
    
    if(str_to_int == NULL){
        return NULL;
    }
    
    length = strlen(str);
    counter = 0;
    
    // This will loop through the string passed to the function, starting at the end of the string.
    // As it loops it takes the elements of the string converting them to integers, and creating
    // nodes in the new linked list.
    for(i = length - 1; i >= 0; i--){
        if(strcmp(&str[i], empty_string) == 0){
            n = 0;
            if(str_to_int->head == NULL){
                str_to_int->head = new_node(n);
                temp = str_to_int->head;
                counter++;
            }else{
                temp->next = new_node(n);
                temp = temp->next;
                counter++;
            }
        }else{
            n = str[i] - '0';
            if(str_to_int->head == NULL){
                str_to_int->head = new_node(n);
                temp = str_to_int->head;
                counter++;
            }else{
                temp->next = new_node(n);
                temp = temp->next;
                counter++;
            }
        }
    }
    
    str_to_int->length = counter;
    
    return str_to_int;
}

// This function takes in a linked list as an input and converts it to a dynamically allocated
// string array.
char *listyIntToString(ListyInt *listy){
    
    char *array;
    int i;
    
    if(listy == NULL || listy->head == NULL){
        return NULL;
    }
    
    array = malloc(sizeof(char) * (listy->length + 1));
    
    if(array == NULL){
        return NULL;
    }
    
    i = listy->length - 1;
    // While the linked list is not NULL it takes the digits contained in the linked list and converts
    // them to characters, storing them in the array.
    while(listy->head != NULL){
        array[i--] = listy->head->digit + '0';
        listy->head = listy->head->next;
    }
    
    return array;
}

// This functions takes an unsined int as a paramter and extracts the digis, while also inserting them
// into a dynamically allocated linked list
ListyInt *uintToListyInt(unsigned int n){
    
    ListyInt *uintListy;
    Node *temp;
    int remainder, counter;
    
    if(n > UINT_MAX){
        return NULL;
    }
    
    uintListy = new_linked_list();
    
    if(uintListy == NULL){
        return NULL;
    }
    
    // If n is less than 10 it will creat a linked list with just n because it is already down to one
    // digit and return a pointers to the struct
    if(n < 10){
        if(uintListy->head == NULL){
            uintListy->head = new_node(n);
            uintListy->length++;
        }
        return uintListy;
    }
    
    counter = 0;
    
    // This while loop extracts the digits of the unsigned integer, inserting them into the linked
    // list. It keeps looping until the integer is down to its last digit, inserts it into the list
    // adn breaks out.
    while(1){
        remainder = n % 10;
        
        if(uintListy->head == NULL){
            uintListy->head = new_node(remainder);
            temp = uintListy->head;
            counter++;
        }else if(n < 10){
            temp->next = new_node(remainder);
            counter++;
            break;
        }else{
            temp->next = new_node(remainder);
            temp = temp->next;
            counter++;
        }
        n /= 10;
    }
    
    uintListy->length = counter;
    
    return uintListy;
}

//This function takes an unsigned integer represented as a linked list and returns an allocated pointer
// to that integer.
unsigned int *listyIntToUint(ListyInt *listy){
    
    unsigned int *p, *result, Ans;
    int i, j;
    
    if(listy == NULL){
        return NULL;
    }
    // If the length of the list is greater than 10 the integer is to large to be an unsigned int/
    if(listy->length > 10){
        return NULL;
    }
    
    p = malloc(sizeof(unsigned int) * listy->length);
    
    if(p == NULL){
        return NULL;
    }
    
    result = malloc(sizeof(unsigned int));
    
    if(result == NULL){
        return NULL;
    }
    
    i = listy->length - 1;
    // This while loop goes through the digits in the list linked and stores them in reverse order
    // in the unsigned int array p.
    while(listy->head != NULL){
        p[i--] = listy->head->digit;
        listy->head = listy->head->next;
    }
    
    Ans = 0;
    // This for loop takes the elements in p and store them into a variable, checking as it goes not
    // to cause overflow if the numbers represented by the list is to large to be an unsigned int.
    for(j = 0; j < listy->length; j++){
        
        if(Ans > UINT_MAX / 10){
            return NULL;
        }else{
            Ans *= 10;
        }
        if(Ans > UINT_MAX - p[j]){
            return NULL;
        }else{
            Ans += p[j];
        }
    }
    result[0] = Ans;
    
    free(p);
    p = NULL;
    
    return result;
}
// This function takes a linked list and adds one to it.
void plusPlus(ListyInt *listy){
    
    int carry, sum;
    
    if(listy == NULL){
        return;
    }
    
    carry = 1;
    
    while(listy->head != NULL){
        sum = carry + listy->head->digit;
        
        carry = (sum >= 10) ? 1 : 0;
        
        sum %= 10;
        
        listy->head->digit = sum;
        
        listy->head = listy->head->next;
    }
    
    if(carry > 0){
        listy->head->next = new_node(carry);
    }
    
}

// This function will take an unsigned integer and calculate the the fiboncacci sequence up to that
// term.
ListyInt *fib(unsigned int n){
    
    ListyInt *a, *b, *result, *temp = NULL;
    int i, count, data1, data2;
    
    if(n > UINT_MAX){
        return NULL;
    }
    
    data1 = 0;
    data2 = 1;
    // If the term passed to this functin is less than two it will return a linked list containing
    // n.
    if(n < 2){
        temp = new_linked_list();
        if(temp == NULL){
            return NULL;
        }
        temp->head = new_node(n);
        temp->length++;
        
        return temp;
    }
    
    a = new_linked_list();
    
    if(a == NULL){
        return NULL;
    }
    
    b = new_linked_list();
    
    if(b == NULL){
        return NULL;
    }
    
    //temp = new_linked_list();
    
    /*if(temp == NULL){
        return NULL;
    }*/
    
    a->head = new_node(data1);
    b->head = new_node(data2);
    //temp->head = new_node(data1);
    
    // This for loop loops from two all the way to the nth term passed to this function. As it loops
    // through it adds the fist two lists together, storing the result of thos two linked list. Then
    // it equates the first list to the second, the second to the resultant list and keeps going until
    // it reaches the nth term.
    for(i = 2; i <= n; i++){
        result = listyAdd(a, b);
        a = destroyListyInt(a);
        //a = listyAdd(temp, b);
        a = b;
        //b = destroyListyInt(b);
        //free(b);
        //b = listyAdd(temp, result);
        b = result;
        //result = destroyListyInt(result);
        //free(result);
    }
    
    a = destroyListyInt(a);
    //b = destroyListyInt(b);
    //temp = destroyListyInt(temp);
    
    return b;
}

// This function will create the new nodes in the linked lists.
Node *new_node(int data){
    
    Node *new_node = malloc(sizeof(Node));
    
    new_node->digit = data;
    new_node->next = NULL;
    
    return new_node;
}
// This is a function to destroy the linked list.
Node *destroy_linked_list(Node *head){
    
    Node *temp, *current;
    
    if(head == NULL){
        return NULL;
    }
    
    current = head;
    
    while(current != NULL){
        temp = current->next;
        free(current);
        current = temp;
    }
     
    return NULL;
}
// This function creates a new linked list struct.
ListyInt *new_linked_list(void){
    return calloc(1, sizeof(ListyInt));
}
// This function returns how hard I found the assignment.
double difficultyRating(void){
    return 4.5;
}
// This function will return the amount of hours I spent on the assignment.
double hoursSpent(void){
    return 40;
}
