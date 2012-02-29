module SimplerTiles
  # The Layer object contains connection info for a particular datasource and
  # tracks a list of {Query}s.
  class Layer
    include SimplerTiles::PP

    # Initialize a Layer
    def initialize(source)
      self.source = source
      yield self if block_given?
    end

    # Add a query to this Layer's c list.
    def query(sql, &blk)
      layer = SimplerTiles::Query.new(sql, &blk)
      add_query layer
    end

  private

    def inspect_attributes
      [:source]
    end
  end
end
