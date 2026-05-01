# Exemplo ROS2
Esse projeto é um exemplo simples de conceitos importantes de ros2 na prática, nele exploramos os conceitos de pacotes, cmake, nós, pub/sub, parametros e launcher

Utilizamos como exemplo um sistema de leitura e filtraçao de sensores

## A estrutura
Foram criados dois pacotes, um para leitura de pacotes, onde há dois nós, um leitor de sensores, e um emulador de sensores, e um para filtração de pacotes, onde há um nó para filtração que ilustra o uso de parametros, com seu max\_deviation

## Compilando
Para compilar, é so utilizar o colcon no diretorio raiz do projeto

``` bash
$ colcon build
```

## Utilizando
### Rodando Manualmente
Primeiramente, podemos rodar os nós individualmente
Começamos rodando o filtro, no pacote sensor\_filter, rodamos o nó telemetry\_filter

```bash
# se estiver em zsh ou outro terminal, utilize o setup correspondente
$ source install/setup.bash
$ ros2 run sensor_filter telemetry_filter
```

O nó de filtro já esta rodando, mas ele não recebe nenhuma informação para filtrar, podemos mandar uma mensagem pelo terminal, e devemos ver ele receber essa mensagem.
Em outro terminal rode:

```bash
$ source install/setup.bash
$ ros2 topic pub --once /telemetria apresentacao_interfaces/msg/Telemetria "{ velocidade: 200.0 }"
```

Agora, vamos rodar o sensor\_emulator, do pacote sensor\_comunication, para mandar valores aleatorios ao filtro:
```bash
$ ros2 run sensor_comunication sensor_emulator
```

Agora você deve ver os dois nós se comunicando

### Parametros
Podemos utilizar os parametros para alterar o funcionamento de um nó, ou as constantes que ele usa sem reescrever código ou recompilar o nó.
No nó telemetry\_filter temos o parametro max\_deviation, que controla quao estrito o filtro é, e tem um valor padrão de 2.0, mas podemos alterar o valor desse parametro quando rodamos o nó:

No terminal que roda telemetry\_filter termine o processo (Cntrl-c), e rode:
```bash
$ ros2 run sensor_filter telemetry_filter --ros-args -p max_deviation:=0.5
```
Podemos ver também que é muito mais provavel que uma mensagem seja filtrada

### Launch
O launch é um jeito de rodar todos os nós com um commando só programaticamente, e é parte do pacote startup que também foi criado.

Para utilizar o launch, podemos terminar todos os nós, e rodar no terminal:
```bash
$ ros2 launch startup all_nodes.py
```

O launcher também pode utilizar parametros, como o simples max\_deviation que passa esse parametro para o filter, ou parametros como use\_real, que determina se utilizamos o nó emulador ou o real:
```bash
$ ros2 launch startup all_nodes.py use_real:=true
# ou use_real:= false
# pode-se combinar também com max_deviation:=...
```
