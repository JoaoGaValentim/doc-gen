# Gerador De Documentos Brasileiros (docGen 🇧🇷)

Este projeto tem como principal finalidade gerar documentos brasileiros, tais, como:

- RG (Registro Geral)
- CPF (Cadastro de Pesso Física)
- CNPJ (Cadastro Nacional de Pessoa Juridica)

Ele foi projetado para ser simples e direto ao ponto, rodando via terminal.

## Classe `Document`

A estrutura da classe no cabeçalho `Document.hpp`:

```cpp
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
```
### Características e funcionalidades

- Ao instanciar a classe `Document` da seguinte maneira:
```cpp
    Document doc("cpf"); // tipo de documento que queremos gerar
```
incializaermos o construtor com o parâmetro `std::string document`, que será verificado dentro da
função `std::string generate()`
- Usaremos dessa classe um único método publico: `std::string generate()`, capaz de gerar nosso documento


## Instalando

Para instalar, siga esses passos:

```bash
mkdir build # 1
cd build # 2
cmake .. # 3
make # 4
cd .. # 5
cmake -B build -DCMAKE_INSTALL_PREFIX=/caminho/destino # unix: /usr/local - 6
sudo cmake --install build # 7
```

## Usando

- `-rg` vai gerar um rg
- `-cpf` vai gerar 1
- `-cnpj` vai gerar cnpj
- `-h` vai abrir o menu de ajuda

```bash
docGen -h # help
```

```bash
docGen -rg
```

```bash
docGen -cpf
```

```bash
docGen -cnpj
```
