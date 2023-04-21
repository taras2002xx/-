package com.taras.streams_lab4

import scala.collection.mutable.ListBuffer
import scala.io.Source

object StreamWork {
  val T = 7
  val N = 6
  val Sr: Array[KeyPoint] = new Array[KeyPoint](N)
  var maxTer: Int = 0

  private val fullPath = "C:\\Users\\taras_shokalo\\Desktop\\graphs\\src\\main\\scala\\"

  def fillThread(): Seq[Stream] = {

    readFromFile("streams.txt").toSeq
  }

  def readFromFile(filePath: String): ListBuffer[Stream] = {
    val streams = new ListBuffer[Stream]

    val bufferedSource = Source.fromFile(fullPath + filePath)
    for (line <- bufferedSource.getLines) {
      val edgeParams = line.split(" ")
        streams += Stream(edgeParams(0).toInt, edgeParams(1).toInt, edgeParams(2).toInt)
    }

    bufferedSource.close

    println(streams)
    streams
  }

  def main(args: Array[String]): Unit = {

    val thread = fillThread()

    for (i <- 0 until N) {
      Sr(i) = KeyPoint(i, 0, 0)
    }

    for (i <- 0 until N)
      for (j <- 0 until T) {
        if (Sr(i).name == thread(j).a)
          Sr(i).output += thread(j).c
        if (Sr(i).name == thread(j).b)
          Sr(i).input += thread(j).c
      }
    Sr(N - 2).input = Sr(N - 2).output
    Sr(N - 1).output = Sr(N - 1).input
    for (i <- 0 until N)
      Sr(i).capacity = Math.max(Sr(i).input, Sr(i).output)
    maxTer = Math.max(Sr(N - 1).capacity, Sr(N - 2).capacity)

    for (j <- 0 until N)
      if (thread(j).b == N - 1)
        Sr(N - 1).capacity -= Math.min(thread(j).c, Sr(thread(j).a).capacity)

    for (i <- N - 3 until(0, -1))
      for (j <- 0 until T)
        if (thread(j).b == i)
          Sr(i).capacity -= Math.min(thread(j).c, Sr(thread(j).a).capacity)

    println("Thread max capacity: " + maxTer)

  }

  case class Stream(a: Int, b: Int, c: Int)

  case class KeyPoint(name: Int, var input: Int, var output: Int) {
    var capacity: Int = 0
  }

  case class Transformer() {
      def numToUpperLetter(num: Int) : String = {
        (num + 65).toString
      }
      def upperLetterToNum(s: Char): Int = s.toInt - 65
  }

}
