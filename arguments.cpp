#include "arguments.h"

Arguments::Arguments(int argc, char** argv){
    GetArguments(argc, argv);
}

void Arguments::GetArguments(int argc, char** argv){
    int opt;

    if(argc == 1) printUsage();

    while((opt = getopt(argc, argv, "caf:o:s:x:h")) != -1){
    switch(opt){
      case 'a': this->check_all = true; break;
      case 'c': this->opcode_only = true; break;
      case 'f': this->input_file = optarg;  break;
      case 'o': this->output_file = optarg; break;
      case 's': this->search_opcode = optarg; break;
      case 'h': printUsage();
      default: printUsage("[ERROR] Unexpected argument given to program, use -h to print the help menu.\n");
    }
  }
  if(this->input_file.empty() || this->search_opcode.empty()) {
    printUsage("[ERROR] Did you forget to give a input file and a opcode ?\n");
  }
}

void Arguments::printUsage(){
    std::cout << "USAGE: opcount [OPTIONS]\n";
    std::cout << "  -a <all> check for the frequency of every opcode found in the text section\n";
    std::cout << "  -f <input> file path of your extracted text section\n";
    std::cout << "  -o <output> output the results to a file of choice\n";
    std::cout << "  -s <search> search for the frequency of a single opcode (needed if not using -a switch)\n";
    std::cout << "  -c <opcode> search only for an opcode (e.g 'mov' or 'xor', defaults expects a full instruction 'mov rax, rax' or 'xor rax, rax')\n";
    std::cout << "  -v  verbose mode\n";
    std::cout << "  -? or -h print this help menu\n";
    std::cout << "\n";
    std::cout << "examples : objcopy --dump-section .text=exit.code exit\n";
    std::cout << "           opcount -s 'mov rax, rax' -f exit.code\n";
    std::cout << "           opcount -a -f exit.code\n";
    exit(0);
}

void Arguments::printUsage(std::string msg){
    std::cout << "USAGE: opcount [OPTIONS]\n";
    std::cout << "  -a <all> check for the frequency of every opcode found in the text section\n";
    std::cout << "  -f <input> file path of your extracted text section\n";
    std::cout << "  -o <output> output the results to a file of choice\n";
    std::cout << "  -s <search> search for the frequency of a single opcode (needed if not using -a switch)\n";
    std::cout << "  -c <opcode> search only for an opcode (e.g 'mov' or 'xor', defaults expects a full instruction 'mov rax, rax' or 'xor rax, rax')\n";
    std::cout << "  -v  verbose mode\n";
    std::cout << "  -? or -h print this help menu\n";
    std::cout << "\n";
    std::cout << "examples : objcopy --dump-section .text=exit.code exit\n";
    std::cout << "           opcount -s 'mov rax, rax' -f exit.code\n";
    std::cout << "           opcount -a -f exit.code\n";
    std::cout << "\n";
    std::cout << msg << "\n";
    exit(0);
}
