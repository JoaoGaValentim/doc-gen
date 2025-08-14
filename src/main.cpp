#include "../include/Document.hpp"
#include <cstdlib>
#include <format>
#include <iostream>
#include <string>
#include <vector>

void help() {
  std::cout << "Use the comands" << '\n';
  std::cout << "  -rg to generate RG" << '\n';
  std::cout << "  -cpf to generate CPF" << '\n';
  std::cout << "  -cnpj to generate CNPJ" << '\n';
  std::cout << "  -h to open this documentation" << '\n';
}

void generate(int argc, const char **argv) {
  std::vector<std::string> directives{"-rg", "-cpf", "-cnpj"};

  if (argc == 2) {
    std::string arg = argv[1];
    // Verifica se começa com '-'
    if (!arg.empty() && arg[0] == '-') {
      // Verifica se o argumento está na lista de diretivas
      if (std::find(directives.begin(), directives.end(), arg) !=
          directives.end()) {
        std::string docType = arg.substr(1); // Remove o '-'
        Document document(docType);
        std::cout << std::format("DOCUMENT = {0}", document.generate()) << "\n";
        return;
      }
    }
  }

  help();
}

int main(int argc, const char **argv) {
  generate(argc, argv);
  return EXIT_SUCCESS;
}
