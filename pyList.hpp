#ifndef _LIST_CppPython_KLEVH_
#define _LIST_CppPython_KLEVH_

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <functional>
#include "CustomOperators/CustomOperators.hpp"
using std::cout;
using std::endl;
using std::ostream;
using std::range_error;
using std::string;
using std::ostringstream;
using std::function;

// ---------------------------------------------------------------------------
//python's lists

//An element of the linked list
template <class T>
struct Element{
  T value; //value of the element
  Element<T> * next; //next element
  Element<T> * prec; //previous element
  Element(T value); //element's constructor
};

//The python linked list
template <class T>
class List{
  Element<T> * first; //first Element of the list
  Element<T> * last; //last element of the list
  unsigned long size; //size of the list
  bool wasCleared; //is useful for the () operator
    
 public:
  //constructors and destructor of the list
  List();
  List(T val);
  template <class ...U> List(T val,U ...args)
    :first(nullptr),last(nullptr),size(0)
    ,wasCleared(false){
    operator()(val,args...);
  }
  template <class ...U> List(const List<T>& l, U ...args)
    :first(nullptr),last(nullptr),size(0)
    ,wasCleared(false){
    operator()(l,args...);
  }
  ~List();
  List(const List<T>& l);
  // overloading of operators =,+,+=,*= in this order
  List<T>& operator=(const List<T>& l);
  List<T> operator+(const List<T>& l);
  List<T>& operator+=(const List<T>& l);
  List<T>& operator*=(const unsigned& times);
  //overloading of [] accessor, one with unsigned to access values, one with string to copy a part of the list like in python
  T& operator[](int id) const;
  List<T> operator[](const string& s) const;
  //overloading of List*unsigned operator
  List<T> operator*(const unsigned times);
  //getLength method, used in len function
  unsigned getLength() const;
  //append and insert methods, return true if there was an error, false if not
  bool append(T value);
  bool insert(int id,T value);
  //pop and del methods
  T pop();
  T del(unsigned id);
  //overloading of opperator << (for append) and >> (for pop)
  List<T>& operator<<(const T& val);
  List<T>& operator>>(T& val);
  //overloading of cast from List to string
  explicit operator const string();
    
  //list creation operator, is the same as the python syntax l=[1,2,3,4], if a list is inside, for example l2(1,2,l), it will result as l2(1,2,1,2,3,4)
  template <class ...U>
    List<T>& operator()(T val,U ...args){
    if(!wasCleared){
      wasCleared = true;
      while(size)
	pop();
    }
    append(val);
    return operator()(args...);
  }
  template <class ...U>
    List<T>& operator()(const List<T>& l,U ...args){
    if(!wasCleared){
      wasCleared = true;
      while(size)
	pop();
    }
    for(List<T>::iterator it(l);!it.end();++it)
      append(*it);
    return operator()(args...);
  }
  List<T>& operator()(T val){
    if(!wasCleared){
      while(size)
	pop();
    }else
      wasCleared = false;
    append(val);
    return *this;
  }
  List<T>& operator()(const List<T>& l){
    if(!wasCleared){
      while(size)
	pop();
    }else
      wasCleared = false;
    for(List<T>::iterator it(l);!it.end();++it)
      append(*it);
    return *this;
  }
    
  //List iterator
  class iterator{
    Element<T> * curr; //current element of the iterator
    Element<T> * first; //first element of the iterator
    bool _end; //tells whether or not the iterator reached its end
        
  public:
    //iterator's constructors
    iterator(const List<T>& l);
    iterator(const List<T>::iterator& it);
    //reset method, set first as curr
    void reset();
    //set the iterator to its end
    void setEnd();
    //!= operator to compare iterators
    bool operator!=(const List<T>::iterator& it);
    //= operator
    List<T>::iterator& operator=(const List<T>::iterator& it);
    //overloading of operators *iterator, ++iterator and iterator++
    T operator*();
    T operator++();
    T operator++(int);
    //method to tells whether or not the iterator reached its end
    bool end();
  };
    
  //iterator's begin and end functions
  List<T>::iterator begin() const;
  List<T>::iterator end() const;
};

//unsigned*List overloading operator
template <class T>
List<T> operator*(const unsigned& times,const List<T>& l);

//python's len function
template <class T>
unsigned len(const List<T>& l);

//overloading of << operator for terminal display purpose
template <class T>
ostream& operator<<(ostream& os,const List<T>& l);
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
//class element implementation
//Constructor : just initialize attributes
template <class T>
Element<T>::Element(T value)
  :value(value),next(nullptr),prec(nullptr)
{}

//class list implementation
//Constructor : just initialize attributes
template <class T>
List<T>::List()
  :first(nullptr),last(nullptr),size(0),wasCleared(false)
{}
template <class T>
List<T>::List(T val)
  :first(nullptr),last(nullptr)
  ,size(0),wasCleared(false){
  append(val);
}

//Destructor : free the memory used by the list
template <class T>
List<T>::~List(){
  Element<T> * curr=first, *tmp;
    
  //we go through all the elements of the list, deleting them one by one
  while(curr){
    tmp=curr->next;
    delete curr;
    curr=tmp;
  }
}

//Copy's constructor : copy the elements of another list in the newly created list
template <class T>
List<T>::List(const List<T>& l)
  :first(nullptr),last(nullptr),size(0),wasCleared(false){
  List<T>::iterator it(l); //iterator to the list to be copied
    
  //we append every element of the list to be copied in our list, so that they keep the same order
  while(!it.end()){
    append(*it);
    ++it;
  }
}

//= operator : same behavior as copy's constructor but clear our list first
template <class T>
List<T>& List<T>::operator=(const List<T>& l){
  List<T>::iterator it(l);
    
  while(getLength())
    pop();
  while(!it.end()){
    append(*it);
    ++it;
  }

  return *this;
}

//+ operator : create a new list and append all the element of our list into it, then all the element of the other list, and return it
template <class T>
List<T> List<T>::operator+(const List<T>& l){
  List<T>::iterator it(l);
  Element<T> * curr;
  List<T> res;
    
  curr=first;
  while(curr){ //appending the element of our list
    res.append(curr->value);
    curr=curr->next;
  }
  while(!it.end()){ //appending the elements of the other list
    res.append(*it);
    ++it;
  }
    
  return res;
}

//+= operator : appends all the element of the list to our list then return a reference to our list
template <class T>
List<T>& List<T>::operator+=(const List<T>& l){
  for(List<T>::iterator it(l);!it.end();++it)
    append(*it);
        
  return *this;
}

//*= operator : if the unsigned argument is 0, it clears our list, if not, it appends time-1 times the list to itself. The method then return a reference to the list
template <class T>
List<T>& List<T>::operator*=(const unsigned& times){
  if(times) //append the list
    for(unsigned i=0;i<times-1;++i)
      for(List<T>::iterator it(*this);!it.end();++it)
	append(*it);
  else //clear the list
    while(getLength())
      pop();
            
  return *this;
}

//[int] operator : accessor to the list's elements, allow doing like in python : l[-1], l[5]=5, ...
template <class T>
T& List<T>::operator[](int id) const{
  Element<T> * curr = first;
  unsigned i;
    
  if(static_cast<unsigned>(id)>=size || id<-(int)size)//throw an error when the id is out of range
    throw range_error("List : [int] : id out of range exception");
  if(id<0)//convert negative id into positive one
    i = size + id;
  else
    i = static_cast<unsigned>(id);
    
  while(i--)
    curr=curr->next;
    
  return curr->value;
}

//[string] operator : return a sublist of your list depending of the range described by the string : l[::-1], l[:3], l[2:], l[1:8:3], ...
template <class T>
List<T> List<T>::operator[](const string& s) const{
  long int i = 0, j = 0, k = 0; //three numbers of the range : l[i:j:k]
  int signe=1; //used to remember the signe while translating characters to number
  bool guessI=false, guessJ=false; //those bools are set to true if the variable (i and j respectively) had to be guessed
  unsigned id =0;//tells where we are in the string to analyse it
  List<T> res; //resulting list
  Element<T> * curr; //element to go through our list
    
  //we ignore spaces at the beginning
  while(s[id]==' ')
    ++id;
  //if the first character after all those spaces is not a :, we try to read an integer next
  if(s[id]!=':'){
    if(s[id]=='-'){
      signe=-1;
      ++id;
    }
    if(s[id]<'0' || s[id]>'9')
      throw range_error("List : [string] : NaN in first index of range");
    while(s[id]>='0' && s[id]<='9'){
      i=i*10+(int)(s[id]-'0');
      ++id;
    }
    i*=signe;
    while(s[id]==' ')
      ++id;
  }else //else we have to guess i
    guessI=true;
  if(s[id]!=':') //if at the end of the reading if the integer and extra spaces, we are not on a :, then there is a "syntax error" in the string
    throw range_error("List : [string] : Bad range of indexes");
  ++id;
    
  //we do the same thing for j
  while(s[id]==' ')
    ++id;
  if(s[id]!=':' && s[id]){
    if(s[id]=='-'){
      signe=-1;
      ++id;
    }else
      signe=1;
    if(s[id]<'0' || s[id]>'9')
      throw range_error("List : [string] : NaN in second index of range");
    while(s[id]>='0' && s[id]<='9'){
      j=j*10+(int)(s[id]-'0');
      ++id;
    }
    j*=signe;
    while(s[id]==' ')
      ++id;
  }else
    guessJ=true;
  if(s[id]!=':' && s[id]) //here, there is no error if we do not have a : because we are at the end of the string, if not, error
    throw range_error("List : [string] : Bad range of indexes");

  //lastly, we read k the same way
  if(s[id] && s[id]==':'){
    ++id;
    if(s[id]=='-'){
      signe=-1;
      ++id;
    }else
      signe=1;
    if(s[id]<'0' || s[id]>'9')
      throw range_error("List : [string] : NaN in third index of range");
    while(s[id]>='0' && s[id]<='9'){
      k=k*10+(int)(s[id]-'0');
      ++id;
    }
    k*=signe;
  }else
    k=1;
    
  //then we correct i and j si that they are positives
  if(i<0)
    i=size+i;
  if(j<0)
    j=size+j+1;
        
  //we throw out of range exception if we need to
  if(i<0 || static_cast<unsigned>(i)>=size)
    throw range_error("List : [string] : first index out of range");
  if(j<0 || static_cast<unsigned>(j)>size)
    throw range_error("List : [string] : second index out of range");
        
  //the increment has to be different from zero, if not, error
  if(!k)
    throw range_error("List : [string] : range increment can not be zero");
    
  //now we save the sublist in two different ways depending on the signe of k
  if(k>0){
    //if k positive, we read and ignore the i first elements then append to the resulting list the j-i next element
    if(guessI)
      i=0;
    if(guessJ)
      j=size;
    curr=first;
    for(int a=0;a<i;++a)
      curr=curr->next;
    for(int a=i;a<j;a+=k){
      res.append(curr->value);
      curr=curr->next;
      for(int i=0;i<k-1 && curr;++i)
	curr=curr->next;
    }
  }else{
    //if k is negative, we read and ignore the first j elements, then read and insert the i-j next elements each time at the beginning of the resulting list to invert their order
    if(guessJ)
      j=0;
    if(guessI)
      i=size;
    curr=first;
    for(int a=0;a<j;++a)
      curr=curr->next;
    for(int a=j;a<i;a-=k){
      res.insert(0,curr->value);
      curr=curr->next;
      for(int i=0;i>k+1 && curr;--i)
	curr=curr->next;
    }
  }
    
  return res;
}

//* operator : do like *= operator but instead of modifying our list, it creates a new list
template <class T>
List<T> List<T>::operator*(const unsigned times){
  List<T> res;
  Element<T> * curr;
    
  for(unsigned i=0;i<times;++i){
    curr=first;
    for(unsigned j=0;j<size;++j){
      res.append(curr->value);
      curr=curr->next;
    }
  }
    
  return res;
}

//returns the length of the list (to be used by len function)
template <class T>
unsigned List<T>::getLength() const{
  return size;
}

//append : add the valur at the end of the list, return true if there was an error, false if not
template <class T>
bool List<T>::append(T value){
  Element<T> * curr=new Element<T>(value);;
    
  if(curr){
    if(last){
      last->next=curr;
      curr->prec=last;
      last=curr;
    }else{
      first=curr;
      last=curr;
    }
    ++size;
    return false;
  }
    
  return true;
}

//insert : add the value at the position id if possible, if id is out of range, throw an exception, if there was a memory error, return true, else return false
template <class T>
bool List<T>::insert(int id,T value){
  Element<T> ** curr=&first, *tmp;

  if(id<0)
    id=size+id;
  if(id<0 || static_cast<unsigned>(id)>size)
    throw range_error("List : insert : index out of bound");
    
  if(static_cast<unsigned>(id)==size){
    return append(value);
  }else{
    for(unsigned i=0;i<static_cast<unsigned>(id);++i)
      curr=&((*curr)->next);
    
    tmp=*curr;
    *curr=new Element<T>(value);
    
    if(*curr){
      (*curr)->next=tmp;
      (*curr)->prec=tmp->prec;
      if(tmp->prec)
	tmp->prec->next=*curr;
      tmp->prec=*curr;
      ++size;
      return false;
    }else{
      *curr=tmp;
      return true;
    }
  }
}

//remove and return the last value of the list
template <class T>
T List<T>::pop(){
  T res = {};
  Element<T> * curr = last;
    
  if(size){
    if(!last->prec)
      first=nullptr;
    else
      last->prec->next=nullptr;
    last=last->prec;
    res=curr->value;
    delete curr;
    size--;
  }else
    throw range_error("List : pop : the list is empty");
    
  return res;
}

//del : remove and return the value at the index id of the list
template <class T>
T List<T>::del(unsigned id){
  T res = {};
  Element<T> * curr=first;
    
  if(id>=size)
    throw range_error("List : del : index out of range");
        
  if(id==size-1){
    return pop();
  }else{
    for(unsigned i=0;i<id;++i)
      curr=curr->next;
    
    res=curr->value;
    curr->next->prec=curr->prec;
    curr->prec->next=curr->next;
    delete curr;
    size--;
  }
    
  return res;
}

//operator << : behave like append
template <class T>
List<T>& List<T>::operator<<(const T& val){
  append(val);
    
  return *this;
}

//operator >> : behave like pop
template <class T>
List<T>& List<T>::operator>>(T& val){
  val=pop();
    
  return *this;
}

//const string cast operator : return a string version of the list
template <class T>
List<T>::operator const string(){
  ostringstream s;
    
  s<<*this;
    
  return s.str();
}

//iterator's begin and end functions
template <class T>
typename List<T>::iterator List<T>::begin() const{
  return List<T>::iterator(*this);
}
template <class T>
typename List<T>::iterator List<T>::end() const{
  List<T>::iterator it(*this);
  it.setEnd();
  return it;
}

//other functions using list
//* operator for when the unsigned is put before the list
template <class T>
List<T> operator*(const unsigned& times,const List<T>& l){
  List<T> res;
  typename List<T>::iterator it(l);
    
  for(unsigned i=0;i<times;++i)
    for(it.reset();!it.end();++it)
      res.append(*it);
            
  return res;
}

//return the length of the list
template <class T>
unsigned len(const List<T>& l){
  return l.getLength();
}

//operator<< for display purpose
template <class T>
ostream& operator<<(ostream& os,const List<T>& l){
  typename List<T>::iterator it(l);
    
  os<<"[";
  while(!it.end()){
    os<<*it;
    ++it;
    if(!it.end())
      os<<", ";
  }
  os<<"]";
    
  return os;
}
    
//List::iterator class implementation
//Iterator's constructor
template <class T>
List<T>::iterator::iterator(const List<T>& l)
  :curr(l.first),first(l.first){}

//Iterator copy constructor
template <class T>
List<T>::iterator::iterator(const List<T>::iterator& it)
  :curr(it.curr),first(it.first){}

//reset the iterator to its beginning
template <class T>
void List<T>::iterator::reset(){
  curr=first;
}

//set the iterator to its end
template <class T>
void List<T>::iterator::setEnd(){
  curr=nullptr;
}

//!= operator to compare iterators
template <class T>
bool List<T>::iterator::operator!=(const List<T>::iterator& it){
  return curr!=it.curr;
}

//= operator
template <class T>
typename List<T>::iterator& List<T>::iterator::operator=(const List<T>::iterator& it){
  curr=it.curr;
  first=it.first;
  return *this;
}

//unary operator * : getter for the current value of the iterator
template <class T>
T List<T>::iterator::operator*(){
  return curr->value;
}

//++ operator : go to the next element and return its value if possible
template <class T>
T List<T>::iterator::operator++(){
  T val={};
    
  if(curr)
    curr=curr->next;
  if(curr)
    val=curr->value;
    
  return val;
}

//operator ++: return the value of the current element and go to the next
template <class T>
T List<T>::iterator::operator++(int){
  T val={};
    
  if(curr){
    val=curr->value;
    curr=curr->next;
  }
    
  return val;
}

//tells whether or not the iterator reached its end
template <class T>
bool List<T>::iterator::end(){
  return !curr;
}
// ---------------------------------------------------------------------------




// List new operators
namespace List_operator{
    template <class T>
    Custom_operator::operator_lhs <function<bool(T,const List<T>&)>> in(){
        return {[](T v,const List<T>& l){
            for(T i : l)
                if(i==v)
                    return true;
            return false;
        }};
    }
}
// ---------------------------------------------------------------------------
#endif
