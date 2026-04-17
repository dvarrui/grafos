require "test/unit"
require_relative "../lib/graph"

class TestLoad < Test::Unit::TestCase

  def test_load_grafo0
    filename = "data/grafo0.txt"
    g = Graph.new
    g.load(filename)

    assert_equal(filename, g.filename)
    assert_equal(4, g.nodes.count)
    assert_equal(0, g.arcs.count)
    assert_equal(0, g.cangotos.count)
  end

  def test_load_grafo1
    filename = "data/grafo1.txt"
    g = Graph.new
    g.load(filename)

    assert_equal(filename, g.filename)
    assert_equal(7, g.nodes.count)
    assert_equal(4, g.arcs.count)
    assert_equal(0, g.cangotos.count)
  end

  def test_load_grafo2
    filename = "data/grafo2.txt"
    g = Graph.new
    g.load(filename)

    assert_equal(filename, g.filename)
    assert_equal(7, g.nodes.count)
    assert_equal(5, g.arcs.count)
    assert_equal(0, g.cangotos.count)
  end
end