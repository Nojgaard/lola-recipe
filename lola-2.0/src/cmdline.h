/** @file cmdline.h
 *  @brief The header file for the command line option parser
 *  generated by GNU Gengetopt version 2.22.6
 *  http://www.gnu.org/software/gengetopt.
 *  DO NOT modify this file, since it can be overwritten
 *  @author GNU Gengetopt by Lorenzo Bettini */

#ifndef CMDLINE_H
#define CMDLINE_H

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h> /* for FILE */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef CMDLINE_PARSER_PACKAGE
/** @brief the program name (used for printing errors) */
#define CMDLINE_PARSER_PACKAGE PACKAGE
#endif

#ifndef CMDLINE_PARSER_PACKAGE_NAME
/** @brief the complete program name (used for help and version) */
#ifdef PACKAGE_NAME
#define CMDLINE_PARSER_PACKAGE_NAME PACKAGE_NAME
#else
#define CMDLINE_PARSER_PACKAGE_NAME PACKAGE
#endif
#endif

#ifndef CMDLINE_PARSER_VERSION
/** @brief the program version */
#define CMDLINE_PARSER_VERSION VERSION
#endif

enum enum_check { check__NULL = -1, check_arg_none = 0, check_arg_full, check_arg_modelchecking };
enum enum_search { search__NULL = -1, search_arg_depth = 0, search_arg_findpath, search_arg_sweepline, search_arg_covergraph };
enum enum_stubborn { stubborn__NULL = -1, stubborn_arg_tarjan = 0, stubborn_arg_deletion };
enum enum_pathshape { pathshape__NULL = -1, pathshape_arg_linear = 0, pathshape_arg_run, pathshape_arg_fullrun, pathshape_arg_eventstructure };
enum enum_reporter { reporter__NULL = -1, reporter_arg_stream = 0, reporter_arg_socket, reporter_arg_silent };
enum enum_jsoninclude { jsoninclude__NULL = -1, jsoninclude_arg_path = 0, jsoninclude_arg_state };
enum enum_store { store__NULL = -1, store_arg_comp = 0, store_arg_prefix, store_arg_stl, store_arg_bloom };
enum enum_encoder { encoder__NULL = -1, encoder_arg_bit = 0, encoder_arg_copy, encoder_arg_simplecompressed, encoder_arg_fullcopy };
enum enum_ltlmode { ltlmode__NULL = -1, ltlmode_arg_tree = 0, ltlmode_arg_flat };

/** @brief Where the command line options are stored */
struct gengetopt_args_info
{
  const char *help_help; /**< @brief Print help and exit help description.  */
  const char *detailed_help_help; /**< @brief Print help, including all details and hidden options, and exit help description.  */
  const char *full_help_help; /**< @brief Print help, including hidden options, and exit help description.  */
  const char *version_help; /**< @brief Print version and exit help description.  */
  enum enum_check check_arg;	/**< @brief Verify a property (default='modelchecking').  */
  char * check_orig;	/**< @brief Verify a property original value given at command line.  */
  const char *check_help; /**< @brief Verify a property help description.  */
  char * formula_arg;	/**< @brief Check a formula.  */
  char * formula_orig;	/**< @brief Check a formula original value given at command line.  */
  const char *formula_help; /**< @brief Check a formula help description.  */
  char * buechi_arg;	/**< @brief Check a linear time property specified as a Büchi automaton.  */
  char * buechi_orig;	/**< @brief Check a linear time property specified as a Büchi automaton original value given at command line.  */
  const char *buechi_help; /**< @brief Check a linear time property specified as a Büchi automaton help description.  */
  enum enum_search search_arg;	/**< @brief Search the state space using a particular strategy (default='depth').  */
  char * search_orig;	/**< @brief Search the state space using a particular strategy original value given at command line.  */
  const char *search_help; /**< @brief Search the state space using a particular strategy help description.  */
  enum enum_stubborn stubborn_arg;	/**< @brief Apply a particular scheme for computing stubborn sets. (default='tarjan').  */
  char * stubborn_orig;	/**< @brief Apply a particular scheme for computing stubborn sets. original value given at command line.  */
  const char *stubborn_help; /**< @brief Apply a particular scheme for computing stubborn sets. help description.  */
  int cycle_flag;	/**< @brief Apply transition invariant based reduction. (default=off).  */
  const char *cycle_help; /**< @brief Apply transition invariant based reduction. help description.  */
  int symmetry_flag;	/**< @brief Apply symmetry reduction. (default=off).  */
  const char *symmetry_help; /**< @brief Apply symmetry reduction. help description.  */
  int compressed_flag;	/**< @brief Read a compressed file (default=off).  */
  const char *compressed_help; /**< @brief Read a compressed file help description.  */
  char * state_arg;	/**< @brief Print witness state (default='-').  */
  char * state_orig;	/**< @brief Print witness state original value given at command line.  */
  const char *state_help; /**< @brief Print witness state help description.  */
  char * path_arg;	/**< @brief Print witness path (default='-').  */
  char * path_orig;	/**< @brief Print witness path original value given at command line.  */
  const char *path_help; /**< @brief Print witness path help description.  */
  enum enum_pathshape pathshape_arg;	/**< @brief Select the shape of the witness path (default='linear').  */
  char * pathshape_orig;	/**< @brief Select the shape of the witness path original value given at command line.  */
  const char *pathshape_help; /**< @brief Select the shape of the witness path help description.  */
  char * writeCompressed_arg;	/**< @brief Write a compressed file (default='compressedOutput').  */
  char * writeCompressed_orig;	/**< @brief Write a compressed file original value given at command line.  */
  const char *writeCompressed_help; /**< @brief Write a compressed file help description.  */
  int quiet_flag;	/**< @brief Suppress messages. (default=off).  */
  const char *quiet_help; /**< @brief Suppress messages. help description.  */
  enum enum_reporter reporter_arg;	/**< @brief Select a reporting procedure. (default='stream').  */
  char * reporter_orig;	/**< @brief Select a reporting procedure. original value given at command line.  */
  const char *reporter_help; /**< @brief Select a reporting procedure. help description.  */
  char * json_arg;	/**< @brief Output structured data in JSON format. (default='-').  */
  char * json_orig;	/**< @brief Output structured data in JSON format. original value given at command line.  */
  const char *json_help; /**< @brief Output structured data in JSON format. help description.  */
  enum enum_jsoninclude *jsoninclude_arg;	/**< @brief Control which data should be included in the JSON output..  */
  char ** jsoninclude_orig;	/**< @brief Control which data should be included in the JSON output. original value given at command line.  */
  unsigned int jsoninclude_min; /**< @brief Control which data should be included in the JSON output.'s minimum occurreces */
  unsigned int jsoninclude_max; /**< @brief Control which data should be included in the JSON output.'s maximum occurreces */
  const char *jsoninclude_help; /**< @brief Control which data should be included in the JSON output. help description.  */
  int nolog_flag;	/**< @brief Do not send logging information (default=off).  */
  const char *nolog_help; /**< @brief Do not send logging information help description.  */
  short outputport_arg;	/**< @brief Define output port number (default='5555').  */
  char * outputport_orig;	/**< @brief Define output port number original value given at command line.  */
  const char *outputport_help; /**< @brief Define output port number help description.  */
  short inputport_arg;	/**< @brief Define input port number (default='5556').  */
  char * inputport_orig;	/**< @brief Define input port number original value given at command line.  */
  const char *inputport_help; /**< @brief Define input port number help description.  */
  char * address_arg;	/**< @brief Define hostname or IP for reports (default='localhost').  */
  char * address_orig;	/**< @brief Define hostname or IP for reports original value given at command line.  */
  const char *address_help; /**< @brief Define hostname or IP for reports help description.  */
  char * remoteTermination_arg;	/**< @brief Allow remote termination (default='goodbye').  */
  char * remoteTermination_orig;	/**< @brief Allow remote termination original value given at command line.  */
  const char *remoteTermination_help; /**< @brief Allow remote termination help description.  */
  int printNet_flag;	/**< @brief Print the net (default=off).  */
  const char *printNet_help; /**< @brief Print the net help description.  */
  int stats_flag;	/**< @brief Print memory statistics (default=off).  */
  const char *stats_help; /**< @brief Print memory statistics help description.  */
  int tscc_flag;	/**< @brief Use TSCC exploration (default=off).  */
  const char *tscc_help; /**< @brief Use TSCC exploration help description.  */
  int timelimit_arg;	/**< @brief Abort LoLA after the given time has passed.  */
  char * timelimit_orig;	/**< @brief Abort LoLA after the given time has passed original value given at command line.  */
  const char *timelimit_help; /**< @brief Abort LoLA after the given time has passed help description.  */
  int symmtimelimit_arg;	/**< @brief Abort symmetry computation after the given time has passed.  */
  char * symmtimelimit_orig;	/**< @brief Abort symmetry computation after the given time has passed original value given at command line.  */
  const char *symmtimelimit_help; /**< @brief Abort symmetry computation after the given time has passed help description.  */
  int markinglimit_arg;	/**< @brief Abort LoLA after the given number of markings have been explored.  */
  char * markinglimit_orig;	/**< @brief Abort LoLA after the given number of markings have been explored original value given at command line.  */
  const char *markinglimit_help; /**< @brief Abort LoLA after the given number of markings have been explored help description.  */
  enum enum_store store_arg;	/**< @brief Manage visited states using the specified data structure (default='prefix').  */
  char * store_orig;	/**< @brief Manage visited states using the specified data structure original value given at command line.  */
  const char *store_help; /**< @brief Manage visited states using the specified data structure help description.  */
  enum enum_encoder encoder_arg;	/**< @brief Code visited states using the specified coding scheme (default='bit').  */
  char * encoder_orig;	/**< @brief Code visited states using the specified coding scheme original value given at command line.  */
  const char *encoder_help; /**< @brief Code visited states using the specified coding scheme help description.  */
  int bucketing_arg;	/**< @brief Activate bucketing, if the selected store supports it. (default='16').  */
  char * bucketing_orig;	/**< @brief Activate bucketing, if the selected store supports it. original value given at command line.  */
  const char *bucketing_help; /**< @brief Activate bucketing, if the selected store supports it. help description.  */
  short hashfunctions_arg;	/**< @brief Activate the specified number of hash functions for the Bloom filter (default='2').  */
  char * hashfunctions_orig;	/**< @brief Activate the specified number of hash functions for the Bloom filter original value given at command line.  */
  const char *hashfunctions_help; /**< @brief Activate the specified number of hash functions for the Bloom filter help description.  */
  enum enum_ltlmode ltlmode_arg;	/**< @brief Select LTL-state storage mode (default='tree').  */
  char * ltlmode_orig;	/**< @brief Select LTL-state storage mode original value given at command line.  */
  const char *ltlmode_help; /**< @brief Select LTL-state storage mode help description.  */
  int sweepfronts_arg;	/**< @brief Number of fronts that may run simultaneously in the SweepLine method. (default='1').  */
  char * sweepfronts_orig;	/**< @brief Number of fronts that may run simultaneously in the SweepLine method. original value given at command line.  */
  const char *sweepfronts_help; /**< @brief Number of fronts that may run simultaneously in the SweepLine method. help description.  */
  int sweeplinedelay_arg;	/**< @brief Parameter for the SweepLine search strategy (default='100').  */
  char * sweeplinedelay_orig;	/**< @brief Parameter for the SweepLine search strategy original value given at command line.  */
  const char *sweeplinedelay_help; /**< @brief Parameter for the SweepLine search strategy help description.  */
  int sweeplinespread_arg;	/**< @brief Allow spreading of progress values over a larger range. (default='1').  */
  char * sweeplinespread_orig;	/**< @brief Allow spreading of progress values over a larger range. original value given at command line.  */
  const char *sweeplinespread_help; /**< @brief Allow spreading of progress values over a larger range. help description.  */
  int cycleheuristic_arg;	/**< @brief Heuristical parameter for transition invariant based analysis. (default='-1').  */
  char * cycleheuristic_orig;	/**< @brief Heuristical parameter for transition invariant based analysis. original value given at command line.  */
  const char *cycleheuristic_help; /**< @brief Heuristical parameter for transition invariant based analysis. help description.  */
  int retrylimit_arg;	/**< @brief Set number of retries (0 for infinite retries; relevant only for `--search=findpath') (default='0').  */
  char * retrylimit_orig;	/**< @brief Set number of retries (0 for infinite retries; relevant only for `--search=findpath') original value given at command line.  */
  const char *retrylimit_help; /**< @brief Set number of retries (0 for infinite retries; relevant only for `--search=findpath') help description.  */
  int depthlimit_arg;	/**< @brief Set number of transitions to fire before search is aborted or retried (relevant for `--search=findpath'). (default='1000000').  */
  char * depthlimit_orig;	/**< @brief Set number of transitions to fire before search is aborted or retried (relevant for `--search=findpath'). original value given at command line.  */
  const char *depthlimit_help; /**< @brief Set number of transitions to fire before search is aborted or retried (relevant for `--search=findpath'). help description.  */
  short threads_arg;	/**< @brief Set number of threads to be used for parallelization (default='1').  */
  char * threads_orig;	/**< @brief Set number of threads to be used for parallelization original value given at command line.  */
  const char *threads_help; /**< @brief Set number of threads to be used for parallelization help description.  */
  
  unsigned int help_given ;	/**< @brief Whether help was given.  */
  unsigned int detailed_help_given ;	/**< @brief Whether detailed-help was given.  */
  unsigned int full_help_given ;	/**< @brief Whether full-help was given.  */
  unsigned int version_given ;	/**< @brief Whether version was given.  */
  unsigned int check_given ;	/**< @brief Whether check was given.  */
  unsigned int formula_given ;	/**< @brief Whether formula was given.  */
  unsigned int buechi_given ;	/**< @brief Whether buechi was given.  */
  unsigned int search_given ;	/**< @brief Whether search was given.  */
  unsigned int stubborn_given ;	/**< @brief Whether stubborn was given.  */
  unsigned int cycle_given ;	/**< @brief Whether cycle was given.  */
  unsigned int symmetry_given ;	/**< @brief Whether symmetry was given.  */
  unsigned int compressed_given ;	/**< @brief Whether compressed was given.  */
  unsigned int state_given ;	/**< @brief Whether state was given.  */
  unsigned int path_given ;	/**< @brief Whether path was given.  */
  unsigned int pathshape_given ;	/**< @brief Whether pathshape was given.  */
  unsigned int writeCompressed_given ;	/**< @brief Whether writeCompressed was given.  */
  unsigned int quiet_given ;	/**< @brief Whether quiet was given.  */
  unsigned int reporter_given ;	/**< @brief Whether reporter was given.  */
  unsigned int json_given ;	/**< @brief Whether json was given.  */
  unsigned int jsoninclude_given ;	/**< @brief Whether jsoninclude was given.  */
  unsigned int nolog_given ;	/**< @brief Whether nolog was given.  */
  unsigned int outputport_given ;	/**< @brief Whether outputport was given.  */
  unsigned int inputport_given ;	/**< @brief Whether inputport was given.  */
  unsigned int address_given ;	/**< @brief Whether address was given.  */
  unsigned int remoteTermination_given ;	/**< @brief Whether remoteTermination was given.  */
  unsigned int printNet_given ;	/**< @brief Whether printNet was given.  */
  unsigned int stats_given ;	/**< @brief Whether stats was given.  */
  unsigned int tscc_given ;	/**< @brief Whether tscc was given.  */
  unsigned int timelimit_given ;	/**< @brief Whether timelimit was given.  */
  unsigned int symmtimelimit_given ;	/**< @brief Whether symmtimelimit was given.  */
  unsigned int markinglimit_given ;	/**< @brief Whether markinglimit was given.  */
  unsigned int store_given ;	/**< @brief Whether store was given.  */
  unsigned int encoder_given ;	/**< @brief Whether encoder was given.  */
  unsigned int bucketing_given ;	/**< @brief Whether bucketing was given.  */
  unsigned int hashfunctions_given ;	/**< @brief Whether hashfunctions was given.  */
  unsigned int ltlmode_given ;	/**< @brief Whether ltlmode was given.  */
  unsigned int sweepfronts_given ;	/**< @brief Whether sweepfronts was given.  */
  unsigned int sweeplinedelay_given ;	/**< @brief Whether sweeplinedelay was given.  */
  unsigned int sweeplinespread_given ;	/**< @brief Whether sweeplinespread was given.  */
  unsigned int cycleheuristic_given ;	/**< @brief Whether cycleheuristic was given.  */
  unsigned int retrylimit_given ;	/**< @brief Whether retrylimit was given.  */
  unsigned int depthlimit_given ;	/**< @brief Whether depthlimit was given.  */
  unsigned int threads_given ;	/**< @brief Whether threads was given.  */

  char **inputs ; /**< @brief unamed options (options without names) */
  unsigned inputs_num ; /**< @brief unamed options number */
} ;

/** @brief The additional parameters to pass to parser functions */
struct cmdline_parser_params
{
  int override; /**< @brief whether to override possibly already present options (default 0) */
  int initialize; /**< @brief whether to initialize the option structure gengetopt_args_info (default 1) */
  int check_required; /**< @brief whether to check that all required options were provided (default 1) */
  int check_ambiguity; /**< @brief whether to check for options already specified in the option structure gengetopt_args_info (default 0) */
  int print_errors; /**< @brief whether getopt_long should print an error message for a bad option (default 1) */
} ;

/** @brief the purpose string of the program */
extern const char *gengetopt_args_info_purpose;
/** @brief the usage string of the program */
extern const char *gengetopt_args_info_usage;
/** @brief the description string of the program */
extern const char *gengetopt_args_info_description;
/** @brief all the lines making the help output */
extern const char *gengetopt_args_info_help[];
/** @brief all the lines making the full help output (including hidden options) */
extern const char *gengetopt_args_info_full_help[];
/** @brief all the lines making the detailed help output (including hidden options and details) */
extern const char *gengetopt_args_info_detailed_help[];

/**
 * The command line parser
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser (int argc, char **argv,
  struct gengetopt_args_info *args_info);

/**
 * The command line parser (version with additional parameters - deprecated)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param override whether to override possibly already present options
 * @param initialize whether to initialize the option structure my_args_info
 * @param check_required whether to check that all required options were provided
 * @return 0 if everything went fine, NON 0 if an error took place
 * @deprecated use cmdline_parser_ext() instead
 */
int cmdline_parser2 (int argc, char **argv,
  struct gengetopt_args_info *args_info,
  int override, int initialize, int check_required);

/**
 * The command line parser (version with additional parameters)
 * @param argc the number of command line options
 * @param argv the command line options
 * @param args_info the structure where option information will be stored
 * @param params additional parameters for the parser
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser_ext (int argc, char **argv,
  struct gengetopt_args_info *args_info,
  struct cmdline_parser_params *params);

/**
 * Save the contents of the option struct into an already open FILE stream.
 * @param outfile the stream where to dump options
 * @param args_info the option struct to dump
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser_dump(FILE *outfile,
  struct gengetopt_args_info *args_info);

/**
 * Save the contents of the option struct into a (text) file.
 * This file can be read by the config file parser (if generated by gengetopt)
 * @param filename the file where to save
 * @param args_info the option struct to save
 * @return 0 if everything went fine, NON 0 if an error took place
 */
int cmdline_parser_file_save(const char *filename,
  struct gengetopt_args_info *args_info);

/**
 * Print the help
 */
void cmdline_parser_print_help(void);
/**
 * Print the full help (including hidden options)
 */
void cmdline_parser_print_full_help(void);
/**
 * Print the detailed help (including hidden options and details)
 */
void cmdline_parser_print_detailed_help(void);
/**
 * Print the version
 */
void cmdline_parser_print_version(void);

/**
 * Initializes all the fields a cmdline_parser_params structure 
 * to their default values
 * @param params the structure to initialize
 */
void cmdline_parser_params_init(struct cmdline_parser_params *params);

/**
 * Allocates dynamically a cmdline_parser_params structure and initializes
 * all its fields to their default values
 * @return the created and initialized cmdline_parser_params structure
 */
struct cmdline_parser_params *cmdline_parser_params_create(void);

/**
 * Initializes the passed gengetopt_args_info structure's fields
 * (also set default values for options that have a default)
 * @param args_info the structure to initialize
 */
void cmdline_parser_init (struct gengetopt_args_info *args_info);
/**
 * Deallocates the string fields of the gengetopt_args_info structure
 * (but does not deallocate the structure itself)
 * @param args_info the structure to deallocate
 */
void cmdline_parser_free (struct gengetopt_args_info *args_info);

/**
 * Checks that all the required options were specified
 * @param args_info the structure to check
 * @param prog_name the name of the program that will be used to print
 *   possible errors
 * @return
 */
int cmdline_parser_required (struct gengetopt_args_info *args_info,
  const char *prog_name);

extern const char *cmdline_parser_check_values[];  /**< @brief Possible values for check. */
extern const char *cmdline_parser_search_values[];  /**< @brief Possible values for search. */
extern const char *cmdline_parser_stubborn_values[];  /**< @brief Possible values for stubborn. */
extern const char *cmdline_parser_pathshape_values[];  /**< @brief Possible values for pathshape. */
extern const char *cmdline_parser_reporter_values[];  /**< @brief Possible values for reporter. */
extern const char *cmdline_parser_jsoninclude_values[];  /**< @brief Possible values for jsoninclude. */
extern const char *cmdline_parser_store_values[];  /**< @brief Possible values for store. */
extern const char *cmdline_parser_encoder_values[];  /**< @brief Possible values for encoder. */
extern const char *cmdline_parser_ltlmode_values[];  /**< @brief Possible values for ltlmode. */


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* CMDLINE_H */
