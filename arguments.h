#include <string>
#include <iostream>
#include <unistd.h>

class Arguments{
public:
    std::string input_file;
    std::string output_file;
    std::string search_opcode;
    bool check_all = false;
    bool opcode_only = false;
    Arguments(int argc, char** argv);
    void printUsage();
    void printUsage(std::string msg);
private:
    void GetArguments(int argc, char** argv);
};
