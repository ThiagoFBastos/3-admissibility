# 3-admissibility
A partir do número de vértices dado na entrada, o gerador constrói grafos com $2$ $\le$ $\sigma$ $\le$ $3$ e nos
informa: o $diam(G)$, $dT(G)$, $\sigma_{T}(G)$, matriz de adjacências e considerando cada $\sigma$ $\in$ $\{2,3\}$ apresentamos a porcentagem de grafos com um certo valor de $dT(G)$.
Se quisermos encontrar um grafo qualquer $G$ com $\sigma_{T}(G)$ $\le$ $k$, nós supomos que $T$ seja uma de suas árvores geradoras em que $\sigma_{T}(G)$ $=$ $\sigma(T)$ e assim todo par de vértices $(u,v)$ com $1$ $\le$ $d(u,v)$ $\le$ $k$ é uma possível aresta em $G$. Assim, se quisermos todos os $G$ com $\sigma_{T}(G)$ $\le$ $k$ consideramos que qualquer árvore possa ser uma possível árvore geradora com $\sigma_{T}(G)$ $=$ $\sigma(T)$ nos levando a achar todas as árvores rotuladas de $n$ vértices.
Como um grafo pode ter mais de uma árvore geradora, o algoritmo acima pode resultar em grafos duplicados e por isso utilizamos nos algoritmos estruturas que funcionem como um conjunto: Tries, armazenadas na memória principal, e Tabelas Hash, armazenadas em arquivos binários, que armazenam as matrizes de adjacências dos grafos que são tratadas como strings binárias pela Trie e como um números inteiros pela a Tabela Hash.
## Pré Requisitos
* compilador g++ que suporta c++ 17
* POSIX thread
## D(3)+trie+is_2_admissible
Construimos os grafos $G$ com $2$ $\le$ $\sigma$ $\le$ $3$ a partir das árvores com diâmetro igual a três que são obtidas ao selecionar os dois vértices que pertencem ao $c(G)$ e distribuímos os demais entre as vizinhanças dos vértices no centro.
Após isso, encontramos o conjunto $S$ de todos os pares de vértices $(u, v)$, com $2$ $\le$ $d(u, v)$ $\le$ $3$, e para cada subconjunto possível de $S$ criamos um novo grafo $G^{'}$ em que $(u, v)$ $\in$ $E(G^{'})$, desde que $G^{'}$ não possua um vértice universal.  Após isso, utilizamos o algoritmo polinomial para verificar se o grafo é 2-admissível.
### Parâmetros
#### ./generator [n] [d]
##### [n]
Número de vértices do grafo a ser gerado (Tome cuidado com testes em que n $>$ 7)
##### [d]
Nome do arquivo que contém os grafos e suas propriedades
## hash+thread
Encontra todos os grafos que possuam $\sigma_{T}(G)$ $=$ 2 e $\sigma_{T}(G)$ $=$ 3 tirando a vantagem do próprio objetivo para descobrir $\sigma$. Por isso, focamos primeiramente nos que possuem 1 $<$ $\sigma_{T}(G)$ $\le$ 2 e colocamos as matrizes de adjacências em um certo conjunto $S$ (hash), em seguida naqueles com 1 $<$ $\sigma_{T}(G)$ $\le$ $3$ que não estão em $S$ e os colocamos em um conjunto $S^{'}$ (hash). Com isso, os grafos com $\sigma(G)$ $=$ 2 estão em $S$ e os com $\sigma(G)$ $=$ 3 em $S^{'}$.
### Parâmetros
#### ./generator [n] [d]
##### [n]
Número de vértices do grafo a ser gerado
##### [d]
Nome do arquivo que contém os grafos e suas propriedades
## trie+trie+thread
Encontra todos os grafos que possuam $\sigma_{T}(G)$ $=$ 2 e $\sigma_{T}(G)$ $=$ 3 tirando a vantagem do próprio objetivo para descobrir $\sigma$. Por isso, focamos primeiramente nos que possuem 1 $<$ $\sigma_{T}(G)$ $\le$ 2 e colocamos as matrizes de adjacências em um certo conjunto $S$(trie), em seguida naqueles com 1 $<$ $\sigma_{T}(G)$ $\le$ $3$ que não estão em $S$ e os colocamos em um conjunto $S^{'}$(trie). Com isso, os grafos com $\sigma(G)$ $=$ 2 estão em $S$ e os com $\sigma(G)$ $=$ 3 em $S^{'}$.
### Parâmetros
#### ./generator [n] [d]
##### [n]
Número de vértices do grafo a ser gerado (Tome cuidado com testes em que n $>$ 7)
##### [d]
Nome do arquivo que contém os grafos e suas propriedades
### random
Dados o número de vértices $n$ e a quantidade de instâncias à serem geradas $k$, encontramos $k$ grafos obtidos de maneira aleatória que possuam $2$ $\le$ $\sigma_{T}(G)$ $\le$ $3$. Para encontrar um grafo que satisfaça esse requisito, supomos uma de suas árvores geradoras $T$ em que $\sigma(T)$ $=$ $\sigma_{T}(G)$ e adicionamos todas as arestas possíveis em que $\sigma_{T}(G)$ $\le$ $3$. Após isso, utilizamos o algoritmo polinomial para verificar se o grafo é 2-admissível.
#### Parâmetros
##### /generator [n] [i] [d]
###### [n]
Número de vértices do grafo a ser gerado
###### [i]
Número de instâncias a serem geradas
###### [d]
Nome do arquivo que contém os grafos e suas propriedades
## LeitorDoBinario
Lê o arquivo binário e exibe na tela as matrizes de adjacências e os atributos guardados.
### Parâmetros
#### ./tradutor [d]
##### [d]
Nome do arquivo que contém os grafos e suas propriedades 
