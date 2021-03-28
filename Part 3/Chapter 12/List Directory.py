import os

search_path = os.path.abspath(os.path.dirname(os.path.dirname(os.path.dirname(__file__))))
search_path_len = len(search_path.split(os.sep))

for root, dirs, files in os.walk(search_path):
    path = root.split(os.sep)
    print((len(path) - search_path_len) * '--', os.path.basename(root), sep="")
    for file in files:
        print((len(path) - search_path_len + 1) * '--', file, sep="")