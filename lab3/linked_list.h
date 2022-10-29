//
// Created by angel on 2022-05-10.
//

#ifndef LAB3_LINKED_LIST_H
#define LAB3_LINKED_LIST_H

#include <iostream>
#include <memory>

template<typename T>
class linked_list{
public:
    linked_list():head(nullptr), tail(nullptr){};
    ~linked_list() { clean(); }
    void push_back(T value);
    void clean();
    [[nodiscard]] size_t size() const;
    T operator[](int pos) const;
    friend std::ostream& operator<<(std::ostream& out, const linked_list<int>& src);
private:
    struct node{
        explicit node(T value):value(value),next(nullptr){};
        T value;
        std::shared_ptr<node> next;
    };
    std::shared_ptr<node> head;
    std::shared_ptr<node> tail;
};

template<typename T>
T linked_list<T>::operator[](int pos) const {
    int counter = 0;
    for(node* temp = head.get(); temp != nullptr; temp = temp->next.get(), counter++) {
        if (counter == pos) {
            return temp->value;
        }
    }
    return tail->value;
}

template<typename T>
void linked_list<T>::push_back(T value) {
    auto temp = std::make_shared<node>(value);
    if(head == nullptr){
        head = temp;
    }else{
        tail->next = temp;
    }
    tail = std::move(temp);
}

template<typename T>
size_t linked_list<T>::size() const {
    size_t size = 0;
    for(node* temp = head.get(); temp != nullptr; temp = temp->next.get()){
        size++;
    }
    return size;
}

std::ostream& operator<<(std::ostream &out, const linked_list<int> &src) {
    if(!src.size()){
        out << "- ";
    }else{
        for(int i = 0; i < src.size(); i++){
            out << src[i] << " ";
        }
    }
    return out;
}

template<typename T>
void linked_list<T>::clean() {
    while(head){
        head = std::move(head->next);
    }
}

#endif //LAB3_LINKED_LIST_H
