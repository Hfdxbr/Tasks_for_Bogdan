#include "big_int.h"
//4'000'000'000


BigInt::BigInt(std::string s) {
    if (s.front() == '-') {
        sign = -1;
        s = s.substr(1);
    }
    auto head = s.size() % piece_size;
    // 111'222222222'333333333 -> [333333333, 222222222, 111]
    if (head != 0)
        Number.push_front(std::stoi(s.substr(0, head)));
    for(auto i = head; i < s.size(); i += piece_size)
        Number.push_front(std::stoi(s.substr(i, piece_size)));
}

BigInt::BigInt(int value) {
    if (value < 0) {
        value = -value;
        sign = -1;
    }
    Number.push_front(value);
}

BigInt::BigInt(const BigInt& other) {
    Number = other.Number;
    sign = other.sign;
}

bool BigInt::operator < (const BigInt &B) const {
    if (sign != B.sign)
        return sign < B.sign;

    if (Number.size() != B.Number.size())
        return sign > 0 ? Number.size() < B.Number.size() : Number.size() > B.Number.size();

    auto this_iter = Number.rbegin();
    auto other_iter = B.Number.rbegin();

    for (; this_iter != Number.rend(); ++this_iter, ++other_iter)
        if (*(this_iter) != *(other_iter))
            return sign > 0 ? *(this_iter) < *(other_iter) : *(this_iter) > *(other_iter);

    return false;
}

BigInt & BigInt::operator=(const BigInt& other) {
    if (this != &other)
        Number = other.Number;
        sign = other.sign;
    return *this;
}

bool BigInt::operator!=(const BigInt& B) const {
    if (sign != B.sign)
        return false;

    if (Number.size() != B.Number.size())
        return false;

    auto this_iter = Number.rbegin();
    auto other_iter = B.Number.rbegin();

    for (;this_iter != Number.rend(); ++this_iter, ++other_iter)
        if (*(this_iter) != *(other_iter))
            return false;

    return true;
}

bool BigInt::operator<=(const BigInt& other) const {
    return !(*this > other);
}
bool BigInt::operator==(const BigInt& other) const {
    return !(*this != other);
}
bool BigInt::operator>(const BigInt& other) const {
    return (*this != other && *this >= other); 
}
bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}

std::list<unsigned> sum_list(const std::list<unsigned>& a, const std::list<unsigned>& b) {
    std::list<unsigned> result;
    auto it_a = a.begin();
    auto it_b = b.begin();

    bool add_unity = false;
    for(; it_a != a.end() && it_b != b.end(); ++it_a, ++it_b) {
        result.push_back(*it_a + *it_b);
        result.back() += add_unity;
        add_unity = false;
        if(result.back() >= piece_val) {
            result.back() -= piece_val;
            add_unity = true;
        }
    }
    for(; it_a != a.end(); ++it_a) {
        result.push_back(*it_a);
        result.back() += add_unity;
        add_unity = false;
        if(result.back() >= piece_val) {
            result.back() -= piece_val;
            add_unity = true;
        }
    }
    for(; it_b != b.end(); ++it_b) {
        result.push_back(*it_b);
        result.back() += add_unity;
        add_unity = false;
        if(result.back() >= piece_val) {
            result.back() -= piece_val;
            add_unity = true;
        }
    }
    return result;
}

std::list<unsigned int> sub_list(const std::list<unsigned>& a, const std::list<unsigned>& b) {
    std::list<unsigned> result;
    auto it_a = a.begin();
    auto it_b = b.begin();

    bool sub_unity = false;
    for(; it_a != a.end() && it_b != b.end(); ++it_a, ++it_b) {
        result.push_back(abs(*it_a - *it_b));
        if (*it_a - *it_b < 0)
            result.back() += sub_unity;
        else result.back() -= sub_unity;
        sub_unity = false;
        if(result.back() < 0) {
            sub_unity = true;
        }
    }
    for(; it_a != a.end(); ++it_a) {
        result.push_back(*it_a);
        result.back() -= sub_unity;
        sub_unity = false;
    }
    if (it_b != b.end()) {
        result.clear();
        result = sub_list(b,a);
    }
    return result;
}

BigInt BigInt::operator+(const BigInt& other) const {
    BigInt result;
    result.sign = 1;

    
    if (sign == other.sign == 1)
        result.Number = sum_list(Number, other.Number);
    
    if (sign == -other.sign == 1) {
        result.Number = sub_list(Number, other.Number);
        if(*this < -other) {
            result.sign = -result.sign;
        }
    }

    if (-sign == other.sign == 1) {
        result.Number = sub_list(other.Number, Number);
        if(-*this > other) {
            result.sign = -result.sign;
        }
    }

    if (-sign == -other.sign == 1) {
        result.Number = sub_list(other.Number, Number);
        result.sign = -result.sign;
    }

    return result;
}

BigInt BigInt::operator-(const BigInt& other) const {
    BigInt temp_1 = *this;
    BigInt temp_2 = other;
    temp_2.sign = -temp_2.sign;

    return temp_1 + temp_2;
}

BigInt & BigInt::operator+=(const BigInt& other) {
    *this = *this + other;
    return *this;
}
BigInt & BigInt::operator-=(const BigInt& other) {
    *this = *this - other;
    return *this;
}
BigInt BigInt::operator-() const {
    BigInt result;
    result.Number = Number;
    result.sign = -sign;

    return result;
}

BigInt & BigInt::operator++() {
    BigInt temp(1);
    *this = *this + temp;
    return *this;
}
BigInt BigInt::operator++(int) {
    BigInt result;
    BigInt temp(1);
    result = *this + temp;
    return result;
}
BigInt & BigInt::operator--() {
    BigInt temp(1);
    *this = *this - temp;
    return *this;
}
BigInt BigInt::operator--(int) {
    BigInt result;
    BigInt temp(1);
    result = *this - temp;
    return result;
}


std::ostream & operator<<(std::ostream& os, const BigInt& number) {
    auto this_iter = number.Number.rbegin();
    for (; this_iter != number.Number.rend(); ++this_iter) {
        os << *this_iter;
    }
}