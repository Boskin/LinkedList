#include <iostream>
#include "list.hpp"

using std::cout;
using std::cin;

void reverseList(List<int>& list);

int main() {
    List<int> numbers;
    int size;
    int num;
    
    cout << "How many numbers would you like to enter: ";
    cin >> size;
    
    while(size > 0) {
        size--;
        cout << "Number: ";
        cin >> num;
        numbers.add(num);
    }
    
    if(numbers.size() > 0) {
        reverseList(numbers);
        
        cout << "In reverse order:\n";
        
        for(Iterator<int> i(&numbers); i.valid(); i++)
            cout << i.get() << '\n';
    }
    
    return 0;
}

void reverseList(List<int>& list) {
    int counter = 0;
    for(Iterator<int> i(&list), j(&list, list.size() - 1); counter < list.size() / 2; i++, j--, counter++) {
        int temp = i.get();
        i.get() = j.get();
        j.get() = temp;
    }
}
