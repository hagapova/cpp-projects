#include <iostream>
#include <cstddef>
#include <utility>

template <typename T>
class UniquePtr {
public:
    T *theobj;

    UniquePtr() : theobj(nullptr) {}

    UniquePtr(T *obj) : theobj(obj) {}

    UniquePtr(UniquePtr&& other) {
        theobj = nullptr;
        std::swap(theobj, other.theobj);
    }

    UniquePtr& operator =(std::nullptr_t) {
        delete theobj;
        theobj = nullptr;
        return *this;
    }

    UniquePtr& operator =(UniquePtr&& other) {
        std::swap(theobj, other.theobj);
        return * this;
    }

    UniquePtr(UniquePtr& other) = delete;
    UniquePtr& operator =(UniquePtr& other) = delete;

    T& operator *() {
        return *theobj;
    }

    const T& operator *() const {
        return *theobj;
    }

    const T* operator ->() const {
        return theobj;
    }

    T* release() {
        T* temp = theobj;
        theobj = nullptr;
        return temp;
    }

    void reset(T * ptr) {
        delete theobj;
        theobj = ptr;
    }

    void swap(UniquePtr& other) {
        std::swap(theobj, other.theobj);
    }

    T * get() const {
        return theobj;
    }

    explicit operator bool() const {
        return (theobj != nullptr);
    }

    ~UniquePtr() {
        delete theobj;
    }
};

