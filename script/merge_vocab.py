with open("vocab/Rust/node_type/txl_old.txt","r") as f:
    old_nodes = f.readlines()

with open("vocab/Rust/node_type/txl_new.txt","r") as f1:
    new_nodes = f1.readlines()

nodes = old_nodes + new_nodes
nodes = list(set(nodes))

with open("vocab/Rust/node_type/txl.txt", "w") as f2:
    for n in nodes:
        n = n.replace("<", "").replace(">", "").replace("/", "")
        f2.write(n.upper())