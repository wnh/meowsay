
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cats.h"
#include "scanner.h"

#define WIDTH 60

void
format_text(char *bleft, char *bright, char *msg)
{
  printf("%s%-60s%s\n", bleft, msg, bright);
}

void
print_usage(int code)
{
  printf("usage: meowsay [-n|-l|-p] text\n");
  exit(code);
}


int
main(int argc, char *argv[])
{
  char bleft[255], bright[255];
  char *cat;
  int cat_len, opt;

  bool picked = false;
  while((opt = getopt(argc, argv, "nlp")) != -1) {
    if (picked) print_usage(1);
    switch(opt) {
    case 'n':
      cat     = nyan_txt;
      cat_len = nyan_txt_len;
      break;
    case 'l':
      cat     = longcat_txt;
      cat_len = longcat_txt_len;
      break;
    case 'p':
      cat     = pusheen_txt;
      cat_len = pusheen_txt_len;
      break;
    default:
	print_usage(1);
    }
  }
  argv += optind;
  char *msg = argv[0];

  // catfile format
  //     line 1: top line
  //     line 2: left padding for speech bubble
  //     line 3: right padding for speech bubble
  //     line 4...: the rest of the cat
  Scanner lcatscan; //ha!
  Scanner *catscan = &lcatscan; //ha!

  ScanInit(catscan, cat, "\n");

  ScanHasNext(catscan);
  printf("%s\n", ScanNext(catscan));

  ScanHasNext(catscan);
  strncpy(bleft, ScanNext(catscan), 255);

  ScanHasNext(catscan);
  strncpy(bright, ScanNext(catscan), 255);

  format_text(bleft, bright, msg);
  while(ScanHasNext(catscan)) {
    printf("%s\n", ScanNext(catscan));
  }
}
