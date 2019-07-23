# apache-logs

Trabalho de Estrutura de Dados. Gerenciamento de arquivos de logs do servidor Apache com listas encadeadas.

## Funcionalidades

- Carregar dados dos arquivos de logs do Apache;
- Buscar informações por uma chave de busca;
- Excluir registros especificados;
- Apresentar os campos de cada registro;
- Apresentar a quantidade de ips e usuários repetidos;
- Informar os períodos de maior utilização da rede;

Os arquivos de logs do Apache são lidos e alocados dinamicamente em Listas Duplamente Encadeadas, Não Circulares e Sem Nó Cabeça e todas as funcionalidades do programa são executadas através de funções de manipulação destas listas.

## Desenvolvimento
	
O programa foi desenvolvido em linguagem C, ambiente de desenvolvimento Geany. 

	
## Compilar e Executar 

O programa deve ser compilado com o GCC através do GNU Make e executado em Terminal.

Todas as diretivas de compilação do programa estão descritas no arquivo `Makefile` que se encontra no diretório principal do projeto.

Abrir o Terminal no diretório principal do projeto e digitar:

`$ make`
`$ ./ApacheLogs`

## Autores

- Vinícius Chaves Nascimento
- Rafael Sousa Aragão de Almeida
