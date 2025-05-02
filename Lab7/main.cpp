#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Vector1 {
protected:
    vector<T> elements;
public:
    void push(T elem) {
        elements.push_back(elem);
    }

    T pop() {
        T val = elements.back();
        elements.pop_back();
        return val;
    }

    bool empty() const {
        return elements.empty();
    }

    int size() const {
        return (int)elements.size();
    }

    class iterator {
    private:
        typename vector<T>::iterator it, begin_it, end_it;
    public:
        iterator(typename vector<T>::iterator cur,
                 typename vector<T>::iterator b,
                 typename vector<T>::iterator e)
                : it(cur), begin_it(b), end_it(e) {}

        iterator& operator++() {
            ++it;
            if (it == end_it) it = begin_it;
            return *this;
        }

        iterator operator+(int n) const {
            iterator tmp = *this;
            for (int i = 0; i < n; ++i) {
                ++tmp;
            }
            return tmp;
        }

        T& operator*() const {
            return *it;
        }

        bool operator!=(const iterator& other) const {
            return it != other.it;
        }
    };

    iterator begin() {
        return iterator(elements.begin(), elements.begin(), elements.end());
    }

    iterator end() {
        return iterator(elements.end(), elements.begin(), elements.end());
    }
};

int main() {
    Vector1<int> v;
    v.push(1);
    v.push(2);
    v.push(3);

    auto it = v.begin();
    cout << *it << " ";
    cout << *(it + 1) << " ";
    cout << *(it + 2) << " ";
    cout << *(it + 3) << " ";
    cout << *(it + 4) << " ";

    return 0;
}