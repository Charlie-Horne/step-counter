#!/usr/bin/env python3
"""
Generate a dependency graph for C source files in the Core folder,
ignoring files starting with 'stm' and specific peripheral modules.
The graph starts from module 'app', ignores self-dependencies, and
groups provided modules in a distinct cluster. Supports customizing
aspect ratio and size.
Outputs a Graphviz DOT file and PNG if graphviz is installed.
"""
import os
import re
import sys
try:
    from graphviz import Digraph
except ImportError:
    print("Please install graphviz: pip install graphviz", file=sys.stderr)
    sys.exit(1)

# Configuration
CORE_DIR = 'Core'
EXCLUDE_PREFIX = 'stm'
EXCLUDE_MODULES = {'adc', 'dma', 'gpio', 'i2c', 'spi', 'tim', 'usart'}
PROVIDED_MODULES = EXCLUDE_MODULES.copy()
ENTRY_MODULE = 'app'
INCLUDE_PATTERN = re.compile(r'#include\s+"([^\"]+)"')
# Graph layout customization
GRAPH_SIZE = '20,25!'  # width,height in inches, '!' to enforce
ASPECT_RATIO = 'auto'  # options: 'auto', 'compress', 'fill', or float string


def find_source_files(core_dir):
    """Walk Core folder and collect .c and .h files not matching exclusion rules."""
    files = {}
    for root, _, filenames in os.walk(core_dir):
        for fname in filenames:
            if not fname.endswith(('.c', '.h')):
                continue
            module = os.path.splitext(fname)[0]
            if module.startswith(EXCLUDE_PREFIX) or module in EXCLUDE_MODULES:
                continue
            path = os.path.join(root, fname)
            files[module] = path
    return files


def parse_includes(file_path):
    """Return a list of included module names from local includes in a file, excluding unwanted modules."""
    deps = []
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            for line in f:
                m = INCLUDE_PATTERN.search(line)
                if m:
                    included = os.path.splitext(os.path.basename(m.group(1)))[0]
                    if included.startswith(EXCLUDE_PREFIX) or included in EXCLUDE_MODULES:
                        continue
                    deps.append(included)
    except FileNotFoundError:
        pass
    return deps


def build_graph(files):
    """Build a dependency graph: module -> list of dependent modules, excluding self-dependencies."""
    graph = {}
    for mod, path in files.items():
        deps = parse_includes(path)
        graph[mod] = [d for d in deps if d != mod]
    return graph


def traverse_deps(graph, start):
    """Return set of reachable modules from start via DFS."""
    visited = set()
    stack = [start]
    while stack:
        node = stack.pop()
        if node not in visited and node in graph:
            visited.add(node)
            stack.extend(graph[node])
    return visited


def render_graph(graph, reachable, output='dependency_graph'):
    """Render the dependency graph (reachable subset) to DOT and PNG with custom aspect ratio and size."""
    dot = Digraph(comment='Dependency Graph')
    # Apply layout options
    dot.attr(size=GRAPH_SIZE, ratio=ASPECT_RATIO)

    # Cluster: Provided Modules
    with dot.subgraph(name='cluster_provided') as c:
        c.attr(label='Provided Modules', style='filled', color='lightgrey')
        for mod in PROVIDED_MODULES:
            if mod in reachable:
                c.node(mod)

    # Add other nodes
    for node in reachable:
        if node in PROVIDED_MODULES:
            continue
        style = {'color': 'red', 'style': 'filled'} if node == ENTRY_MODULE else {}
        dot.node(node, **style)

    # Add edges
    for src in reachable:
        for dst in graph.get(src, []):
            if dst in reachable:
                dot.edge(src, dst)

    # Output files
    dot.render(output, view=False, format='png')
    print(f"Generated {output}.png and {output}.gv")


def main():
    files = find_source_files(CORE_DIR)
    if ENTRY_MODULE not in files:
        print(f"Error: Entry module '{ENTRY_MODULE}' not found in {CORE_DIR}", file=sys.stderr)
        sys.exit(1)

    graph = build_graph(files)
    for ex in EXCLUDE_MODULES:
        graph.pop(ex, None)

    reachable = traverse_deps(graph, ENTRY_MODULE)
    render_graph(graph, reachable)

if __name__ == '__main__':
    main()
