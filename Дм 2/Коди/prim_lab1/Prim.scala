тpackage com.taras.prim_lab1


import com.taras.{Edge, Graph}

import scala.collection.mutable.ListBuffer

class Prim(primGraph: Graph) {

  private val vertices = primGraph.getVertices

    def findPrim() : ListBuffer[Edge] = {
      val tree = new Graph(new ListBuffer[Edge])

      val sortedEdges = primGraph.EdgesSortedByWage()

      val graph = new Graph(sortedEdges)
      graph.print()

      addToTree(tree, graph, graph.pop)

      println()
      graph.print()

      while (vertices.nonEmpty) {
        val nextEdge =  findNextMin(graph.edges, tree.edges, tree.edges)
        addToTree(tree, graph, nextEdge)
      }

      println("Tree")
      tree.print()

      tree.edges
    }

  def findNextMin(graph : ListBuffer[Edge], tree : ListBuffer[Edge], initTree: ListBuffer[Edge]) : Edge = {
    if (tree.nonEmpty) {
      if (graph.head.compareVertices(tree.head) && !graph.head.isPresent(vertices)) {
        println(graph.head)
        println(vertices)
        graph.head
      }
      else findNextMin(graph, tree.tail, initTree)
    } else if (graph.nonEmpty) {
      findNextMin(graph.tail, initTree, initTree)
    }
    else Edge("", "", 0)
  }

  def addToTree(tree: Graph, graph: Graph, nextEdge: Edge): Unit = {
    tree.edges += nextEdge
    graph.edges -= nextEdge
    vertices -= nextEdge.vertex1
    vertices -= nextEdge.vertex2
  }

}
