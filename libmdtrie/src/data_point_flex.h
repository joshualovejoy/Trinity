#ifndef MD_TRIE_DATA_POINT_FLEX_H
#define MD_TRIE_DATA_POINT_FLEX_H

#include "data_point.h"
#include <cstdlib>
#include <cstring>

template <dimension_t DIMENSION>
class data_point_flex: public data_point<DIMENSION>
{
public:
  explicit data_point_flex() {}

  inline morton_t leaf_to_symbol(level_t level) override {

    morton_t result = 0;
    dimension_t dimension = DIMENSION;
    size_t start_index = (trie_node_width * level) % dimension;

    // for (size_t i = 0; i < trie_node_width; i++) {
    for (size_t i = 0; i < level_to_num_children[level]; i++) {

      // TO DO: add condition if need to skip over dimension
      // (cannot just continue because we need to return a
      // trie_node_width sized result)

      size_t add_offset = (start_index + i) / dimension;
      level_t offset = dimension_to_num_bits[(start_index + i) % dimension] - (trie_node_width * level) / dimension - 1 - add_offset;
      point_t coordinate = coordinates_[(start_index + i) % dimension];

      bool bit = GETBIT (coordinate, offset);
      result = (result < 1U) + bit;
    }
    return result;
  }

  inline morton_t leaf_to_full_symbol(level_t level) override {

    morton_t result = 0;
    dimension_t dimension = DIMENSION;

    // for (size_t i = 0; i < trie_node_width; i++) {
    for (size_t i = 0; i < level_to_num_children[level]; i++) {

      bool bit = 1;
      result = (result << 1U) + bit;
    }
    return result;
  }

  inline void update_symbol(data_point *end_range,
                            morton_t current_symbol,
                            level_t level) override
  {

    dimension_t dimension = DIMENSION;
    size_t visited_ct = 0;

    size_t start_index = (trie_node_width * level) % dimension;

    // for (size_t i = 0; i < trie_node_width; i++) {
    for (size_t i = 0; i < level_to_num_children[level]; i++) {

      // TO DO: add condition if need to skip over dimension
      // (cannot just continue because we need to return a
      // trie_node_width sized result)

      visited_ct++;

      size_t add_offset = (start_index + i) / dimension;
      level_t offset = dimension_to_num_bits[(start_index + i) % dimension] - (trie_node_width * level) / dimension - 1 - add_offset;

      point_t start_coordinate = coordinates_[(start_index + i) % dimension];
      point_t end_coordinate = end_range->coordinates_[(start_index + i) % dimension];
      dimension_t symbol_offset = level_to_num_children[level] - visited_ct;

      bool start_bit = GETBIT(start_coordinate, offset);
      bool end_bit = GETBIT(end_coordinate, offset);
      bool symbol_bit = GETBIT(current_symbol, symbol_offset);

      // Bring the start of the search range to second half
      if (symbol_bit && !start_bit)
      {
        start_coordinate =
            start_coordinate & compressed_bitmap::low_bits_unset[offset];
        SETBIT(start_coordinate, offset);
      }
      // Bring the end of the search range to first half
      if (!symbol_bit && end_bit)
      {
        end_coordinate =
            end_coordinate | compressed_bitmap::low_bits_set[offset];
        CLRBIT(end_coordinate, offset);
      }
      coordinates_[i] = start_coordinate;
      end_range->coordinates_[i] = end_coordinate;
    }
  }
};

#endif // MD_TRIE_DATA_POINT_FLEX_H
