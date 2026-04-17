[<< back](../README.md)
---

# 3. El algoritmo **can-go-to**

Este programa se basa en la estructura de datos `cangotos[]` para calcular las `cc`y las `cfc`.

La estructura de datos `cangotos[i]`, establece para un nodo `i`, cuáles son los nodos a los que se puede llegar avanzando los por arcos (aristas) teniendo en cuanta su dirección (o sentido).

## 3.1 Estructura del programa

Ficheros del proyecto:

```
grafo
├── lib
│   ├── calculate.rb
│   ├── graph.rb
│   ├── load.rb
│   └── show.rb
├── test/...
├── debug.rb
└── main.md
```

* `main.rb`: es el fichero principal del proyecto.
    1. Lee el argumento
    2. Crea un objeto `Graph`.
    3. Carga el `FILENAME`.
    4. Hace los cálculos y muestra por pantalla.
* `lib/`: En esta carpeta están las definiciones de las clases.
* `lib/graph.rb`: Define la clase `Graph`.
* `lib/load.rb`: Define los métodos para cargar el contenido del fichero.
* `lib/show.rb`: Define los métodos que muestran los datos por pantalla.
* `lib/calculate.rb`: Define los métodos que realizan los cálculos.
* `debug.rb`: es igual que `main.rb`, pero muestra más información por pantalla.
* `test/`: en esta carpeta tenemos los tests. Para ejecutar todos los test podemos ejecutar el comando `rake` o el fichero principal `ruby test/all_tests.rb`.

## 3.2 Debug

Si ejecutamos el programa `debug.rb`con un grafo vemos ahora se muestra además una sección llamada "cangotos". Esta información se calcula internamente como un paso previo al cálculo de las componentes conexas (`cc`) y de las componentes fuertemente conexas (`cfc`).

La variable `cangotos`, representa para cada nodo N, el subconjunto de todos los nodos, a los que se puede llegar avanzando por los arcos (aristas) siguiendo el sentido (dirección) de los arcos.

A parir de esta información se puede calcular:

* `cc`: con 8 líneas de código no recursivo (método `calculate_cc()`).
* `cfc`: con 13 líneas de código no recursivo (método `calculata_cfc()`).

## 3.3 Calcular CC

```ruby
def calculate_cc
  @cc = []
  frees = @nodes.dup
  @nodes.each do |node|
    next unless frees.include? node

    component = [node] + @cangotos[node]
    frees -= component
    @cc << component
  end
end
```

## 3.4 Calcular CFC

```ruby
  def calculate_cfc
    @cfc = []
    frees = @nodes.dup
    @nodes.each do |node1|
      next unless frees.include? node1

      component = [node1]
      @cangotos[node1].each do |node2|
        if @cangotos[node2].include?(node1)
          component << node2
          frees -= component
        end
      end
      @cfc << component
    end
  end
```

## 3.5 Debug: ejemplo grafo1

* Ejecutar el ejemplo en modo "debug":

```bash
$ ruby debug.rb data/grafo1.txt

Graph (filename: data/grafo1.txt)
  > nodes (7)
  > arcs  (4)
    | 1 --> 2
    | 2 --> 3
    | 4 --> 5
    | 4 --> 6
  > cangotos:
    | node 1 -> 2, 3
    | node 2 -> 3
    | node 3 -> 
    | node 4 -> 5, 6
    | node 5 -> 
    | node 6 -> 
    | node 7 -> 
  > cc  (3)
    | cc  1 ==> [1, 2, 3]
    | cc  2 ==> [4, 5, 6]
    | cc  3 ==> [7]
  > cfc (7)
    | cfc 1 ==> [1]
    | cfc 2 ==> [2]
    | cfc 3 ==> [3]
    | cfc 4 ==> [4]
    | cfc 5 ==> [5]
    | cfc 6 ==> [6]
    | cfc 7 ==> [7]
```

La información que devuelve `cangotos` indica que si avanzamos por los arcos dirigidos, tenemos que:

* Desde el nodo 1, podemos llegar (`can go to`) a los nodos 2 y 3.
* Desde el nodo 2, podemos llegar al nodos 3.
* Desde el nodo 3, no llegamos a ningún nodo.
* Desde el nodo 4, podemos llegar (`can go to`) a los nodos 5 y 6.
* Desde los nodos 5, 6 y 7, no llegamos a ningún nodo.

> NOTA: Esta información de los `cangotos[i]`, nos será muy útil para calcular los `cc` y los `cfc` de forma sencilla.

## 3.6 Debug: ejemplo grafo2

* Ejecutar el ejemplo en modo "debug":

```bash
$ ruby debug.rb data/grafo2.txt 
Graph (filename: data/grafo2.txt)
  > nodes (7)
  > arcs  (5)
    | 1 --> 2
    | 2 --> 3
    | 3 --> 1
    | 4 --> 5
    | 4 --> 6
  > cangotos:
    | node 1 -> 2, 3
    | node 2 -> 3, 1
    | node 3 -> 1, 2
    | node 4 -> 5, 6
    | node 5 -> 
    | node 6 -> 
    | node 7 -> 
  > cc  (3)
    | cc  1 ==> [1, 2, 3]
    | cc  2 ==> [4, 5, 6]
    | cc  3 ==> [7]
  > cfc (5)
    | cfc 1 ==> [1, 2, 3]
    | cfc 2 ==> [4]
    | cfc 3 ==> [5]
    | cfc 4 ==> [6]
    | cfc 5 ==> [7]
```
