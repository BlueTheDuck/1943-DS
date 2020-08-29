#include "nf_lib.h"
#include <nds.h>

#include <stdio.h>

int main(int argc, char *argv[]) {
  consoleDemoInit();
  iprintf("Hello!\n");
  for (;;) {
    swiWaitForVBlank();
  }
  return 0;
}