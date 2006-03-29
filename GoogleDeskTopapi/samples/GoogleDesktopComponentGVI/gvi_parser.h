// Copyright 2006 Google Inc. All rights reserved.

#ifndef GVI_H__
#define GVI_H__

#include <map>
#include <string>

// utility class that parses GVI files.
class GVIParser
{
public:
  GVIParser(void);
  ~GVIParser(void);

  enum ParseStatus {
    OK = 0,
    E_FILE_DOESNT_EXIST = 1,
    E_BAD_FILE_HEADER = 2,
    E_NO_METADATA = 3
  };
  // give me a filename, and i will parse it's meta-data, stuffing
  // it into (metadata) as a (key, value) map. Returns 0 on success,
  // otherwise an error code enumeration:
  static int ParseMetadata(const char *file_name, 
    std::map<std::string, std::string> * metadata);
protected:
 typedef struct {
  char fourcc[4];
  int file_size;
  char file_type[4];
} RIFF_HEADER;
typedef struct {
  char ckid[4];
  int chunk_size;
} CHUNK_HEADER;
};

#endif