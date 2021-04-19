#include <iostream>
#include "uci.h"
#include "string.h"
#include "stdlib.h"

#define DUDU_UCI_START(PACKAGE, SECTION) class PACKAGE##SECTION { \
 private: \
  struct uci_context *context; \
  std::string package = #PACKAGE; \
  std::string section = #SECTION; \
  std::string basePath = package + "." + section; \
 public: \
  PACKAGE##SECTION() { \
    context = uci_alloc_context(); \
  } \
  ~PACKAGE##SECTION() { \
    uci_free_context(context); \
  }
#define DUDU_UCI_END };

#define DUDU_UCI_INT(INT_VAL) \
 private: \
  int INT_VAL; \
 public: \
  int get##INT_VAL() { \
    std::string option = #INT_VAL; \
    std::string optionPath = basePath + "." + option; \
    struct uci_ptr ptr; \
    if (UCI_OK != uci_lookup_ptr(context, &ptr, (char*)optionPath.c_str(), true)) { \
        uci_perror(context, "not found!\n"); \
        return -1; \
    } \
    return atoi(ptr.o->v.string); \
  }

#define DUDU_UCI_STRING(STRING_VAL) \
 private: \
  std::string STRING_VAL; \
 public: \
  std::string get##STRING_VAL() { \
    std::string option = #STRING_VAL; \
    std::string optionPath = basePath + "." + option; \
    struct uci_ptr ptr; \
    if (UCI_OK != uci_lookup_ptr(context, &ptr, (char*)optionPath.c_str(), true)) { \
        uci_perror(context, "not found!\n"); \
        return ""; \
    } \
    return ptr.o->v.string; \
  }
