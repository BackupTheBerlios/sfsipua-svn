
#include "./gvi_parser.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::string;

GVIParser::GVIParser(void) {
}

GVIParser::~GVIParser(void) {
}

int GVIParser::ParseMetadata(const char *file_name,
							 std::map<string, string> * metadata) {
  ifstream is;
  is.open (file_name, ios::binary );
  if (!is.is_open()) {
    return E_FILE_DOESNT_EXIST;
  }
  RIFF_HEADER riff_header;
  is.read((char *) &riff_header, sizeof(RIFF_HEADER));
  if (is.gcount() != sizeof(RIFF_HEADER)) {
    return E_BAD_FILE_HEADER;
  }
  static const char *kFileHeader = "RIFF";
  static const char *kFileType = "AVI ";
  if (strncmp(riff_header.fourcc, kFileHeader, strlen(kFileHeader)) != 0) {
    return E_BAD_FILE_HEADER;
  }
  if (strncmp(riff_header.file_type, kFileType, strlen(kFileType)) != 0) {
    return E_BAD_FILE_HEADER;
  }
  while (is.good()) {
    CHUNK_HEADER chunk_header;
    is.read((char *) &chunk_header, sizeof(CHUNK_HEADER));
    if (is.gcount() != sizeof(CHUNK_HEADER))
      break;
    static const char *kMetadataChunkHeader = "GMET";
    if (strncmp(chunk_header.ckid, kMetadataChunkHeader,
      strlen(kMetadataChunkHeader)) == 0) {
      // into the google meta-data chunk, read it.
      string s;
      char c;
      string last_key = "";
      string last_val = "";
      for (int j = 0; j < chunk_header.chunk_size; j++) {
        is.get(c);
        if (c == 10) {
          string::size_type index = s.find(':');
          if (index != string::npos) {
            string key = s.substr(0, index);
            string val = s.substr(index+1);
            if (key == last_key) {
              val = last_val + '\n' + val;
            }
            (*metadata)[key] = val;
            last_key = key;
            last_val = val;
          }
          s = "";
        } else {
          s += c;
        }
      }
      return OK;
    } else {
      // advance beyond the data
      is.seekg(chunk_header.chunk_size, ios::cur);
    }
  }
  is.close();
  return E_NO_METADATA;
}
