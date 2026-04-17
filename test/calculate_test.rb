require "test/unit"
require_relative "../lib/graph"

class TestCalculate < Test::Unit::TestCase

  def test_grafo0
    filename = "data/grafo0.txt"
    g = Graph.new
    g.load(filename)
    g.calculate

    assert_equal(5, g.cangotos.count)
    assert_equal(4, g.cc.count)
    assert_equal(4, g.cfc.count)
  end

  def test_grafo1
    filename = "data/grafo1.txt"
    g = Graph.new
    g.load(filename)
    g.calculate

    assert_equal(8, g.cangotos.size)
    assert_equal(3, g.cc.size)
    assert_equal(7, g.cfc.size)
  end

  def test_grafo2
    filename = "data/grafo2.txt"
    g = Graph.new
    g.load(filename)
    g.calculate

    assert_equal(8, g.cangotos.count)
    assert_equal(3, g.cc.count)
    assert_equal(5, g.cfc.count)
  end
end