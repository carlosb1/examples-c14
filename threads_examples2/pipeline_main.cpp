#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <list>

template <typename Data>
class pipeline {
    typedef boost::function<Data(Data)> filter_function;
    typedef std::list<filter_function> filter_list;
    filter_list m_list;

public:
    template<typename T>
    void add(T t) {
        m_list.push_back(boost::bind(&T::filter, t, _1));
    }

    Data run(Data data) {
        typedef typename filter_list::iterator iter;
        iter end = m_list.end();

        for(iter it = m_list.begin(); it != end; ++it) {
            data = (*it)(data);
        }

        return data;
    }
};

struct foo {
    int filter(int i) {
        return i + 1;
    }
};

int main(int argc, _TCHAR* argv[])
{
    pipeline<int> pipe;
    foo f;
    pipe.add(f);
    std::cout << pipe.run(0);
    char c;
    std::cin >> c;
}
