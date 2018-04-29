#pragma once
#include "stdafx.h"
#include <iostream>

template<class T>
class ring
{
private:
	int m_pos;
	int m_size;
	T * m_values;
public:
	class iterator;
	//constructor
	ring(int size):m_pos(0),m_size(size),m_values(0){
		m_values = new T[size];
	}
	//destructor
	~ring()
	{
		delete[]m_values;
	}

	int size()
	{
		return m_size;
	}

	void add(T value)
	{
		m_values[m_pos] = value;
		m_pos++;
		if (m_pos == m_size)
			m_pos = 0;
	}
	T &get(int pos)
	{
		return m_values[pos];
	}
	iterator begin()
	{
		return iterator(0, *this);
	}
	iterator end()
	{
		return iterator(m_size, *this);
	}
};


template<class T>
class ring<T>::iterator {
private:
	int m_pos;
	ring &m_ring;
public:
	iterator(int pos, ring &aRing):m_pos(pos),m_ring(aRing){}

	iterator &operator++() //prefix
	{
		m_pos++;
		return *this;
	}
	iterator &operator++(int) //postfix
	{
		m_pos++;
		return *this;
	}

	T &operator*()
	{
		return m_ring.get(m_pos);
	}

	bool operator!=(const iterator &other) const{
		return m_pos != other.m_pos;
	}
};
