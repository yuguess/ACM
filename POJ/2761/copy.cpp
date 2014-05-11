
int find_kth(int k) {
  int ans = 0, cnt = 0, i;
  for (i = 20; i >= 0; i--) {
    ans += (1 << i);
    if (ans >= MAXN || cnt + c[ans] >= k)
      ans -= (1 << i);
    else
      cnt += c[ans];
  }

  return ans + 1;
}
