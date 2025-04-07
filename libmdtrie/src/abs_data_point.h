#ifndef MD_TRIE_ABS_DATA_POINT_H
#define MD_TRIE_ABS_DATA_POINT_H

#include "compressed_bitmap.h"
#include "defs.h"         // defines: dimension_t, point_t, level_t, morton_t, n_leaves_t, etc.
#include <cstdlib>
#include <cstring>

template <dimension_t DIMENSION>
class abs_data_point {
public:
  inline point_t *get() { return coordinates_; }

  inline void set(point_t *coordinates) {
    memcpy(coordinates_, coordinates, sizeof(point_t) * DIMENSION);
  }

  inline point_t get_coordinate(dimension_t index) {
    return coordinates_[index];
  }

  inline void set_coordinate(dimension_t index, point_t value) {
    coordinates_[index] = value;
  }

  inline void set_primary(n_leaves_t value) { primary_key_ = value; }

  inline n_leaves_t read_primary() { return primary_key_; }

  uint64_t coordinate_to_raw_morton()
  {
    uint64_t result = 0;

    // note: 32 might need to change depending on width
    // however, this function isn't called anywhere yet
    for (level_t level = 0; level < 32; level++)
    {
      for (size_t i = 0; i < DIMENSION; i++)
      {
        level_t offset = DIMENSION - level - 1;
        point_t coordinate = coordinates_[i];

        bool bit = GETBIT(coordinate, offset);
        result = (result << 1U) + bit;
      }
    }
    return result;
  }

  std::vector<int32_t> generate_vector()
  {
    std::vector<int32_t> return_pt(DIMENSION);

    for (unsigned i = 0; i < DIMENSION; i++)
    {
      return_pt[i] = coordinates_[i];
    }

    return return_pt;
  }

  virtual void copy_from(abs_data_point<DIMENSION>& other) = 0;

  // Create a polymorphic copy of the object.
  virtual abs_data_point<DIMENSION>* clone() const = 0;

  // Functions to convert the coordinates into Morton symbols.
  virtual morton_t leaf_to_symbol(level_t level) = 0;
  virtual morton_t leaf_to_full_symbol(level_t level) = 0;

  // Update the symbol for range search purposes.
  virtual void update_symbol(abs_data_point<DIMENSION>* end_range, morton_t current_symbol, level_t level) = 0;

protected:
  /**
   * Data point struct is used both to represent a data point and the return
   * "struct" for range search Range search can either return a vector of
   * coordinates or a vector of primary keys
   */
    point_t coordinates_[DIMENSION];
    n_leaves_t primary_key_;
};

#endif // MD_TRIE_ABS_DATA_POINT_H