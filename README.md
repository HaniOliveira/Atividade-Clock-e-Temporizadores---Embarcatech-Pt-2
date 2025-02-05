# Projeto de Controle de LEDs com Raspberry Pi Pico

## Descrição

Este projeto implementa um sistema de controle de LEDs usando um Raspberry Pi Pico. Quando acionado por um botão, três LEDs (vermelho, verde e azul) acendem simultaneamente e depois se apagam em sequência com intervalos de 3 segundos.

## Componentes Necessários

- Projeto disponibilizado para ser usado no simulador online Wokwi

## Conexões

- LED Vermelho: GPIO 11
- LED Verde: GPIO 12
- LED Azul: GPIO 13
- Botão: GPIO 5 (com pull-up interno habilitado)

## Funcionamento

1. Ao pressionar o botão, todos os LEDs acendem simultaneamente
2. Após 3 segundos, o LED vermelho apaga
3. Após mais 3 segundos, o LED verde apaga
4. Após mais 3 segundos, o LED azul apaga
5. O sistema então fica pronto para um novo ciclo

## Características do Código

- Utiliza callbacks para controle de tempo
- Implementa debounce em software para o botão
- Usa variável global para controle de estado
- Implementa pull-up interno para o botão

## Observações

- O sistema possui proteção contra múltiplos acionamentos durante a execução
- Inclui delay de debounce de 200ms para evitar falsos acionamentos do botão
- Utiliza sleep de 10ms no loop principal para reduzir uso do CPU
