#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// Estrutura para passar os dados do carro para a thread
typedef struct {
    int car_number;
} Car;

// Função que simula a corrida de um carro
void* corrida_do_carro(void* arg) {
    Car* car = (Car*)arg;
    
    // Tempo aleatório para o carro completar a corrida (simulando a velocidade)
    float tempo_corrida = (rand() % 6 + 5); // Tempo entre 5 e 10 segundos
    printf("Carro %d começou a corrida!\n", car->car_number);
    
    // O carro "corre" por um tempo aleatório
    sleep((int)tempo_corrida);
    
    printf("Carro %d terminou a corrida em %.2f segundos!\n", car->car_number, tempo_corrida);
    
    pthread_exit(NULL);  // Finaliza a thread
}

// Função principal que inicia a corrida
int main() {
    srand(time(NULL));  // Inicializa o gerador de números aleatórios
    
    pthread_t threads[5];  // 5 carros (threads)
    Car carros[5];
    
    // Criando as threads para os carros
    for (int i = 0; i < 5; i++) {
        carros[i].car_number = i + 1;
        if (pthread_create(&threads[i], NULL, corrida_do_carro, (void*)&carros[i]) != 0) {
            perror("Erro ao criar a thread");
            return 1;
        }
    }
    
    // Aguardando todas as threads terminarem
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("A corrida terminou!\n");
    return 0;
}
