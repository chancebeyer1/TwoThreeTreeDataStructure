#pragma once
#include <vector>

template<typename K, typename V>
class TwoThreeNode
{
public:

  std::vector<K>* keys;
  std::vector<V>* values;
  std::vector<TwoThreeNode<K, V>*>* pointers;

  TwoThreeNode(K key, V value)
  {
    this->keys = new std::vector<K>(1);
    this->keys->at(0) = key;
    this->values = new std::vector<V>(1);
    this->values->at(0) = value;
    this->pointers = new std::vector<TwoThreeNode<K, V>*>(2);
  }

  bool isTwoNode()
  {
    return this->keys->size() == 1;
  }

  bool isThreeNode()
  {
    return this->keys->size() == 2;
  }

  bool isFourNode()
  {
    return this->keys->size() == 3;
  }

  bool findIn(K key, int* i)
  {
    if (this->isTwoNode())
    {
      if (this->keys->at(0) == key)
      {
        i = new int(0);
        return true;
      }
      else if (this->keys->at(0) > key)
      {
        i = new int(0);
        return false;
      }
      else
      {
        i = new int(1);
        return false;
      }
    }
    else if (this->isThreeNode())
    {
      for (int k = 0; k < this->keys->size(); k++)
      {
        if (this->keys->at(k) == key)
        {
          i = new int(k);
          return true;
        }
      }
      if (this->keys->at(0) > key)
      {
        i = new int(0);
        return false;
      }
      else if (this->keys->at(1) < key)
      {
        i = new int(2);
        return false;
      }
      else
      {
        i = new int(1);
        return false;
      }
    }
  }

  void add(K key, V value)
  {
    int* i = 0;
    bool f = this->findIn(key, i);
    if (this->isTwoNode())
    {
      if ((int) i == 0)
      {
        this->keys->insert(this->keys->begin(), key);
        this->values->insert(this->values->begin(), value);
        this->pointers->insert(this->pointers->begin(), nullptr);
      }
      else
      {
        this->keys->push_back(key);
        this->values->push_back(value);
        this->pointers->push_back(nullptr);
      }
    }
    else if (this->isThreeNode())
    {
      if ((int) i == 0)
      {
        this->keys->insert(this->keys->begin(), key);
        this->values->insert(this->values->begin(), value);
        this->pointers->insert(this->pointers->begin(), nullptr);
      }
      else if ((int) i == 1)
      {
        this->keys->insert(this->keys->begin() + 1, key);
        this->values->insert(this->values->begin() + 1, value);
        this->pointers->insert(this->pointers->begin() + 1, nullptr);
      }
      else
      {
        this->keys->push_back(key);
        this->values->push_back(value);
        this->pointers->push_back(nullptr);
      }
    }
  }

  //void resize()
  //{
  //  int size = this->keys.size() + 1;
  //  this->keys.resize(size);
  //  this->values.resize(size);
  //  this->pointers.resize(size + 1);
  //}
  //
  //void addFront(K key, V value)
  //{
  //  this->keys.insert(this->keys.begin(), key);
  //  this->values.insert(this->values.begin(), value);
  //  this->pointers.resize(this->pointers.size() + 1);
  //  this->pointers[2] = this->pointers[1];
  //  this->pointers[1] = this->pointers[0];
  //  this->pointers[0] = nullptr;
  //}

  //void addBack(K key, V value)
  //{
  //  this->keys.push_back(key);
  //  this->values.push_back(value);
  //  this->pointers.resize(this->pointers.size() + 1);
  //  this->pointers[2] = this->pointers[1];
  //  this->pointers[1] = nullptr;
  //}

};