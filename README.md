
![Thumbnail R-type](https://user-images.githubusercontent.com/93229568/197653776-d8cfa24e-c242-4f99-8b78-023ddccf92ea.jpg)


# Trabalho final da disciplina de Desenvolvimento de software

O objetivo deste trabalho é desenvolver um jogo eletrônico gráfico semelhante às versôes clássicas (antigas) da franquia R-type. 
R-Type é um videogame de fliperama de rolagem horizontal desenvolvido e lançado pela Irem em 1987. 
O jogador controla uma nave estelar, a R-9 “Arrowhead”, em seus esforços para destruir o Bydo, uma poderosa raça alienígena curvada em exterminar toda a humanidade. 
A versão arcade foi distribuída pela Nintendo na América do Norte; é o último título de arcade distribuído pela Nintendo. 
É o primeiro jogo da série R-Type. O jogo é composto por vários níveis sequenciais, com um chefe inimigo no final de cada um. 
O jogador controla uma pequena nave espacial e deve navegar pelo terreno e lutar contra os inimigos usando as várias armas da nave. 
A nave espacial do jogador tem, por padrão, uma arma principal fraca, mas de disparo rápido; e uma arma mais poderosa chamada canhão de ondas, 
que exige que o jogador segure o fogo para aumentar a força do canhão.

Baseando no jogo foi feita uma apresentação com o objetivo de mostrar as grandes áreas que um engenheiro de sistemas pode agregar. Ainda fazendo melhorias no jogo em relação a desempenho gráficos.

<details>
  <summary><b>Slides da apresentação<b/></summary>
    
![Slide1](https://user-images.githubusercontent.com/93229568/166400803-8ed13b47-df6d-4fb5-aabb-69f736497b69.jpg)
![Slide2](https://user-images.githubusercontent.com/93229568/166400809-d28aa32a-8859-4b15-affc-e0509abc5abe.jpg)
![Slide3](https://user-images.githubusercontent.com/93229568/166400811-d15ce646-6457-40a1-8cc2-23fb915983d2.jpg)
![Slide4](https://user-images.githubusercontent.com/93229568/166400812-879340b0-d34d-4634-a654-2f168abbb365.jpg)
![Slide5](https://user-images.githubusercontent.com/93229568/166400813-fa42c5a7-2782-474b-a888-446f211d58a6.jpg)
![Slide6](https://user-images.githubusercontent.com/93229568/166400815-994e6034-3940-48f2-a231-0eedfaca97e5.jpg)
![Slide7](https://user-images.githubusercontent.com/93229568/166400816-c0298963-c87b-4d4c-921f-b9eaac8a92cb.jpg)
![Slide8](https://user-images.githubusercontent.com/93229568/166400818-03b3ed8a-132a-439e-99f3-d60557dbc905.jpg)
![Slide9](https://user-images.githubusercontent.com/93229568/166400819-f6644c95-d730-462f-be76-13a37a767d4c.jpg)
![Slide10](https://user-images.githubusercontent.com/93229568/166400820-2613a18e-6f00-4c3f-be0a-a0754c8ddede.jpg)
![Slide11](https://user-images.githubusercontent.com/93229568/166400821-99b17c55-0661-4342-ae50-dd16aa32835b.jpg)
![Slide12](https://user-images.githubusercontent.com/93229568/166400822-1d358d34-7bdb-41af-828c-82fb749ce062.jpg)
![Slide13](https://user-images.githubusercontent.com/93229568/166400823-107900c0-3dd5-4e8c-9610-6cae8b4055db.jpg)
![Slide14](https://user-images.githubusercontent.com/93229568/166400824-b8b3efad-fa0a-433c-b05f-2208562705b1.jpg)
![Slide15](https://user-images.githubusercontent.com/93229568/166400826-e88ed830-7d4f-47d9-9553-9c7b5a5430d0.jpg)
    
</details>
  
## 🔨 Funcionalidades/Regras do jogo

  - `Controle preciso dos movimentos da nave`:  O jogador deve ter acesso a teclas que controlam a
movimentação da nave e essa deve responder aos comandos do jogador. As teclas escolhidas foram as setas.
  
  - `Tiro básico`:  O jogador deve ter acesso a uma tecla que dispara o tiro do canhão do tanque. O tiro não deve 
mudar de direção depois que ele foi lançado e só deve para depois que ele sair da tela ou colidir: 1) com o tanque inimigo 
ou 2) com um obstáculo do cenário. Além disso, um canhão só pode disparar 1 tiro por vez. A tecla utilizada para o tiro foi o espaço.
  
  - `Tiro avançado`:  Ao segurar o botão de tiro, o tiro deve aumentar de tamanho e, quando disparado no
seu tamanho máximo, deve ser capaz de eliminar todos os inimigos que estejam em sua rota.
  
  - `Bloco`:  O cenário deve conter pelo menos um bloco que elimina o jogador e inimigos que colidem com
ele. Além disso, blocos devem ter tamanhos e posições variáveis, mas devem ocupar, no mínimo, um
quinto da altura da tela e devem ter comprimento pelo menos equivalente à largura da tela. Enquanto
inimigos podem ser destruídos, blocos não podem.
  
  - `Controle de coliões`:  Os objetos presentes no cenário não podem se sobrepor. Tiros não podem
atravessar obstáculos e nem inimigos. Da mesma forma, os movimentos dos inimigos e da nave do
jogador devem ser limitados aos espaços vazios do cenário, ou seja, não podem sair da tela e não
podem atravessar blocos.
 
  - `Pontuação`: Cada inimigo destruído deve aumentar a pontuação do jogador. Inimigos devem oferecer
valores em pontuação diferentes, de acordo com algum critério (ex: tamanho). O cenário deve exibir
os pontos ganhos pelos jogadores.
  
  - `Fim de jogo`:  O jogo deve terminar quando o jogador colidir com um inimigo ou com um bloco.
  
  - `Recorde`:  A maior pontuação registrada (recorde) deve ser armazenada em um arquivo. O valor do
recorde deve ser exibido sempre que o personagem terminar o jogo de forma vitoriosa. Se além disso
ele também bater o recorde, uma mensagem informativa deve ser apresentada para ele. 


## ✔️ Técnicas e tecnologias utilizadas

- `Linguagem C`
- `Biblioteca Allegro5`
- `Windows - MinGW`

## 📁 Acesso ao projeto

Você pode acessar o codigo fonte que foi desenvolvido para jogo [aqui](https://github.com/lfelipesal/R-type/blob/main/tp.c).

## 🛠️ Abrir e rodar o projeto

Para jogar o que foi desenvolvido basta clonar esse repositório na maquina local no ambiente Windows, entrar na pasta pelo prompt de comando(cmd),
e dentro da pasta digitar o comando make.
