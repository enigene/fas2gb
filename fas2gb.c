/*  FASTA to GenBank converter v1.2, 31 Oct 2013
 *  Minimalistic convertion for Percon.
 *  Author: Lev I. Uralsky (Institute of Molecular Genetics, Moscow, Russia)
 *  gcc -Wall -Werror -Os -s -o fas2gb fas2gb-v1.2.c
 *  Usage: fas2gb input.fas > output.gb
 */

#include <stdio.h>
#include <stdlib.h>

static void fas2gb(FILE *fp)
{
  char buffer[4096];
  const int LINE_LEN = 60;
  int i, j;
  int sites = 0;
  int numSitesInLine = 0;
  fpos_t pos;
  _Bool pass = 0;
  _Bool GetSiteLen = 0;

  while (fgets(buffer, sizeof(buffer), fp) != 0) {
    if (buffer[0] == '>') {
      if (GetSiteLen) { printf("\n//\n"); }
      if (pass == 0) {
        if (fgetpos(fp, &pos) == 0) {
          printf("LOCUS      ");
          j = 0;
          while (buffer[j] != '\r' && buffer[j] != '\n') {
            fputc(buffer[j], stdout);
            j++;
          }
          pass = 1;
          sites = 0;
          GetSiteLen = 0;
        }
      } else if (pass == 1) {
        if (fsetpos(fp, &pos) == 0) {
          printf("  %d\n", sites);
          printf("ORIGIN\n          ");
          pass = 0;
          GetSiteLen = 1;
        }
      }
      numSitesInLine = 0;
    } else {
      i = 0;
      while (buffer[i] != '\r' && buffer[i] != '\n') {
        if (GetSiteLen) {
          if (numSitesInLine == LINE_LEN) {
            printf("\n          ");
            numSitesInLine = 0;
          }
          fputc(buffer[i], stdout);
        }
        i++;
        sites++;
        numSitesInLine++;
      }
    }
  }

  if (fsetpos(fp, &pos) == 0) {
    printf("  %d\n", sites);
    printf("ORIGIN\n          ");
    numSitesInLine = 0;
    while (fgets(buffer, sizeof(buffer), fp) != 0) {
      if (buffer[0] != '>') {
        i = 0;
        while (buffer[i] != '\r' && buffer[i] != '\n') {
          if (numSitesInLine == LINE_LEN) {
            printf("\n          ");
            numSitesInLine = 0;
          }
          fputc(buffer[i], stdout);
          i++;
          sites++;
          numSitesInLine++;
        }
      }
    }
  }

  printf("\n//\n");
}

int main(int argc, char **argv)
{
  FILE *fp;
  const char *file;

  if (argc == 1) {
    fas2gb(stdin);
  } else {
    while ((file = *++argv) != 0) {
      if ((fp = fopen(file, "rb")) != 0) {
        fas2gb(fp);
        fclose(fp);
      }
      if (ferror(fp)) {
        /* handle error */
      }
    }
  }
  return(0);
}
