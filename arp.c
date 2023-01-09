//pd interface
#include "m_pd.h"

// C libs for rand() function
#include <stdio.h>
#include <stdlib.h>

// new class
static t_class *arp_class;



//dataspace of new object
// dont understand x_obj
typedef struct _arp
{
  t_object  x_obj;

  // 2nds inlet, notein float value
  t_inlet *x_in2;

  // float for last pressed note value
  t_float fVal;

  //float for mode, 0 = UP, 1 = DOWN, 2 = RANDOM ---- NOT DONE YET
  t_float mode;

  // int counter for cur arpeggio step
  t_int i_cur;

  // float array to hold note intervals for major scale
  t_float a[8];
} t_arp;


// method called when active inlet gets bang
void arp_bang(t_arp *x)
{
  if(x->mode == 3 || x->mode <= 1)
  {
    outlet_float(x->x_obj.ob_outlet, x->fVal);

    x->i_cur++;
    x->i_cur = x->i_cur%8;
    x->fVal += x->a[x->i_cur];
  }
  else if(x->mode == 2)
  {
    x->i_cur = rand() % 8;
    outlet_float(x->x_obj.ob_outlet, x->fVal + x->a[x->i_cur]);
  }
}


// method called when active inlet gets float
void arp_float(t_arp *x)
{
  post("%f", x->fVal);
  x->i_cur = 7;
}

// constructor, arg unsued rn
void *arp_new(t_floatarg f)
{
  t_arp *x = (t_arp *)pd_new(arp_class);

  post("%f", f);
  x->mode = f;

  x->i_cur = 0;

  // array of major scale intervals for UP pattern
  if(x->mode == 0)
  {
    x->a[0] = 2;
    x->a[1] = 2;
    x->a[2] = 1;
    x->a[3] = 2;
    x->a[4] = 2;
    x->a[5] = 2;
    x->a[6] = 1;
    x->a[7] = -12;
  }
  // DOWN pattern
  else if(x->mode == 1)
  {
    x->a[0] = -2;
    x->a[1] = -2;
    x->a[2] = -1;
    x->a[3] = -2;
    x->a[4] = -2;
    x->a[5] = -2;
    x->a[6] = -1;
    x->a[7] = 12;
  }
  // RANDOM pattern
  else if(x->mode == 2)
  {
    x->a[0] = 0;
    x->a[1] = 2;
    x->a[2] = 4;
    x->a[3] = 5;
    x->a[4] = 7;
    x->a[5] = 9;
    x->a[6] = 11;
    x->a[7] = 12;
  }
  // minor scale I think
  else if(x->mode == 3)
  {
    x->a[0] = 2;
    x->a[1] = 1;
    x->a[2] = 2;
    x->a[3] = 2;
    x->a[4] = 1;
    x->a[5] = 2;
    x->a[6] = 2;
    x->a[7] = -12;
  }
  else
  {
    pd_error(x, " ERROR argument passed to object must be 0 (UP), 1 (DOWN), 2 (RANDOM), or 3 (MINOR)");
  }

  // second passive inlet for notin float value
  floatinlet_new(&x->x_obj, &x->fVal);

  // idk if this actually works but it doesn't not work so I'm leaving it
  outlet_new(&x->x_obj, &s_float);
  return (void *)x;
}


// idk how most of this works , refer to documentation
void arp_setup(void)
{
  arp_class = class_new(gensym("arp"),
      (t_newmethod)arp_new,
      0,
      sizeof(t_arp),
      CLASS_DEFAULT,
      A_DEFFLOAT, 0);

  class_addbang(arp_class, arp_bang);
  class_addfloat(arp_class, arp_float);
}
