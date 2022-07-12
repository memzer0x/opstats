#include <iostream>
#include <vector>
#include <sys/mman.h>
#include <capstone/capstone.h>

class TextSectionHex{
public:
    uint64_t instructionCount;
    std::vector<uint64_t> uniqueInstructionList;
    std::vector<std::vector<uint64_t>> InstructionList;
    void printTextSectionContent();
    void showMemoryInformations();
    TextSectionHex(void* textSectionAddress, size_t textSectionSize) : sectionAddress(textSectionAddress), sectionSize(textSectionSize){};
private:
    void* sectionAddress;
    size_t sectionSize;
};

class TextSectionMnemonic{
public:
    uint64_t instructionCount;
    std::vector<std::string> uniqueInstructionList;
    std::vector<std::string> InstructionList;
    void printTextSectionContent();
    void showMemoryInformations();
    uint64_t getMnemonicStatistics(std::string& mnemonic);
    TextSectionMnemonic(void* textSectionAddress, size_t textSectionSize) : sectionAddress(textSectionAddress), sectionSize(textSectionSize){};
private:
    void* sectionAddress;
    size_t sectionSize;
};

TextSectionHex parseTextSectionHex(void* textSectionAddress, size_t textSectionSize);
TextSectionMnemonic parseTextSectionMnemonic(void* textSectionAddress, size_t textSectionSize, bool opcode_only);