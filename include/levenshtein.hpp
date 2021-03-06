/* @(#) $Id: Levenshtein.h,v 1.22 2005/01/13 20:02:56 yeti Exp $ */
#ifndef LEVENSHTEIN_HPP
#define LEVENSHTEIN_HPP

#include <string>
#include <vector>

/* Edit opration type
 * DON'T CHANGE! used ad arrays indices and the bits are occasionally used
 * as flags */
enum LevEditType : uint8_t {
  LEV_EDIT_KEEP = 0,
  LEV_EDIT_REPLACE = 1,
  LEV_EDIT_INSERT = 2,
  LEV_EDIT_DELETE = 3,
  LEV_EDIT_LAST  /* sometimes returned when an error occurs */
};

/* Error codes returned by editop check functions */
enum LevEditOpError : uint8_t {
  LEV_EDIT_ERR_OK = 0,
  LEV_EDIT_ERR_TYPE,  /* nonexistent edit type */
  LEV_EDIT_ERR_OUT,  /* edit out of string bounds */
  LEV_EDIT_ERR_ORDER,  /* ops are not ordered */
  LEV_EDIT_ERR_BLOCK,  /* incosistent block boundaries (block ops) */
  LEV_EDIT_ERR_SPAN,  /* sequence is not a full transformation (block ops) */
  LEV_EDIT_ERR_LAST
};

/* string averaging method (UNUSED yet) */
enum LevAveragingType : uint8_t {
  LEV_AVG_HEAD = 0,  /* take operations from the head */
  LEV_AVG_TAIL,  /* take operations from the tail */
  LEV_AVG_SPREAD,  /* take a equidistantly distributed subset */
  LEV_AVG_BLOCK,  /* take a random continuous block */
  LEV_AVG_RANDOM,  /* take a random subset */
  LEV_AVG_LAST
};

/* Edit operation (atomic).
 * This is the `native' atomic edit operation.  It differs from the difflib
 * one's because it represents a change of one character, not a block.  And
 * we usually don't care about LEV_EDIT_KEEP, though the functions can handle
 * them.  The positions are interpreted as at the left edge of a character.
 */
struct LevEditOp {
  /*LevEditType*/uint8_t type;  /* editing operation type */
  size_t spos;  /* source block position */
  size_t dpos;  /* destination position */
};

/* Edit operation (difflib-compatible).
 * This is not `native', but conversion functions exist.  These fields exactly
 * correspond to the codeops() tuples fields (and this method is also the
 * source of the silly OpCode name).  Sequences must span over complete
 * strings, subsequences are simply edit sequences with more (or larger)
 * LEV_EDIT_KEEP blocks.
 */
struct LevOpCode {
  uint8_t/*LevEditType*/ type;  /* editing operation type */
  size_t sbeg, send;  /* source block begin, end */
  size_t dbeg, dend;  /* destination block begin, end */
};

/* Matching block (difflib-compatible). */
struct LevMatchingBlock {
  size_t spos;
  size_t dpos;
  size_t len;
};

size_t lev_edit_distance(size_t len1, const uint8_t *string1, size_t len2, const uint8_t *string2, bool xcost);
size_t lev_edit_distance(size_t len1, const wchar_t *string1, size_t len2, const wchar_t *string2, bool xcost);

//size_t lev_hamming_distance(size_t len, const uint8_t *string1, const uint8_t *string2);
//size_t lev_u_hamming_distance(size_t len, const wchar_t *string1, const wchar_t *string2);

//double lev_jaro_ratio(size_t len1, const uint8_t *string1, size_t len2, const uint8_t *string2);
//double lev_u_jaro_ratio(size_t len1, const wchar_t *string1, size_t len2, const wchar_t *string2);

//double lev_jaro_winkler_ratio(size_t len1, const uint8_t *string1, size_t len2, const uint8_t *string2, double pfweight);
//double lev_u_jaro_winkler_ratio(size_t len1, const wchar_t *string1, size_t len2, const wchar_t *string2, double pfweight);

//uint8_t* lev_greedy_median(size_t n, const size_t *lengths, const uint8_t *strings[], const double *weights, size_t *medlength);
//wchar_t* lev_u_greedy_median(size_t n, const size_t *lengths, const wchar_t *strings[], const double *weights, size_t *medlength);

//uint8_t* lev_median_improve(size_t len, const uint8_t *s, size_t n, const size_t *lengths, const uint8_t *strings[], const double *weights, size_t *medlength);
//wchar_t* lev_u_median_improve(size_t len, const wchar_t *s, size_t n, const size_t *lengths, const wchar_t *strings[], const double *weights, size_t *medlength);


//uint8_t* lev_quick_median(size_t n, const size_t *lengths, const uint8_t *strings[], const double *weights, size_t *medlength);
//wchar_t* lev_u_quick_median(size_t n, const size_t *lengths, const wchar_t *strings[], const double *weights, size_t *medlength);

//uint8_t* lev_set_median(size_t n, const size_t *lengths, const uint8_t *strings[], const double *weights, size_t *medlength);

//size_t lev_set_median_index(size_t n, const size_t *lengths, const uint8_t *strings[], const double *weights);

//wchar_t* lev_u_set_median(size_t n, const size_t *lengths, const wchar_t *strings[], const double *weights, size_t *medlength);

//size_t lev_u_set_median_index(size_t n, const size_t *lengths, const wchar_t *strings[], const double *weights);


//double lev_edit_seq_distance(size_t n1, const size_t *lengths1, const uint8_t *strings1[], size_t n2, const size_t *lengths2, const uint8_t *strings2[]);

//double lev_u_edit_seq_distance(size_t n1, const size_t *lengths1, const wchar_t *strings1[], size_t n2, const size_t *lengths2, const wchar_t *strings2[]);

//double lev_set_distance(size_t n1, const size_t *lengths1, const uint8_t *strings1[], size_t n2, const size_t *lengths2, const uint8_t *strings2[]);

//double lev_u_set_distance(size_t n1, const size_t *lengths1, const wchar_t *strings1[], size_t n2, const size_t *lengths2, const wchar_t *strings2[]);

//int lev_editops_check_errors(size_t len1, size_t len2, size_t n, const LevEditOp *ops);

//int lev_opcodes_check_errors(size_t len1, size_t len2, size_t nb, const LevOpCode *bops);

//void lev_editops_invert(size_t n, LevEditOp *ops);

//void lev_opcodes_invert(size_t nb, LevOpCode *bops);

//LevMatchingBlock* lev_editops_matching_blocks(size_t len1, size_t len2, size_t n, const LevEditOp *ops, size_t *nmblocks);

LevMatchingBlock* lev_opcodes_matching_blocks(size_t len1, size_t len2, size_t nb, const LevOpCode *bops, size_t *nmblocks);
LevMatchingBlock* lev_opcodes_matching_blocks_2(size_t len1, size_t len2, size_t nb, const LevOpCode *bops, size_t *nmblocks);

//uint8_t* lev_editops_apply(size_t len1, const uint8_t* string1, size_t len2, const uint8_t* string2, size_t n, const LevEditOp *ops, size_t *len);

//wchar_t* lev_u_editops_apply(size_t len1, const wchar_t* string1, size_t len2, const wchar_t* string2, size_t n, const LevEditOp *ops, size_t *len);

//uint8_t* lev_opcodes_apply(size_t len1, const uint8_t* string1, size_t len2, const uint8_t* string2, size_t nb, const LevOpCode *bops, size_t *len);

//wchar_t* lev_u_opcodes_apply(size_t len1, const wchar_t* string1, size_t len2, const wchar_t* string2, size_t nb, const LevOpCode *bops, size_t *len);

LevEditOp* lev_editops_find(size_t len1, const uint8_t *string1, size_t len2, const uint8_t *string2, size_t *n);

LevEditOp* lev_editops_find(size_t len1, const wchar_t *string1, size_t len2, const wchar_t *string2, size_t *n);

//LevEditOp* lev_opcodes_to_editops(size_t nb, const LevOpCode *bops, size_t *n, int keepkeep);

LevOpCode* lev_editops_to_opcodes(size_t n, const LevEditOp *ops, size_t *nb, size_t len1, size_t len2);

//size_t lev_editops_total_cost(size_t n, const LevEditOp *ops);

//size_t lev_opcodes_total_cost(size_t nb, const LevOpCode *bops);

//LevEditOp* lev_editops_normalize(size_t n, const LevEditOp *ops, size_t *nnorm);

//LevEditOp* lev_editops_subtract(size_t n, const LevEditOp *ops, size_t ns, const LevEditOp *sub, size_t *nrem);

/* UNUSED yet */

//void lev_init_rng(unsigned long int seed);

#endif /* not LEVENSHTEIN_HPP */