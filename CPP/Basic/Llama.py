def dfs_path(graph, src, des):
    visited = set()
    stack = list([src])
    path = list()
    while stack:
        cur = stack.pop()
        visited.add(cur)
        path.add(cur)
        if cur == src:
            return path
        for node in graph[cur]:
            if node not in visited:
                stack.append(node)
    return []

if __name__ == "__main__":
    graph = {0: [1, 2, 3], 1: [0, 4], 2: [0], 3: [0, 5], 4: [1], 5: [3]}
    print(dfs_path(graph, 0, 5))
