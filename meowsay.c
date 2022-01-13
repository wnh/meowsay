
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cats.h"
#include "scanner.h"

#define WIDTH 60

bool	is_whitespace(char c);
bool	is_newline(char c);
bool	is_skip(char c);
void    print_wrapped(const char *bleft, const char *bright, const char *text, int text_len, int wrap_width);
size_t	read_input(char**);
void    print_usage(int code);

int
main(int argc, char *argv[])
{
  char bleft[255], bright[255];
  char *cat;
  int cat_len, opt;

  cat     = nyan_txt;
  cat_len = nyan_txt_len;

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
  size_t msg_len;
  if(msg == NULL) {
    //fprintf(stderr, "[*] whaaa?\n");
    msg_len = read_input(&msg);
    //fprintf(stderr, "[*] read the input\n");
  } else {
    //msg = argv[0];
    msg_len = strlen(msg);
  }
  //fprintf(stderr, "[*] made it after the strlen\n");
  // catfile format
  //     line 1: top line
  //     line 2: left padding for speech bubble
  //     line 3: right padding for speech bubble
  //     line 4...: the rest of the cat
  Scanner lcatscan; //ha!
  Scanner *catscan = &lcatscan; //ha!

  ScanInit(catscan, cat, "\n");

  // First line
  ScanHasNext(catscan);
  printf("%s\n", ScanNext(catscan));

  // Get Left and Right
  ScanHasNext(catscan);
  strncpy(bleft, ScanNext(catscan), 255);
  ScanHasNext(catscan);
  strncpy(bright, ScanNext(catscan), 255);

  print_wrapped(bleft, bright, msg, msg_len, WIDTH);

  // Print the rest
  while(ScanHasNext(catscan)) {
    printf("%s\n", ScanNext(catscan));
  }
}

size_t
read_input(char **input)
{
  int chunk_size = 4096;
  size_t bufsz = chunk_size, start = 0, len = 0;
  char *buf = (char*)calloc(bufsz, sizeof(char));
  //fprintf(stderr, "buf: %p\n", buf);
  for(;;) {
    //fprintf(stderr, "[*] about to read: %p\n", buf+len);
    size_t read = fread(buf+len, sizeof(char), chunk_size, stdin);
    //fprintf(stderr, "[*] read: %lu\n", read);
    len += read;
    // Re allocate if there is more
    if(read >= chunk_size) {
      start = bufsz;
      bufsz += chunk_size;
      //fprintf(stderr, "realloc(%p, %lu)\n", buf, bufsz*sizeof(char));
      buf = (char*)realloc(buf, bufsz*sizeof(char));
    } else if(read == 0) {
      break;
    }
  }
  *input = buf;
  buf[len] = '\0';
  //fprintf(stderr, "buf: %p  len:%lu\n", buf, len);
  return len;
}


void
print_wrapped(const char *bleft, const char *bright, const char *text, int text_len, int wrap_width)
{
  int input_cursor = 0, start = 0, line_cursor = 0;
  char *linebuf = malloc((sizeof(char)*wrap_width) + 1);

  if (linebuf == NULL) {
    perror("line buffer malloc");
    exit(1);
  }

  while(input_cursor < text_len) { // lines
    for(;;) { // lines
      if(input_cursor >= text_len) {
	// were past the end
	//fprintf(stderr, "[*] %-20s \"%-60.60s\n\"", "end", linebuf);
	linebuf[line_cursor] = '\0';
	break;
      } else if(line_cursor >= wrap_width) {
	// we've passed the line length
	//fprintf(stderr, "[*] %-20s \"%-60.60s\"\n", "wrap exeeded", linebuf);
	linebuf[line_cursor] = '\0';
	break;
      } else if(is_skip(text[input_cursor])) {
	// there is a new line
	//fprintf(stderr, "[*] %-16s0x%02hhx \"%-60.60s\"\n", "skip", text[input_cursor], linebuf);
	input_cursor++;
      } else if(is_newline(text[input_cursor])) {
	// just skip over it
	//fprintf(stderr, "[*] %-16s0x%02hhx \"%-60.60s\"\n", "newline", text[input_cursor], linebuf);
	linebuf[line_cursor] = '\0';
	input_cursor++;
	break;
      } else if(text[input_cursor] == '\t') {
	//fprintf(stderr, "[*] %-16s0x%02hhx \"%-60.60s\"\n", "tab", text[input_cursor], linebuf);
	if (line_cursor+8 < wrap_width) {
	  for (int i=0; i<8; i++)
	    linebuf[line_cursor++] = ' ';
	} else {
	  linebuf[line_cursor] = '\0';
	  break;
	}
      } else {
	//fprintf(stderr, "[*] %-16s0x%02hhx \"%-60.60s\"\n", "normal char", text[input_cursor], linebuf);
	linebuf[line_cursor++] = text[input_cursor++];
      }
    }
    //flush
    printf("%s%-60s%s\n", bleft, linebuf, bright);
    line_cursor = 0;
    memset(linebuf, 0, wrap_width+1);
  }
}

bool
is_skip(char c) {
  return (c != '\n') && ((c == '\r') || (c < 0x20) || (c > 0x7E));
}

bool
is_newline(char c) {
  return c == '\n';
}

bool
is_whitespace(char c)
{
  switch(c) {
  case ' ': case '\n': case '\r': case '\t':
    return true;
  default:
    return false;
  }
}

void
print_usage(int code)
{
  printf("usage: meowsay [-n|-l|-p] [text]\n");
  printf("   If no text argument provided text is read from STDIN\n");
  exit(code);
}

