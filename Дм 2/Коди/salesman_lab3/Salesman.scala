package com.taras.salesman_lab3

import com.taras.{Edge, Graph}

import scala.collection.mutable.ListBuffer
import scala.util.Random

class Salesman(graph: Graph) {
  var cycle = new ListBuffer[Edge]
  private val edges = graph.edges.clone()
  val vertices = graph.getVertices

  def gamiltonCycle(): Unit = {

    val nextEdge = graph.pop
    println(vertices)

    cycle += nextEdge
    vertices -= nextEdge.vertex1
    vertices -= nextEdge.vertex2

    while (vertices.nonEmpty) {
      val edgesCopy = edges.clone()
      addNextEdge(edgesCopy)
    }

    addLastEdge()
    println(cycle + " length: " + getCycleLength(cycle))

    var swappedCycle = swap()

    for (i <- 0 to 100) {
      println(swappedCycle + " length: " + getCycleLength(swappedCycle))

      if (getCycleLength(swappedCycle) < getCycleLength(cycle)) cycle = swappedCycle

      swappedCycle = swap()
    }
    println("Final cycle: " + cycle + " length: " + getCycleLength(cycle))
  }

  def addNextEdge(edgesCopy: ListBuffer[Edge]): Unit = {
    if (edgesCopy.nonEmpty) {
      if (!edgesCopy.head.isPresent(vertices) && areConnected(cycle.last, edgesCopy.head)) {
        addToCycle(edgesCopy, edgesCopy.head)
        if (edgesCopy.nonEmpty)
          addNextEdge(edgesCopy.tail)
      } else addNextEdge(edgesCopy.tail)
    }
  }

  def swap(): ListBuffer[Edge] = {
    val swappedCycle = new ListBuffer[Edge]
    graph.getVertices
    var randomVertice = ""
    var swapped = " "

    do {
      randomVertice = graph.getVertices.toVector(new Random().nextInt(graph.getVertices.size))
      swapped = graph.getVertices.toVector(new Random().nextInt(graph.getVertices.size))
    } while (randomVertice == swapped)

    println("vertices to swap: " + randomVertice + " " + swapped)

    var edgeWage = 0

    for (edge <- cycle) {
        if (sameVertices(edge, randomVertice, swapped)) {
          swappedCycle += Edge(edge.vertex2, edge.vertex1, edge.wage)
        } else if (edge.vertex1 == randomVertice) {
          edgeWage = getEdgeWage(swapped, edge.vertex2)
          swappedCycle += Edge(swapped, edge.vertex2, edgeWage)
        }
        else if (edge.vertex2 == randomVertice) {
          edgeWage = getEdgeWage(edge.vertex1, swapped)
          swappedCycle += Edge(edge.vertex1, swapped, edgeWage)
        } else if (edge.vertex1 == swapped) {
          edgeWage = getEdgeWage(randomVertice, edge.vertex2)
          swappedCycle += Edge(randomVertice, edge.vertex2, edgeWage)
        } else if (edge.vertex2 == swapped) {
          edgeWage = getEdgeWage(edge.vertex1, randomVertice)
          swappedCycle += Edge(edge.vertex1, randomVertice, edgeWage)
        } else swappedCycle += edge
    }

    swappedCycle
  }

  def getEdgeWage(vertex1: String, vertex2: String): Int = {
      edges.find(e => (e.vertex1 == vertex1 && e.vertex2 == vertex2)
        || (e.vertex1 == vertex2 && e.vertex2 == vertex1)).get.wage
  }

  def sameVertices(edge: Edge, vertex1: String, vertex2: String): Boolean = {
    (edge.vertex1 == vertex1 && edge.vertex2 == vertex2) ||
      (edge.vertex1 == vertex2 && edge.vertex2 == vertex1)
  }

  def addLastEdge(): Unit = {
    for (edge <- edges) {
      if (cycle.last.vertex2 == edge.vertex1) {
        cycle += edge
        return
      }
    }
  }

  def getCycleLength(cycler: ListBuffer[Edge]): Int = {
    var num = 0

    for (edge <- cycler) {
      num += edge.wage
    }
    num
  }

  def addToCycle(edgesCopy: ListBuffer[Edge], nextEdge: Edge): Unit = {
    cycle += nextEdge
    edgesCopy -= nextEdge
    vertices -= nextEdge.vertex1
    vertices -= nextEdge.vertex2
  }

  def areConnected(edge1: Edge, edge2: Edge): Boolean = {
    if (edge1.vertex2 == edge2.vertex1) true
    else false
  }

}
