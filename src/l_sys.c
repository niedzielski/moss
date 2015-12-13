#include "global.h"
#include "l_sys.h"

static const int PREDECESSOR_OFFSET = '0';

seq_t succeed_predecessor(l_sys_t * const l_sys, char predecessor) {
  int predecessor_index = predecessor - PREDECESSOR_OFFSET;
  return predecessor_index < l_sys->successors_len
    ? sdsnew(l_sys->successors[predecessor_index])
    : sdscatprintf(sdsempty(), "%c", predecessor); // identity production
}

seq_t succeed_predecessors(l_sys_t * const l_sys, seq_t predecessors) {
  seq_t successor = sdsempty();
  for (int i = 0, n = strlen(predecessors); i < n; ++i) {
    seq_t succession = succeed_predecessor(l_sys, predecessors[i]);
    successor = sdscatsds(successor, succession);
    sdsfree(succession);
  }
  return successor;
}

seq_t succeed(l_sys_t * l_sys, int n) {
  seq_t successor = sdsnew(l_sys->axiom);
  for (int i = 0; i < n; ++i) {
    seq_t predecessor = successor;
    successor = succeed_predecessors(l_sys, predecessor);
    sdsfree(predecessor);
  }
  return successor;
}