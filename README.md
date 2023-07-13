
Fluxômetro  com arduino e display Nokia 5110


O código foi projeto tendo em vista os seguintes componentes:

1) Um arduino nano  - porém funciona para qualquer arduino

2) Um push button em pull up interno para iniciar e parar a medição do fluxo

3) Dois sensores de fluxo de líquidos que utiliza o efeito hall - nesse caso, não existe este sensor para o proteus, então simulei o funcionamento do sensor, que nada mais é um sensor de efeito hall, que utilizando das interrupções do arduino, contamos o número de pulsos num intervalo de 1 segundo. Observe que na imagem o valor de L/s do Fluxo 2 é a metade extado de litros/min do Fluxo 1, isso porque injeto um sinal quadrado de 5v a 100hz no Fluxo 1 e de 50hz no Fluxo 2.

4) Um display Nokia 5110 de fundo azul, que opera em 5v,  não necessitando de divisores de tensão. (foi utilizado a lib LCD5110_Basic

<p align="center">
  <img src=https://raw.githubusercontent.com/pkaislan123/Flux-metro-com-Arduino/main/simula%C3%A7%C3%A3o_proteus.png title="hover text">
</p>
