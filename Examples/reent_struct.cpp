// Debugged

#def_module(struct) tree_node(ID, Type, Name, Arity) {
  @goal:-brackets_off.
  @goal:-write(ID). {
    @goal:-write(Type),write(' '),write(Name),write(';').
    @refs(2):-write('struct '),write(ID),write(' * Left;'),
             write('struct '),write(ID),write(' * Right;'),
             !.
    @refs(N):-write('struct '),write(ID),write(' * Children['),write(N),write('];'),!.
    @goal:-refs(Arity).
  }
};

tree_node('node2', 'int', 'Data', 2);
tree_node('node4', 'int', 'Data', 4);

int main() {
  struct node2 BinLeaf;
  struct node4 QuadLeaf;

  BinLeaf.Data = 1;
  BinLeaf.Left = NULL;
  BinLeaf.Right = NULL;

  QuadLeaf.Data = 2;
  for (int i = 0; i < 4; i++)
      QuadLeaf.Children[i] = NULL;

  return 0;
}