/*
File: string.cpp

Copyright (c) 2018 Alexander DuPree

This software is released as open source through the MIT License

Authors: Alexander DuPree

https://github.com/AlexanderJDupree/Python-Strings-for-CPP

*/

#ifndef STRING_CPP
#define STRING_CPP

#include <iostream>
#include "string.hpp"

/* Constructors */
String::String(const_pointer str) : String(len(str) + 1)
{
    copy(str, _capacity);
    _data[_length] = '\0';
}

String::String(size_type n) : _data(new char[n]), _length(0), _capacity(n) {}

/* Capacity */
String::size_type String::size() const
{
    return _length;
}

String::size_type String::length() const
{
    return _length;
}

String::size_type String::capacity() const
{
    return _capacity;
}

void String::reserve(size_type n)
{
    if(_capacity > n) { return; }

    resize(n - 1);
}

void String::resize(size_type n)
{
    _capacity = n + 1;
    if(_data == nullptr)
    {
        _data = new char[_capacity];
        return;
    }

    pointer temp = new char[_capacity];

    this->_length = copy(*this, temp, _capacity - 1);

    temp[_length] = '\0';

    delete [] this->_data;

    this->_data = temp;

    return;
}

bool String::empty() const
{
    return !(_length);
}

/* Operations */
String::size_type String::len(const_pointer str)
{
    validate_pointer(str);

    size_type length;
    for(length = 0; str[length] != '\0'; ++length);

    return length;
}

String::size_type String::copy(const self_type& in_str, pointer out_str, size_type len, size_type pos)
{
    validate_pointer(out_str);
    validate_pointer(in_str._data);

    size_type i = 0;
    for(; i < len && in_str._data[pos] != '\0'; ++i)
    {
        out_str[i] = in_str._data[pos++];
    }
    return i;
}

String::size_type String::copy(const_pointer str, size_type len)
{
    validate_pointer(str);
    if (len > _capacity) { resize(len); }

    size_type i = 0;
    for(; i < len && str[i] != '\0'; ++i)
    {
        _data[i] = str[i];
    }
    _length = i;
    return i;
}

bool String::compare_equal(const_pointer str) const
{
    if(catch_null_exception(str) || catch_null_exception(_data))
    {
        return false;
    }

    size_type i = 0;
    for (; _data[i] != '\0' && str[i] != '\0' && _data[i] == str[i]; ++i);

    return i == _length;
}

bool String::compare_equal(const self_type& str) const
{
    if(_length != str._length)
    {
        return false;
    }
    else if(_length == 0 && str._length == 0)
    {
        return true;
    }

    return compare_equal(str._data);
}

/* Modifiers */
void String::push_back(const_reference character)
{
    if(_length >= _capacity - 1) { resize(_capacity * 2); }

    _data[_length++] = character;
    _data[_length] = '\0';

    return;
}

/* Operator Overloads */
bool operator==(const String& lhs, const char* rhs)
{
    return lhs.compare_equal(rhs);
}
bool operator==(const char* lhs, const String& rhs)
{
    return (rhs == lhs);
}
bool operator==(const String& lhs, const String& rhs)
{
    return lhs.compare_equal(rhs);
}
bool operator!=(const String& lhs, const char* rhs)
{
    return !(lhs == rhs);
}
bool operator!=(const char* lhs, const String& rhs)
{
    return (rhs != lhs);
}
bool operator!=(const String& lhs, const String& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    os << str._data;
    return os;
}

String::reference String::operator[](index_type pos)
{
    validate_position(pos);

    return _data[pos];
} 

String::const_reference String::operator[](index_type pos) const
{
    validate_position(pos);

    return _data[pos];
}

/* Private */
void String::validate_pointer(const_pointer str)
{
    if(str) { return; }

    throw std::invalid_argument("char pointer points to null");
}

void String::validate_position(index_type& pos) const
{
    if (pos < 0) { pos += _length; }
    if(pos < static_cast<index_type>(_length) && pos >= 0) { return; }

    throw out_of_range("error, index pos is out of bounds", pos);
}

bool String::catch_null_exception(const_pointer str)
{
    try
    {
        validate_pointer(str);
        return false;
    }
    catch(const std::invalid_argument& err)
    {
        return true;
    }
}

#endif // STRING_CPP