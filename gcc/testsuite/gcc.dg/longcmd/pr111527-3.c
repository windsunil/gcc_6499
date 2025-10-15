/* { dg-do run } */
/* { dg-options "@options_128kb_to_2mb.txt" } */

#include <stdio.h>

int main()
{
  printf("Hello world\n");
}
/* { dg-final { output-exists { target *-*-* } } } */
