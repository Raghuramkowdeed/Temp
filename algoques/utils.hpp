#pragma once


#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>


namespace AlgoComp {
typedef unsigned long cyclecount_t;

static __inline__ cyclecount_t GetCpucycleCount(void)
{
  uint32_t lo, hi;
  __asm__ __volatile__ (      // serialize
			"xorl %%eax,%%eax \n        cpuid"
			::: "%rax", "%rbx", "%rcx", "%rdx");
  /* We cannot use "=A", since this would use %rax on x86_64 and return only the lower 32bits of the TSC */
  __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
  return (cyclecount_t)hi << 32 | lo;
}

class PerishableStringTokenizer {
public:
  std::vector < const char * > tokens_ ;
  PerishableStringTokenizer ( char * t_readline_buffer_, unsigned int _bufferlen_ ) 
  {
    bool reading_word_ = false;
    for ( unsigned int i = 0 ; i < _bufferlen_ ; i ++ ) 
      {
	int int_value_char_ = (int)t_readline_buffer_[i] ;
	
	if ( iscntrl ( int_value_char_ ) && ( t_readline_buffer_[i] != '\t' ) ) 
	  { // end of string .. should be replaced with == NUL ?
	    t_readline_buffer_[i] = '\0';
	    break;
	  }
	
	if ( ! isspace ( int_value_char_ ) && ! reading_word_ ) 
	  {
	    tokens_.push_back ( & ( t_readline_buffer_[i] ) ) ;
	    reading_word_ = true;
	  }
	
	if ( isspace ( int_value_char_ ) && reading_word_ ) 
	  { // first space char after word ... replace with NUL
	    t_readline_buffer_[i] = '\0';
	    reading_word_ = false;
	  }
      }
  }
  const std::vector < const char * > & GetTokens ( ) const { return tokens_; }
};

}

