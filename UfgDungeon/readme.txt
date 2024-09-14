UFG DUNGEON - Jogo em C

Bem-vindo ao Labirinto da Decisão, um emocionante jogo em linguagem C onde você enfrentará desafios, tomará decisões estratégicas e buscará derrotar o temível Minotauro escondido nas entranhas de uma árvore de decisão!

-- INSTRUÇÕES:

  Compilação:

    Certifique-se de ter um compilador C instalado em seu sistema. Para compilar o jogo, utilize o seguinte comando no terminal:

    gcc Tarvore.c Menus.c main.c -o labirinto

  Execução:

    Inicie o jogo digitando o seguinte comando:

    ./labirinto

  Objetivo:

    Seu objetivo é percorrer o labirinto, composto por uma árvore de decisão, e derrotar o Minotauro que se encontra em um dos nós folha. Cada decisão que você toma afeta o caminho que você segue e os desafios que enfrenta.

  Decisões:

    Você pode escolher até 3 rotas diferentes em cada decisão. Digite o número correspondente à rota desejada e pressione Enter para prosseguir.

  Desafios:

    Cada rota está repleta de oponentes que causarão danos ao seu personagem. Gerencie sua vida com sabedoria, pois se perder completamente, o jogo termina.

  Minotauro:

    O Minotauro está escondido em algum lugar das folhas da árvore de decisão. Derrote os oponentes, faça escolhas sábias e chegue até o Minotauro para enfrentar o desafio final.

  Vitória ou Derrota:
  
    O jogo termina quando você derrota o Minotauro ou perde toda a sua vida. Boa sorte aventureiro!

  Representação Gráfica:

    É possível gerar uma representação gráfica da árvore de decisão utilizando a biblioteca Graphviz. Para visualizar a estrutura do labirinto.

    Primeiramente instale a biblioteca Graphviz no seu ambiente Linux com o seguinte comando:

      sudo apt install graphviz
    
    Com a biblioca instalada é possível gerar o png do seu percurso com a seguinte instrução no terminal:

      dot -Tpng tree.dot -o tree.png

    Isso criará um arquivo PNG representando a árvore de decisão. Abra o arquivo para explorar visualmente as opções disponíveis em sua jornada.

--AGRADECIMENTOS

  Este jogo foi desenvolvido com paixão e entusiasmo. Agradeço por jogar e espero que desfrute da jornada pelo Labirinto da Decisão!

  Divirta-se!