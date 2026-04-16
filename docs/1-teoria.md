[< back](../README.md)
---

# 1. Teoría

Empezamos conrextualizando un poco de teoría y luego pasamos a la práctica.

## 1.1 Definiciones

* Un **grafo** es una estructura de datos que representa relaciones entre objetos. Se define formalmente como un conjunto de vértices conectados por aristas.
* Un **nodo** (o vértice) es la unidad básica de un grafo. Representa a un objeto o una entidad individual dentro del sistema.
* Un **arco** (o arista) es la conexión o relación que existe entre dos nodos. Indica que hay un camino o un vínculo entre ellos.
* En un **grafos dirigidos** el arco tiene una dirección (un sentido). Se representa con una flecha (ej. 1 -> 2). 
* En un **grafos no dirigidos** la relación es bidireccional; si 1 está conectado con 2, se asume que 2 también lo está con 1.

## 1.2 Calcular las componentes conexas

**Componentes Conexas (Grafos No Dirigidos)**: En un grafo no dirigido, una componente conexa (CC) es un grupo de nodos donde cualquier par de ellos está conectado por un camino.

Algoritmos:

* Búsqueda en Anchura (BFS) o Profundidad (DFS)

**Componentes Fuertemente Conexas (Grafos Dirigidos)**: En los grafos dirigidos, una componente fuertemente conexa (CFC) es un grupo de nodos donde, para cada par `(u,v)`, existe un camino de `u` a `v` y también de `v` a `u`.

Algoritmos:

* El **algoritmo de Kosaraju**. Utiliza dos pasadas de DFS y el concepto de "grafo transpuesto" (invertir todas las flechas).
* El **algoritmo de Tarjan**: Sólo requiere una sola pasada de DFS.
