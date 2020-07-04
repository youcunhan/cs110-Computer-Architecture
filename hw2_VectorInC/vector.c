#include"vector.h"
#include<string.h>
#include<stdlib.h>



/* Constructor, set CAPACITY and ELEMENT_SIZE to VECTOR, alloc memory for DATA */
int vector_init(Vector* vector, size_t capacity, size_t element_size){
    /*check invaid argyument*/
    if(vector == NULL || element_size==0){
        return VECTOR_ERROR;
    }
    /*check if capacity is too small*/
    if(capacity < VECTOR_MINIMUM_CAPACITY){
        capacity = 2;
    }
    /*assign*/
    vector->capacity = capacity;
    vector->element_size = element_size;
    vector->size = 0;
    vector->data = malloc(element_size * capacity);
    /*check if malloc succeeds*/
    if(vector->data == NULL){
        return VECTOR_ERROR;
    }
    /*return sucess*/
    return VECTOR_SUCCESS;
}

/* Copy Constructor, destination should be an **UNINITIALIZED** vector.
   You should copy the memory, instead of changing the pointers only. */
int vector_copy(Vector* destination, Vector* source){
    /*check invaid argyument*/
    if(destination == NULL || source == NULL){
        return VECTOR_ERROR;
    }
    /*assign*/
    destination->capacity = source->capacity;
    destination->element_size = source->element_size;
    destination->size = source->size;
    destination->data = malloc(destination->element_size * destination->capacity);
    /*check if malloc succeeds*/
    if(destination->data == NULL){
        return VECTOR_ERROR;
    }
    /*copy the data*/
    memcpy(destination->data, source->data, destination->element_size * destination->size);
    return VECTOR_SUCCESS;
}

/* Destructor, please free all memory allocated */
int vector_destroy(Vector* vector){
    /*check if malloc succeeds*/
    if(vector == NULL || vector->data == NULL){
        return VECTOR_ERROR;
    }
    /*free the memory*/
    free(vector->data);
    return VECTOR_SUCCESS;
}

/* Insertion */
int vector_push_back(Vector* vector, void* element){
    /*check invalid argument*/
    if(vector == NULL || element == NULL || vector->data == VECTOR_UNINITIALIZED){
        return VECTOR_ERROR;
    }
    if(vector->size == vector->capacity){
        /*grow*/
        void *temp = malloc(vector->capacity * vector->element_size);
        memcpy(temp, vector->data, vector->capacity * vector->element_size);
        /*free the previous data*/
        free(vector->data);
        vector->data = malloc(VECTOR_GROWTH_FACTOR * vector->capacity * vector->element_size);
        memcpy(vector->data, temp, vector->capacity * vector->element_size);
        /*free the temp pointer*/
        free(temp);
        /*check if grow succeeds*/
        if(vector->data == NULL){
            return VECTOR_ERROR;
        }
        /*change capacity*/
        vector->capacity *= VECTOR_GROWTH_FACTOR;
    }
    memcpy((char*)vector->data + vector->size * vector->element_size, element, vector->element_size);
    /*change size*/
    vector->size++;
    
    return VECTOR_SUCCESS;
}
int vector_push_front(Vector* vector, void* element){
    /*just call insert*/
    return vector_insert(vector, 0, element);
}
/* Insert ELEMENT to INDEX, move all elements which index > INDEX right by one time */
int vector_insert(Vector* vector, size_t index, void* element){
    /*check invalid argument*/
    if(vector == NULL || element == NULL || index > vector->size || vector->data == VECTOR_UNINITIALIZED){
        return VECTOR_ERROR;
    }
    /*give it to push*/
    else if(index == vector->size){
        vector_push_back(vector,element);
    }
    /*normal situation*/
    else{
        void* moveAddr;
        if(vector->size == vector->capacity){
            /*grow*/
            void *temp = malloc(vector->capacity * vector->element_size);
            memcpy(temp, vector->data, vector->capacity * vector->element_size);
            /*free the previous data*/
            free(vector->data);
            vector->data = malloc(VECTOR_GROWTH_FACTOR * vector->capacity * vector->element_size);
            memcpy(vector->data, temp, vector->capacity * vector->element_size);
            /*free the temp pointer*/
            free(temp);
            /*check if grow succeeds*/
            if(vector->data == NULL){
                return VECTOR_ERROR;
            }
            /*change capacity*/
            vector->capacity *= VECTOR_GROWTH_FACTOR;
        }
        /*move all elements which index >= INDEX*/
        moveAddr = (char*)vector->data + index * vector->element_size;
        memmove((char*)moveAddr + vector->element_size, moveAddr, (vector->size - index) * vector->element_size);
        memcpy(moveAddr, element, vector->element_size); 
        vector->size++;
    }
    /*return sucess*/
    return VECTOR_SUCCESS;
}
/* Just assign VECTOR[INDEX] = ELEMENT, you should not move any elements */
int vector_assign(Vector* vector, size_t index, void* element){
    /*check invalid argument*/
    if(vector == NULL || element == NULL ||index >= vector->size || vector->data == VECTOR_UNINITIALIZED){
        return VECTOR_ERROR;
    }
    /*normal situation*/
    else{
        memcpy((char*)vector->data + index * vector->element_size, element, vector->element_size);
        /*check if copy succeeds*/
        if (vector->data == VECTOR_UNINITIALIZED){
            return VECTOR_ERROR;
        }
        return VECTOR_SUCCESS;
    }
}

/* Deletion */
/* Delete the right-most element */
int vector_pop_back(Vector* vector){
    return vector_erase(vector, vector->size - 1);
}
/* Delete element at INDEX = 0, move all other elements left by one */
int vector_pop_front(Vector* vector){
    return vector_erase(vector, 0);
}
/* Delete element at INDEX, move all rhs elements left by one */
int vector_erase(Vector* vector, size_t index){
    size_t i;
    /*check invalid argument*/
    if(vector == NULL || vector->size == 0 || vector->data == VECTOR_UNINITIALIZED || index >= vector->size){
        return VECTOR_ERROR;
    }
    /*move all rhs elements left by one*/
    for (i = 0; i < vector->size - index - 1; i++)
    {
        memcpy((char *)vector->data + (index + i) * vector->element_size, vector_get(vector, index + i + 1), vector->element_size);
    }
    vector->size--;
    /*return sucess*/
    return VECTOR_SUCCESS;
}
/* Delete all elements in the vector */
int vector_clear(Vector* vector){
    /*check invalid argument*/
    if(vector == NULL || vector->data == VECTOR_UNINITIALIZED){
        return VECTOR_ERROR;
    }
    /*zero the size*/
    vector->size = 0;
    return VECTOR_SUCCESS;
}

/* Lookup */
/* Returns VECTOR[INDEX] */
void* vector_get(Vector* vector, size_t index){
    /*check invalid argument*/
    if(vector == NULL || vector->data == NULL || index >= vector->size){
        return NULL;
    }
    return (char*)vector->data + index * vector->element_size;
}
/* Returns VECTOR[0] */
void* vector_front(Vector* vector){
    return vector_get(vector, 0);
}

/* Returns VECTOR[-1] */
void* vector_back(Vector* vector){
    return vector_get(vector, vector->size - 1);
}

/* Information */
/* Returns size of VECTOR */
size_t vector_size(const Vector* vector){
    /*check invalid argument*/
    if(vector == NULL){
        return 0;
    }
    return vector->size;
}
/* Returns TRUE if VECTOR is empty(i.e. size == 0) */
bool vector_is_empty(const Vector* vector){
    /*check invalid argument*/
    if(vector == NULL){
        return false;
    }
    return vector->size == 0;
}

/* Memory management */
int vector_resize(Vector* vector, size_t new_size){
    /*check invalid argument*/
    if (vector == NULL || vector->data == VECTOR_UNINITIALIZED)
    {
        return VECTOR_ERROR;
    }
    /*grow when size > capacity*/
    while (vector->capacity < new_size)
    {
        /*grow*/
        void *temp = malloc(vector->capacity * vector->element_size);
        memcpy(temp, vector->data, vector->capacity * vector->element_size);
        /*free the previous data*/
        free(vector->data);
        vector->data = malloc(VECTOR_GROWTH_FACTOR * vector->capacity * vector->element_size);
        memcpy(vector->data, temp, vector->capacity * vector->element_size);
        /*free the temp pointer*/
        free(temp);
        /*check if grow succeeds*/
        if(vector->data == NULL){
            return VECTOR_ERROR;
        }
        /*change capacity*/
        vector->capacity *= VECTOR_GROWTH_FACTOR;
    }
    /*change size*/
    vector->size = new_size;
    return VECTOR_SUCCESS;
}

/* Iterators */
Iterator vector_begin(Vector* vector){
    Iterator begin;
    /*check invalid argument*/
    if(vector == NULL){
        begin.pointer = NULL;
        begin.element_size = 0;
        return begin;
    }
    /*assign*/
    begin.element_size = vector->element_size;
    begin.pointer = vector->data;
    /*return iter*/
    return begin;
}
Iterator vector_end(Vector* vector){
    Iterator end;
    /*check invalid argument*/
    if(vector == NULL){
        end.pointer = NULL;
        end.element_size = 0;
        return end;
    }
    /*assign*/
    end.element_size = vector->element_size;
    end.pointer = (char*)vector->data + vector->element_size * vector->size;
    /*return iter*/
    return end;
}
/* Returns an iterator points to vector[index] */
Iterator vector_iterator(Vector* vector, size_t index){
    Iterator iter;
    /*check invalid argument*/
    if(vector == NULL || index > vector->size){
        iter.pointer = NULL;
        iter.element_size = 0;
        return iter;
    }
    /*assign*/
    iter.element_size = vector->element_size;
    iter.pointer = (char*)vector->data + vector->element_size * index;
    /*return iter*/
    return iter;
}

/* Returns the element, similar to `operator *()' in C++ */
void* iterator_get(Iterator* iterator){
    /*check invalid argument*/
    if(iterator == NULL){
        return NULL;
    }
    return iterator->pointer;
}

/* Similar to `operator++()' in C++ */
void iterator_increment(Iterator* iterator){
    /*check invalid argument*/
    if(iterator == NULL || iterator->pointer == NULL){
        return;
    }
    iterator->pointer = (char*)iterator->pointer + iterator->element_size;
}
/* Similar to `operator--()' in C++ */
void iterator_decrement(Iterator* iterator){
    /*check invalid argument*/
    if(iterator == NULL || iterator->pointer == NULL){
        return;
    }
    iterator->pointer = (char*)iterator->pointer - iterator->element_size;
}
/* Similar to `operator==(Iterator second)' in C++ */
bool iterator_equals(Iterator* first, Iterator* second){
    /*check invalid argument*/
    if(second == NULL || first == NULL || first->pointer == NULL || second->pointer == NULL){
        return 0;
    }
    return (first->element_size == second->element_size && first->pointer == second->pointer);
}

/* Sort the vector in nondecreasing according to comparision function less.
     You can implement any sorting algorithm you want such as bubble sort 
	 or quick sort.	 There is no strict time or space limit. */
void vector_sort(Vector *vector, vector_less_func *less){
    /*initialize the loop condition*/
    size_t i;
    size_t j;
    void *temp;
    /*check invalid argument*/
    if(vector == NULL || less == NULL){
        return;
    }
    /*loop bubble sort*/
    for(i = 0;i < vector->size - 1;i++){
        for(j = 0;j < vector->size - i - 1;j++){
            /*get two pointer*/
            void *a = vector_get(vector, j);
            void *b = vector_get(vector, j + 1);
            /*if b < a*/
            if(less(b, a)){
                /*exchange them*/
                temp = malloc(vector->element_size);
                memcpy(temp, a, vector->element_size);
                memcpy(a, b, vector->element_size);
                memcpy(b, temp, vector->element_size);
                /*free the temp pointer*/
                free(temp);
            }
        }
    }
}