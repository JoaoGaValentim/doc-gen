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
  std::cout << "  -o use with \"docGen [doc] [total >= 1] -o\" generate "
               "[first_doc]_[directive].txt file"
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

int get_total_documents(const char **argv) {
  return !argv[2] ? 1 : std::isdigit(*argv[2]) ? atoi(argv[2]) : 0;
}

void start_generation(std::vector<std::string> &documents,
                      std::vector<std::string> directives, const char **argv,
                      std::string arg) {
  int total = get_total_documents(argv);
  if (total != 0) {
    documents = generate_document_it(total, directives, arg);
    for (auto &document_value : documents) {
      std::cout << std::format("DOCUMENTO = {0}", document_value) << '\n';
    }

    std::string arg_file = argv[3];
    std::string doc_type = arg.substr(1);
    std::string file_name = std::format("{0}_{1}.txt", doc_type, documents[0]);
    if (arg_file == "-o") {
      std::ofstream file(file_name, std::ios::app);
      if (file.is_open()) {
        for (auto &document_value : documents) {
          file << document_value << '\n';
        }
        file.close();
      }
    }
    if (arg_file != "-o") {
      help();
    }
    return;
  }

  help();
  return;
}

void execute_commands(std::vector<std::string> &directives, int &argc,
                      const char **argv) {
  std::string arg = argv[1];
  std::string document{};
  std::vector<std::string> documents{};

  bool is_in_directive =
      std::find(directives.begin(), directives.end(), arg) != directives.end();
  bool show_version = arg == "-version" || arg == "-v";
  bool show_help = !arg.starts_with('-') || !is_in_directive || arg == "-h" ||
                   arg == "-help";

  if (show_version) {
    version();
    return;
  }

  if (show_help) {
    help();
    return;
  }

  if (argc == 2 || argc == 3 || argc <= 4) {
    start_generation(documents, directives, argv, arg);
  }

  if (argc > 4) {
    help();
    return;
  }
}

int run_app(int argc, const char **argv) {
  if (argc < 2) {
    help();
    return EXIT_FAILURE;
  }
  std::vector<std::string> directives{"-rg", "-cpf", "-cnpj"};
  execute_commands(directives, argc, argv);
  return EXIT_SUCCESS;
}
