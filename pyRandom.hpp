#ifndef _RANDOM_CppPython_KLEVH_
#define _RANDOM_CppPython_KLEVH_

#include "pyList.hpp"
#include "pySTD.hpp"
#include <cstdlib>
#include <ctime>

//Random module
namespace Random{
  //do not use this variable, it tells whether or not srand was call
  bool _initialized = false;
    
  //calls srand if it was not already
  void _init(){
    if(!_initialized){
      srand(time(0));
      _initialized=true;
    }
  }
    
  //python's randint function
  int randint(int a,int b){
    _init();
    return rand()%(b-a+1)+a;
  }
    
  //python's randrange function
  int randrange(int a,int b,int inc=1){
    _init();
    --b;
    return rand()%((b-a)/inc+1)*inc+a;
  }
  int randrange(int end){
    return randrange(0,end);
  }
    
  //python's choice function
  template <class T>
  T choice(const List<T>& l){
    return l[randint(0,len(l)-1)];
  }
    
  //python's shuffle function
  template <class T>
  void shuffle(List<T>& l){
    unsigned id, size=len(l);
    T * arr = new T[size];
    T tmp;
        
    if(arr){
      for(unsigned i=0;i<size;++i)
	arr[i]=l.pop();
      for(unsigned i=0;i<size;++i){
	id=randint(i,size-1);
	tmp=arr[i];
	arr[i]=arr[id];
	arr[id]=tmp;
	l.append(arr[i]);
      }
      delete[] arr;
    }else{
      for(unsigned i=0;i<len(l)-1;++i){
	id=randint(i,len(l)-1);
	if(id!=i)
	  l[i]^=l[id]^=l[i]^= l[id];
      }
            
    }
  }
}
// ---------------------------------------------------------------------------

#endif
