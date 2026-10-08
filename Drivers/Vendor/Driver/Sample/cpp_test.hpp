#ifndef CPP_TEST_HPP
#define CPP_TEST_HPP

class Counter
{
public:
    Counter() : m_value(0) {}
    explicit Counter(int start) : m_value(start) {}
    void increment() { ++m_value; }
    int  value() const { return m_value; }

private:
    int m_value;
};

#endif /* CPP_TEST_HPP */
