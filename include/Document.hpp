#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <string>
#include <vector>
/**
 *
 *  This class is used to generate Brazil Documents (RG, CPF & CNPJ)
 *  - RG xx.xxx.xxx-xx
 *  - CPF xxx.xxx.xxx-xx
 *  - CNPJ xxx.xxx.xxx/xxxx-xx
 *
 * */
class Document {
public:
  Document(std::string document) : document(document) {};
  ~Document();
  std::string generate();

private:
  const std::vector<std::string> options{"rg", "cpf", "cnpj"};
  const std::string document;
  std::string generateCPF();
  std::string generateRG();
  std::string generateCNPJ();
  int calculateDVCPF(const std::vector<int> &documetDigits);
  int calculateDVCNPJ(const std::vector<int> &digits,
                      const std::vector<int> &weights);
  char calculateDVRG(const std::vector<int> &documetDigits);
};

#endif
