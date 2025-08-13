#include "../include/Document.hpp"
#include <cstddef>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

Document::~Document() {}

std::string Document::generate() {
  std::string value{};

  for (auto &option : this->options) {
    if (option == "rg" && this->document == option) {
      value = this->generateRG();
      break;
    }

    if (option == "cpf" && this->document == option) {
      value = this->generateCPF();
      break;
    }

    if (option == "cnpj" && this->document == option) {
      value = this->generateCNPJ();
      break;
    }
  }

  return value;
}

int Document::calculateDVCNPJ(const std::vector<int> &digits,
                              const std::vector<int> &weights) {
  int sum = 0;
  for (size_t i = 0; i < digits.size(); ++i) {
    sum += digits[i] * weights[i];
  }

  int mod = sum % 11;
  return (mod < 2) ? 0 : 11 - mod;
}

int Document::calculateDVCPF(const std::vector<int> &digits) {
  int weight = digits.size() + 1; // 10 para o 1º DV, 11 para o 2º DV
  int sum = 0;

  for (size_t i = 0; i < digits.size(); ++i) {
    sum += digits[i] * weight--;
  }

  int mod = sum % 11;
  return (mod < 2) ? 0 : 11 - mod;
}

char Document::calculateDVRG(const std::vector<int> &digits) {
  if (digits.size() != 9)
    throw std::invalid_argument("RG must have exactly 9 digits");

  int sum = 0;
  for (int i = 0; i < 9; ++i) {
    int weight = 10 - i; // Peso decrescendo de 10 até 2
    sum += digits[i] * weight;
  }

  int remainder = sum % 11;
  int dv = 11 - remainder;

  if (dv == 10)
    return 'X';
  else if (dv == 11)
    return '0';
  else
    return '0' + dv;
}

std::string Document::generateRG() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, 9);

  std::vector<int> digits;
  for (int i = 0; i < 9; ++i) {
    digits.push_back(dist(gen));
  }

  char dv = calculateDVRG(digits);

  std::ostringstream rgStream;
  for (int i = 0; i < 9; ++i) {
    rgStream << digits[i];
    if (i == 1 || i == 4)
      rgStream << '.';
    else if (i == 7)
      rgStream << '-';
  }
  rgStream << dv;

  return rgStream.str(); // Ex: 12.345.678-X
}

std::string Document::generateCPF() {
  std::random_device device;
  std::mt19937 gen(device());
  std::uniform_int_distribution<> dist(0, 9);

  std::vector<int> digits;

  // Gera os 9 primeiros dígitos
  for (size_t i = 0; i < 9; ++i) {
    digits.push_back(dist(gen));
  }

  // Calcula o 1º dígito verificador
  int first_digit = calculateDVCPF(digits);
  digits.push_back(first_digit); // Agora temos 10 dígitos

  // Calcula o 2º dígito verificador
  int second_digit = calculateDVCPF(digits);
  digits.push_back(second_digit); // Agora temos 11 dígitos

  std::ostringstream cpfStream;
  for (size_t i = 0; i < digits.size(); ++i) {
    cpfStream << digits[i];
    if (i == 2 || i == 5)
      cpfStream << '.';
    else if (i == 8)
      cpfStream << '-';
  }

  return cpfStream.str();
}

std::string Document::generateCNPJ() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, 9);

  std::vector<int> digits;

  // Gera os 8 primeiros dígitos aleatórios
  for (int i = 0; i < 8; ++i) {
    digits.push_back(dist(gen));
  }

  // Acrescenta os 4 dígitos fixos do sufixo da empresa (0001)
  digits.push_back(0);
  digits.push_back(0);
  digits.push_back(0);
  digits.push_back(1);

  std::vector<int> first_weights = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
  int dv1 = calculateDVCNPJ(digits, first_weights);
  digits.push_back(dv1);

  std::vector<int> last_weights = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
  int dv2 = calculateDVCNPJ(digits, last_weights);
  digits.push_back(dv2);

  // Formatação do CNPJ
  std::ostringstream cnpjStream;
  for (size_t i = 0; i < digits.size(); ++i) {
    cnpjStream << digits[i];
    if (i == 1 || i == 4)
      cnpjStream << '.';
    else if (i == 7)
      cnpjStream << '/';
    else if (i == 11)
      cnpjStream << '-';
  }

  return cnpjStream.str();
}
