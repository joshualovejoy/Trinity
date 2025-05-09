#include "benchmark.hpp"
#include "common.hpp"
#include "parser.hpp"
#include "trie.h"
#include <climits>
#include <fstream>
#include <sys/time.h>
#include <unistd.h>
#include <vector>

void github_bench(void)
{

  use_github_setting(GITHUB_DIMENSION, micro_github_size);

  if (trie_width == (dimension_t) -1) {
    trie_width = (dimension_t) GITHUB_DIMENSION;
  }
  else {
    identification_string += "_FLEX_" + std::to_string(trie_width) + "_" + std::to_string(max_tree_node);
  }

  md_trie<GITHUB_DIMENSION> mdtrie(trie_width, max_depth, trie_depth, max_tree_node);
  MdTrieBench<GITHUB_DIMENSION> bench(&mdtrie);
  p_key_to_treeblock_compact = new bitmap::CompactPtrVector(total_points_count);
  std::string folder_name = "microbenchmark/";
  if (identification_string != "")
  {
    folder_name = "optimization/";
  }
  bench.insert(GITHUB_DATA_ADDR,
               folder_name + "github_insert" + identification_string,
               total_points_count,
               parse_line_github);
  bench.get_storage(folder_name + "github_storage" + identification_string);
  bench.lookup(folder_name + "github_lookup" + identification_string);
  bench.range_search(GITHUB_QUERY_ADDR,
                     folder_name + "github_query" + identification_string,
                     get_query_github<GITHUB_DIMENSION>);
}

void nyc_bench(void)
{

  use_nyc_setting(NYC_DIMENSION, micro_nyc_size);

  if (trie_width == (dimension_t) -1) {
    trie_width = NYC_DIMENSION;
  }
  else {
    identification_string += "_FLEX_" + std::to_string(trie_width) + "_" + std::to_string(max_tree_node);
  }

  md_trie<NYC_DIMENSION> mdtrie(trie_width, max_depth, trie_depth, max_tree_node);
  MdTrieBench<NYC_DIMENSION> bench(&mdtrie);
  p_key_to_treeblock_compact = new bitmap::CompactPtrVector(total_points_count);
  std::string folder_name = "microbenchmark/";
  if (identification_string != "")
  {
    folder_name = "optimization/";
  }
  bench.insert(NYC_DATA_ADDR,
               folder_name + "nyc_insert" + identification_string,
               total_points_count,
               parse_line_nyc);
  bench.get_storage(folder_name + "nyc_storage" + identification_string);
  bench.lookup(folder_name + "nyc_lookup" + identification_string);
  bench.range_search(NYC_QUERY_ADDR,
                     folder_name + "nyc_query" + identification_string,
                     get_query_nyc<NYC_DIMENSION>);
}

void tpch_bench(void)
{

  use_tpch_setting(TPCH_DIMENSION, micro_tpch_size);

  if (trie_width == (dimension_t) -1) {
    trie_width = TPCH_DIMENSION;
  }
  else {
    identification_string += "_FLEX_" + std::to_string(trie_width) + "_" + std::to_string(max_tree_node);
  }

  md_trie<TPCH_DIMENSION> mdtrie(trie_width, max_depth, trie_depth, max_tree_node);
  MdTrieBench<TPCH_DIMENSION> bench(&mdtrie);
  p_key_to_treeblock_compact = new bitmap::CompactPtrVector(total_points_count);
  std::string folder_name = "microbenchmark/";
  if (identification_string != "")
  {
    folder_name = "optimization/";
  }
  bench.insert(TPCH_DATA_ADDR,
               folder_name + "tpch_insert" + identification_string,
               total_points_count,
               parse_line_tpch);
  bench.get_storage(folder_name + "tpch_storage" + identification_string);
  bench.lookup(folder_name + "tpch_lookup" + identification_string);
  bench.range_search(TPCH_QUERY_ADDR,
                     folder_name + "tpch_query" + identification_string,
                     get_query_tpch<TPCH_DIMENSION>);
}

void sensitivity_num_dimensions_9(void)
{

  use_tpch_setting(9, micro_tpch_size);
  md_trie<9> mdtrie(9, max_depth, trie_depth, max_tree_node);
  MdTrieBench<9> bench(&mdtrie);
  p_key_to_treeblock_compact = new bitmap::CompactPtrVector(total_points_count);

  bench.insert(TPCH_DATA_ADDR,
               "sensitivity/tpch_insert_dimensions" + identification_string +
                   "_" + "9",
               total_points_count,
               parse_line_tpch);
  bench.get_storage("sensitivity/tpch_storage_dimensions" +
                    identification_string + "_" + "9");
  bench.range_search_random("sensitivity/tpch_query_dimensions" +
                                identification_string + "_" + "9",
                            get_random_query_tpch<9>,
                            micro_tpch_size * selectivity_upper,
                            micro_tpch_size * selectivity_lower);
}

void sensitivity_num_dimensions_8(void)
{

  use_tpch_setting(8, micro_tpch_size);
  md_trie<8> mdtrie(8, max_depth, trie_depth, max_tree_node);
  MdTrieBench<8> bench(&mdtrie);
  p_key_to_treeblock_compact = new bitmap::CompactPtrVector(total_points_count);

  bench.insert(TPCH_DATA_ADDR,
               "sensitivity/tpch_insert_dimensions" + identification_string +
                   "_" + "8",
               total_points_count,
               parse_line_tpch);
  bench.get_storage("sensitivity/tpch_storage_dimensions" +
                    identification_string + "_" + "8");
  bench.range_search_random("sensitivity/tpch_query_dimensions" +
                                identification_string + "_" + "8",
                            get_random_query_tpch<8>,
                            micro_tpch_size * selectivity_upper,
                            micro_tpch_size * selectivity_lower);
}

void sensitivity_num_dimensions_7(void)
{

  use_tpch_setting(7, micro_tpch_size);
  md_trie<7> mdtrie(7, max_depth, trie_depth, max_tree_node);
  MdTrieBench<7> bench(&mdtrie);
  p_key_to_treeblock_compact = new bitmap::CompactPtrVector(total_points_count);

  bench.insert(TPCH_DATA_ADDR,
               "sensitivity/tpch_insert_dimensions" + identification_string +
                   "_" + "7",
               total_points_count,
               parse_line_tpch);
  bench.get_storage("sensitivity/tpch_storage_dimensions" +
                    identification_string + "_" + "7");
  bench.range_search_random("sensitivity/tpch_query_dimensions" +
                                identification_string + "_" + "7",
                            get_random_query_tpch<7>,
                            micro_tpch_size * selectivity_upper,
                            micro_tpch_size * selectivity_lower);
}

void sensitivity_num_dimensions_6(void)
{

  use_tpch_setting(6, micro_tpch_size);
  md_trie<6> mdtrie(6, max_depth, trie_depth, max_tree_node);
  MdTrieBench<6> bench(&mdtrie);
  p_key_to_treeblock_compact = new bitmap::CompactPtrVector(total_points_count);
  bench.insert(TPCH_DATA_ADDR,
               "sensitivity/tpch_insert_dimensions" + identification_string +
                   "_" + "6",
               total_points_count,
               parse_line_tpch);
  bench.get_storage("sensitivity/tpch_storage_dimensions" +
                    identification_string + "_" + "6");
  bench.range_search_random("sensitivity/tpch_query_dimensions" +
                                identification_string + "_" + "6",
                            get_random_query_tpch<6>,
                            micro_tpch_size * selectivity_upper,
                            micro_tpch_size * selectivity_lower);
}

void sensitivity_num_dimensions_5(void)
{

  use_tpch_setting(5, micro_tpch_size);
  md_trie<5> mdtrie(5, max_depth, trie_depth, max_tree_node);
  MdTrieBench<5> bench(&mdtrie);
  p_key_to_treeblock_compact = new bitmap::CompactPtrVector(total_points_count);

  bench.insert(TPCH_DATA_ADDR,
               "sensitivity/tpch_insert_dimensions" + identification_string +
                   "_" + "5",
               total_points_count,
               parse_line_tpch);
  bench.get_storage("sensitivity/tpch_storage_dimensions" +
                    identification_string + "_" + "5");
  bench.range_search_random("sensitivity/tpch_query_dimensions" +
                                identification_string + "_" + "5",
                            get_random_query_tpch<5>,
                            micro_tpch_size * selectivity_upper,
                            micro_tpch_size * selectivity_lower);
}

void sensitivity_num_dimensions_4(void)
{

  use_tpch_setting(4, micro_tpch_size);
  md_trie<4> mdtrie(4, max_depth, trie_depth, max_tree_node);
  MdTrieBench<4> bench(&mdtrie);
  p_key_to_treeblock_compact = new bitmap::CompactPtrVector(total_points_count);

  bench.insert(TPCH_DATA_ADDR,
               "sensitivity/tpch_insert_dimensions" + identification_string +
                   "_" + "4",
               total_points_count,
               parse_line_tpch);
  bench.get_storage("sensitivity/tpch_storage_dimensions" +
                    identification_string + "_" + "4");
  bench.range_search_random("sensitivity/tpch_query_dimensions" +
                                identification_string + "_" + "4",
                            get_random_query_tpch<4>,
                            micro_tpch_size * selectivity_upper,
                            micro_tpch_size * selectivity_lower);
}

void sensitivity_num_dimensions_20(void)
{
  use_tpch_setting(20, micro_tpch_size);
  md_trie<20> mdtrie(20, max_depth, trie_depth, max_tree_node);
  MdTrieBench<20> bench(&mdtrie);
  p_key_to_treeblock_compact = new bitmap::CompactPtrVector(total_points_count);
  // Use fewer points.
  total_points_count /= 100;

  bench.insert(TPCH_DATA_ADDR,
               "sensitivity/tpch_insert_dimensions" + identification_string +
                   "_" + "20",
               total_points_count,
               parse_line_tpch);
  bench.get_storage("sensitivity/tpch_storage_dimensions" +
                    identification_string + "_" + "20");
  bench.range_search_random("sensitivity/tpch_query_dimensions" +
                                identification_string + "_" + "20",
                            get_random_query_tpch<20>,
                            micro_tpch_size * selectivity_upper,
                            micro_tpch_size * selectivity_lower);
}

void sensitivity_selectivity(void)
{

  use_tpch_setting(TPCH_DIMENSION, micro_tpch_size);
  md_trie<TPCH_DIMENSION> mdtrie((dimension_t) TPCH_DIMENSION, max_depth, trie_depth, max_tree_node);
  MdTrieBench<TPCH_DIMENSION> bench(&mdtrie);
  p_key_to_treeblock_compact = new bitmap::CompactPtrVector(total_points_count);

  bench.insert(TPCH_DATA_ADDR,
               "sensitivity/tpch_insert_selectivity" + identification_string,
               total_points_count,
               parse_line_tpch);
  bench.range_search_random("sensitivity/tpch_query_selectivity" +
                                identification_string,
                            get_random_query_tpch<TPCH_DIMENSION>,
                            total_points_count,
                            1);
}

void sensitivity_treeblock_sizes(int treeblock_size)
{
  use_tpch_setting(TPCH_DIMENSION, micro_tpch_size);
  md_trie<TPCH_DIMENSION> mdtrie((dimension_t) TPCH_DIMENSION, max_depth, trie_depth, treeblock_size);
  MdTrieBench<TPCH_DIMENSION> bench(&mdtrie);
  p_key_to_treeblock_compact = new bitmap::CompactPtrVector(total_points_count);
  bench.insert(TPCH_DATA_ADDR,
               "sensitivity/tpch_insert_treeblock_sizes_" + std::to_string(treeblock_size),
               total_points_count,
               parse_line_tpch);

  bench.get_storage("sensitivity/tpch_storage_treeblock_sizes_" + std::to_string(treeblock_size));
  bench.lookup("sensitivity/tpch_lookup_treeblock_sizes_" + std::to_string(treeblock_size));
  bench.range_search(TPCH_QUERY_ADDR,
                     "sensitivity/tpch_query_treeblock_sizes_" + std::to_string(treeblock_size),
                     get_query_tpch<TPCH_DIMENSION>);
}

int main(int argc, char *argv[])
{

  std::string argvalue;
  optimization_code = OPTIMIZATION_SM;
  int arg;
  int sensitivity_dimensions = -1;
  int treeblock_size = -1;
  is_microbenchmark = true;

  while ((arg = getopt(argc, argv, "b:o:d:t:w:m:")) != -1)
    switch (arg)
    {
    case 'b':
      argvalue = std::string(optarg);
      break;
    case 't':
      treeblock_size = atoi(optarg);
      break;
    case 'o':
      optimization = std::string(optarg);
      if (optimization == "SM")
        optimization_code = OPTIMIZATION_SM;
      if (optimization == "B")
        optimization_code = OPTIMIZATION_B;
      if (optimization == "CN")
        optimization_code = OPTIMIZATION_CN;
      if (optimization == "GM")
        optimization_code = OPTIMIZATION_GM;
      break;
    case 'd':
      sensitivity_dimensions = atoi(optarg);
      break;
    case 'w':
      trie_width = (dimension_t) atoi(optarg);
      break;
    case 'm':
      max_tree_node = (preorder_t) atoi(optarg);
      break;
    default:
      abort();
    }

  std::cout << "benchmark: " << argvalue << ", optimization: " << optimization
            << ", dimensions: " << sensitivity_dimensions
            << ", treeblock_size: " << treeblock_size 
            << ", trie_width: " << (int) trie_width
            << ", max_tree_node: " << (int) max_tree_node << std::endl;
  if (argvalue == "tpch")
    tpch_bench();
  else if (argvalue == "github")
    github_bench();
  else if (argvalue == "nyc")
    nyc_bench();
  else if (argvalue == "sensitivity_num_dimensions")
  {
    switch (sensitivity_dimensions)
    {
    case 9:
      sensitivity_num_dimensions_9();
      break;
    case 8:
      sensitivity_num_dimensions_8();
      break;
    case 7:
      sensitivity_num_dimensions_7();
      break;
    case 6:
      sensitivity_num_dimensions_6();
      break;
    case 5:
      sensitivity_num_dimensions_5();
      break;
    case 4:
      sensitivity_num_dimensions_4();
      break;
    default:
      std::cout << "wrong dimensions: " << sensitivity_dimensions
                << std::endl;
      abort();
    }
  }
  else if (argvalue == "sensitivity_selectivity")
    sensitivity_selectivity();
  else if (argvalue == "sensitivity_treeblock_size")
    sensitivity_treeblock_sizes(treeblock_size);
  else
    std::cout << "Unrecognized benchmark: " << argvalue << std::endl;
}