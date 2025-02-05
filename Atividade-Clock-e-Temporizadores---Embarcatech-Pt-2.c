#include <stdio.h>
#include "pico/stdlib.h"

// Definição dos pinos
#define LED_R 11
#define LED_G 12
#define LED_B 13
#define BOTAO 5

// Variável global para controle do estado
volatile bool em_execucao = false;

// Função de callback para desligar o terceiro LED
int64_t desliga_led3_callback(alarm_id_t id, void *user_data)
{
    gpio_put(LED_B, 0);
    em_execucao = false;
    return 0;
}

// Função de callback para desligar o segundo LED
int64_t desliga_led2_callback(alarm_id_t id, void *user_data)
{
    gpio_put(LED_G, 0);
    add_alarm_in_ms(3000, desliga_led3_callback, NULL, false);
    return 0;
}

// Função de callback para desligar o primeiro LED (vermelho)
int64_t desliga_led1_callback(alarm_id_t id, void *user_data)
{
    gpio_put(LED_R, 0);
    add_alarm_in_ms(3000, desliga_led2_callback, NULL, false);
    return 0;
}

int main()
{
    stdio_init_all();

    // Configuração dos pinos
    gpio_init(LED_R);
    gpio_init(LED_G);
    gpio_init(LED_B);
    gpio_init(BOTAO);

    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_set_dir(LED_B, GPIO_OUT);
    gpio_set_dir(BOTAO, GPIO_IN);

    // Habilita pull-up no botão
    gpio_pull_up(BOTAO);

    uint32_t ultimo_tempo = 0;
    const uint32_t debounce_delay = 200;

    while (true)
    {
        // Debounce em software
        uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());

        if (!gpio_get(BOTAO) && !em_execucao &&
            (tempo_atual - ultimo_tempo) > debounce_delay)
        {
            em_execucao = true;
            ultimo_tempo = tempo_atual;

            // Liga todos os LEDs
            gpio_put(LED_R, 1);
            gpio_put(LED_G, 1);
            gpio_put(LED_B, 1);

            // Inicia a sequência de desligamento
            add_alarm_in_ms(3000, desliga_led1_callback, NULL, false);
        }

        sleep_ms(10); // Pequeno delay para reduzir uso do CPU
    }
}
