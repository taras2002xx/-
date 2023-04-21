package com.taras.isomorphism_lab5


import com.taras.{Edge, Graph}

class Isomorphism(isomorphicGraph: Graph) {
  var general: Boolean = false

  def changeVerticeNames(graph: Graph): Unit = {
    val initialVertices = graph.getVertices

    val isFirst = true
    if (graph.edges.length != isomorphicGraph.edges.length) return

    else {
      for (edge <- graph.edges) {
        edge.vertex1 = getVerticeName(edge, isFirst)
        edge.vertex2 = getVerticeName(edge, !isFirst)
      }
    }

    def getVerticeName(edge: Edge, isFirst: Boolean): String = {

      if (isFirst)
        isomorphicGraph.getVertices.toSeq(initialVertices.toSeq.indexOf(edge.vertex1))
      else isomorphicGraph.getVertices.toSeq(initialVertices.toSeq.indexOf(edge.vertex2))
    }

  }

  def antiFlex(graph: Graph, m: Int): Unit = {

    if (m == 0) {
      if (isomorphicGraph.equals(graph)) {
        general = true
      }
    } else {
      for (i <- 0 to m) {
        this.antiFlex(graph, m - 1)
        if (i < m) {
          graph.swap(graph.getVertices.toSeq(i), graph.getVertices.toSeq(m))
          reverse(graph, m - 1)
        }
      }
    }

  }

  def reverse(graph: Graph, m: Int): Unit = {
    var i = 0
    var j = m
    while (i < j) {
      graph.swap(graph.getVertices.toSeq(i), graph.getVertices.toSeq(j))
      i += 1; j -= 1
    }
  }
}
