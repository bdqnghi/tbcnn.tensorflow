List<T> mergeSort(List<T> list) {
  int size = list.size();
  if (list.size() > 1) {
    List<T> left = mergeSort(list.subList(0, (size / 2) - 1));
    List<T> right = mergeSort(list.subList(size / 2, size - 1);
    return merge(left, right);
  }
  return list;
}

List<T> merge(List<T> left, List<T> right) {
  List<T> merged = new List<T>();
  while (!left.isEmpty() && !right.isEmpty()) {
    if (left.get(0) < right.get(0)) {
      merged.add(left.get(0));
      left.remove(0);
    } else {
      merged.add(right.get(0));
      right.remove(0);
    }
  }
  merged.addAll(left);
  merged.addAll(right);
  return merged;
}
