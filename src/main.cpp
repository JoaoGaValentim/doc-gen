/**
 * @author João Gabriel Valentim Theodoro
 * @version 0.2
 * @date 2025-08-14
 * */
#include "../include/Document.hpp"
#include <cctype>
#include <cstdlib>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr std::string VERSION = "VERSION v0.0.4";

void help() {
  std::cout << "USE THIS COMMANDS:" << '\n';
  std::cout << "  -rg <opt-total> to generate RG" << '\n';
  std::cout << "  -cpf <opt-total> to generate CPF" << '\n';
  std::cout << "  -cnpj <opt-total> to generate CNPJ" << '\n';
  std::cout << "  -h or -help <opt-total> to open this documentation" << '\n';
  std::cout
      << "  -o [file-name] use with \"docGen [doc] [total >= 1] -o [file]\""
      << "\n";
  std::cout << "  -v or -version show version." << '\n';
}

void version() { std::cout << VERSION << '\n'; }

std::string generate_document(std::vector<std::string> &directives,
                              std::string &arg) {
  bool is_in_directive =
      std::find(directives.begin(), directives.end(), arg) != directives.end();
  std::string docType = arg.substr(1); // Remove o '-'
  Document document(docType);
  return !is_in_directive ? "" : document.generate();
}

std::vector<std::string>
generate_document_it(int &total, std::vector<std::string> &directives,
                     std::string arg) {
std:;
  std::vector<std::string> documents{};
  for (size_t i = 0; i < total; i++) {
    documents.push_back(generate_document(directives, arg));
  }
  return documents;
}

void execute_commands(std::vector<std::string> &directives, int &argc,
                      const char **argv) {
  std::string arg = argv[1];
  std::string document{};
  std::vector<std::string> documents{};
  bool is_in_directive =
      std::find(directives.begin(), directives.end(), arg) != directives.end();

  bool show_help = arg == "-version" || arg == "-v" || !arg.starts_with('-') ||
                   !is_in_directive;

  if (show_help) {
    help();
    return;
  }

  if (arg == "-h" || arg == "-help") {
    help();
    return;
  }

  if (argc == 2 || argc == 3) {
    int total_args = !argv[2] ? 1 : std::isdigit(*argv[2]) ? atoi(argv[2]) : 0;
    if (total_args == 0) {
      help();
      return;
    }
    documents = generate_document_it(total_args, directives, arg);
    for (auto &document_value : documents) {
      std::cout << std::format("DOCUMENTO = {0}", document_value) << '\n';
    }
  }

  if (argc > 3) {
    help();
    return;
  }
}

void run_app(int argc, const char **argv) {
  std::vector<std::string> directives{"-rg", "-cpf", "-cnpj"};
  execute_commands(directives, argc, argv);
}

int main(int argc, const char **argv) {
  if (argc < 2) {
    help();
    return EXIT_FAILURE;
  }
  run_app(argc, argv);
  return EXIT_SUCCESS;
}
