#include "section.h"

void TextSectionHex::printTextSectionContent(){
  for(int i = 0; i < this->InstructionList.size(); i++){
    for(int j = 0; j < this->InstructionList[i].size(); j++){
      std::cout << this->InstructionList[i][j] << " ";
    }
    std::cout << "\n";
  }
  return;
}

void TextSectionHex::showMemoryInformations(){
    std::cout << "Address of TextSection in the current context : " << this->sectionAddress << "\n";
    std::cout << "Size in bytes of the text section : " << this->sectionSize << "\n";
    return;
}

void TextSectionMnemonic::printTextSectionContent(){
  for(int i = 0; i < this->InstructionList.size(); i++){
    for(int j = 0; j < this->InstructionList[i].size(); j++){
      std::cout << this->InstructionList[i][j];
    }
    std::cout << "\n";
  }
  return;
}

void TextSectionMnemonic::showMemoryInformations(){
    std::cout << "Address of TextSection in the current context : " << this->sectionAddress << "\n";
    std::cout << "Size in bytes of the text section : " << this->sectionSize << "\n";
    return;
}

TextSectionHex parseTextSectionHex(void* textSectionAddress, size_t textSectionSize){
    TextSectionHex c_TextSection(textSectionAddress, textSectionSize);
    std::vector<uint64_t> currentTextSectionContent;
  
    csh handle;
    cs_insn *insn;
    size_t count;

    if(cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK){
        std::cout << "ERROR: disassembler failed to initialize.\n";
        exit(EXIT_FAILURE);
    }

    count = cs_disasm(handle, textSectionAddress, textSectionSize, (uint64_t)textSectionAddress, 0, &insn);
    if(count > 0){
        size_t j;
        for(j = 0; j < count; j++){
            for (int k = 0; k < insn[j].size; k++) currentTextSectionContent.push_back((uint64_t)insn[j].bytes[k]);
            c_TextSection.InstructionList.push_back(currentTextSectionContent);
            currentTextSectionContent.clear();
        }
        cs_free(insn, count);
    } else {
        std::cout << "ERROR: Failed to disassemble shellcode!\n";
        exit(EXIT_FAILURE);
    }
    cs_close(&handle);
    c_TextSection.instructionCount = c_TextSection.InstructionList.size();
    return c_TextSection;
}

TextSectionMnemonic parseTextSectionMnemonic(void* textSectionAddress, size_t textSectionSize, bool opcode_only){
    TextSectionMnemonic c_TextSection(textSectionAddress, textSectionSize);
  
    csh handle;
    cs_insn *insn;
    size_t count;

    if(cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK){
        std::cout << "ERROR: disassembler failed to initialize.\n";
        exit(EXIT_FAILURE);
    }

    count = cs_disasm(handle, textSectionAddress, textSectionSize, (uint64_t)textSectionAddress, 0, &insn);
    if(count > 0){
        size_t j;
        for(j = 0; j < count; j++){
            std::string currentInstruction = insn[j].mnemonic;
            if(opcode_only){
                c_TextSection.InstructionList.push_back(currentInstruction);
            } else{
                currentInstruction += insn[j].op_str;
                c_TextSection.InstructionList.push_back(currentInstruction);
            }
        }
        cs_free(insn, count);
    } else {
        std::cout << "ERROR: Failed to disassemble shellcode!\n";
        exit(EXIT_FAILURE);
    }
    cs_close(&handle);

    c_TextSection.instructionCount = c_TextSection.InstructionList.size();
    return c_TextSection;
}

uint64_t TextSectionMnemonic::getMnemonicStatistics(std::string& mnemonic){
    uint64_t count = 0;
    for(int i = 0; i < InstructionList.size(); i++){
        if(InstructionList[i] == mnemonic) count += 1;
    }
    std::cout << "[Mnemonic Stastistics]\n";
    std::cout << "Total Number of Instructions : " << InstructionList.size() << "\n";
    std::cout << float((float(count) / InstructionList.size()) * 100) << "\% of the program is " << mnemonic << " instructions!\n";
    return count;
}