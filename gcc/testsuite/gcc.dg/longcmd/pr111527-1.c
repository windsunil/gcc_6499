/* { dg-do run } */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define ARGV_LIMIT_SIZE              128 * 1024
#define SYSTEM_LIMIT_SIZE            2 * 1024 * 1024
#define STR_TO_WRITE                 "-DTEST "
void create_large_response_file ()
{
  FILE *fp1, *fp2;
  char buffer[1024];

  strcpy (buffer, STR_TO_WRITE);

  fp1 = fopen ("options_128kb_to_2mb.txt", "wb");
  if (fp1 == NULL)
    {
      abort ();
    }
  while (ftell (fp1) < (ARGV_LIMIT_SIZE + 10))
    {
      fwrite (buffer, strlen (buffer), 1, fp1);
    }
  fclose (fp1);

  fp2 = fopen ("options_greater_then_2mb.txt", "wb");
  if (fp2 == NULL)
    {
      abort ();
    }
  while (ftell (fp2) < (SYSTEM_LIMIT_SIZE +10))
    {
      fwrite (buffer, strlen (buffer), 1, fp2);
    }
  fclose (fp2);
}

int main()
{
  create_large_response_file ();
}
