/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque(){
    n1 = 0;
    n2 = 0;
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
    data.push_back(newItem);
    n2++;
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    T val = data[n1];
    // data.erase(data.begin());
    n1++;
    if (n1 - 1 >= n2 - n1 - 1) {
        int newSize = n2 - n1;
        vector<T> newV;
        newV.resize(newSize);
        // int* p = data.data();

        for (int i = n1; i < n2; i++) {
            newV[i - n1] = data[i];
        }
        n1 = 0;
        n2 = newSize;
        data = newV;
    }
    return val;

}
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    T val = data[n2 - 1];
    data.pop_back();
    n2--;
    if (n1 - 1 >= n2 - n1 - 1) {
        vector<T> newV;
        int newSize = n2 - n1;
        newV.resize(newSize);
        // int* p = data.data();


        for (int i = n1; i < n2; i++) {
            newV[i - n1] = data[i];
        }
        n1 = 0;
        n2 = newSize;
        data = newV;
        
    }
    return val;

}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    return data.front();
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    return data.back();
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    return data.empty();
}
