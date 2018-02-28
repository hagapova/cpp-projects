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
        /* delete theobj;
        theobj = other.theobj;
        other.theobj = nullptr; */
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


int main() {
    int *e = new int(66);
    int *re = new int(67);
    UniquePtr<int> ue(e);
    std::unique_ptr<int> reale(re);
    std::cout << *ue << " " << *reale << "\n"; // 66 67
    *ue = 5;
    *reale = 6;
    std::cout << *ue << " " << *reale << "\n"; // 5 6
    std::cout << *e << " " << *re << "\n"; // 5 6
    *e = 13;
    *re = 14;
    std::cout << *ue << " " << *reale << "\n"; // 13 14
    std::cout << *e << " " << *re << "\n"; // 13 14


    std::unique_ptr<int> reala(new int(43));
    std::unique_ptr<int> realb(new int(25));
    std::unique_ptr<int> realc;
    UniquePtr<int> ua(new int(42));
    UniquePtr<int> ub(new int(24));
    UniquePtr<int> uc;

    std::cout << *ua << " " << *reala << "\n"; // 42 43
    std::cout << *(ua.get()) << " " << *(reala.get()) << "\n"; // 42 43

    std::cout << (uc.get() == realc.get()) << "\n"; // 1

    ua.reset(ub.release());
    reala.reset(realb.release());

    std::cout << *ua << " " << *reala << "\n"; //24 25

    std::cout << bool(ub) << " " << bool(realb) << "\n"; // 0 0
    std::cout << bool(ua) << " " << bool(reala) << "\n"; // 1 1
    ua = nullptr;
    reala = nullptr;
    std::cout << bool(ua) << " " << bool(reala) << "\n"; // 0 0

    //std::cout << *a<<  " " << *ra << "\n";
    int *d = new int(111);
    int *rd = new int(112);
    ua.reset(d);
    reala.reset(rd);

    std::cout << *ua << " " << *reala << "\n"; // 111 112

    *ua = 123;
    *reala = 124;
    std::cout << *ua << " " << *reala << "\n"; // 123 124
    std::cout << *(ua.release()) << " " << *(reala.release()) << "\n"; // 123 124


    ua.reset(new int(42));
    reala.reset(new int(43));
    ub.reset(new int(24));
    realb.reset(new int(25));
    std::cout << *ua << " " << *reala << "\n"; // 42 43
    std::cout << *ub << " " << *realb << "\n"; // 24 25
    ua.UniquePtr<int>::swap(ub);
    std::swap(reala, realb);
    std::cout << *ua << " " << *reala << "\n"; // 24 25
    std::cout << *ub << " " << *realb << "\n"; // 42 43
    ua = std::move(ub);
    reala = std::move(realb);
}