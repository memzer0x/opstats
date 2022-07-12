#include <iostream>
#include "arguments.h"
#include "section.h"
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv){
  Arguments argumentsList(argc, argv);
  void* section_mem = malloc(4294967295); // Biggest Text Section Size is 4GB which we will allocate
  int section_fd = open(argumentsList.input_file.c_str(), 00);
  
  if(section_fd == -1){
    std::cout << "[ERROR] Fail to open file " << argumentsList.input_file << "\n";
  }
  int section_size = read(section_fd, section_mem, 4294967295);
  if(section_size == -1){
    std::cout << "[ERROR] Fail to read input file, make sure you have proper permissions on the file and try again!\n";
  
  }

  if(argumentsList.search_opcode.find("\\x") != std::string::npos) {
    TextSectionHex section_content = parseTextSectionHex(section_mem, section_size);
    /* Write Algorithm to Loop on Every Values and Check if we find a similar set of Values */
  } else {
    if(argumentsList.opcode_only){
      TextSectionMnemonic section_content = parseTextSectionMnemonic(section_mem, section_size, true);
      section_content.getMnemonicStatistics(argumentsList.search_opcode);
    } else {
      TextSectionMnemonic section_content = parseTextSectionMnemonic(section_mem, section_size, false);
      section_content.getMnemonicStatistics(argumentsList.search_opcode);
    }

  }

  return 0;
}
