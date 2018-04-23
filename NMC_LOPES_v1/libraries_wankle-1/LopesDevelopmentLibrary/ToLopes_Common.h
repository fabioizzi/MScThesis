#ifndef __TOLOPES_COMMON_H__
#define __TOLOPES_COMMON_H__

// Struct/union combination for telling which messages are sent/received

typedef struct {
  bool create_springspring         :1; 
  bool create_biasforcespring      :1; 
  bool update_max_forces           :1; 
  bool treadmill_velocity          :1; 
  bool enable_effects              :1; 
  bool set_springspringpositions   :1;
  bool set_springspringvelocities  :1;
  bool set_springspringstiffnesses :1;
  bool set_biasforcespring         :1;
} msgId_bits ;

typedef union  {
  msgId_bits b;
  unsigned int intValue;
} msgId_type;

#endif
