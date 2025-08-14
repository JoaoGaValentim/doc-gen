/**
 * @author João Gabriel Valentim Theodoro
 * @version 0.2
 * @date 2025-08-14
 * */
#include "../include/Document.hpp"
#include <cstdlib>
#include <format>
#include <iostream>
#include <string>
#include <vector>

constexpr std::string VERSION = "VERSION v0.0.3";

void help()
{
  std::cout << "USE THIS COMMANDS:" << '\n';
  std::cout << "  -rg <opt-total> to generate RG" << '\n';
  std::cout << "  -cpf <opt-total> to generate CPF" << '\n';
  std::cout << "  -cnpj <opt-total> to generate CNPJ" << '\n';
  std::cout << "  -h <opt-total> to open this documentation" << '\n';
  std::cout << "  -v or -version show version." << '\n';
}

void version()
{

  std::cout << VERSION << '\n';
}

void generate(std::vector<std::string> &directives, std::string &arg)
{
  bool is_in_directive = std::find(directives.begin(), directives.end(), arg) !=
                         directives.end();
  // Verifica se o argumento está na lista de diretivas
  if (is_in_directive)
  {
    std::string docType = arg.substr(1); // Remove o '-'
    Document document(docType);
    std::cout << std::format("DOCUMENT = {0}", document.generate()) << "\n";
  }

  if (!is_in_directive)
  {
    help();
    return;
  }
}

void execute_commands(std::vector<std::string> directives, int &argc, const char **argv)
{
  std::string arg = argv[1];

  if (arg == "-version" || arg == "-v")
  {
    version();
    return;
  }

  if (arg[0] != '-')
  {
    help();
    return;
  }

  if (argc == 2)
  {
    generate(directives, arg);
    return;
  }

  if (argc == 3)
  {
    int total_args = atoi(argv[2]);
    for (size_t i = 0; i < total_args; i++)
    {
      generate(directives, arg);
    }
    return;
  }
}

void run_app(int argc, const char **argv)
{
  std::vector<std::string> directives{"-rg", "-cpf", "-cnpj"};
  execute_commands(directives, argc, argv);
}

int main(int argc, const char **argv)
{
  if (argc < 2)
  {
    help();
    return EXIT_FAILURE;
  }
  run_app(argc, argv);
  return EXIT_SUCCESS;
}
