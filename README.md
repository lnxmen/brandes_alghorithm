# Optimizations:
## 1.0 https://github.com/lnxmen/brandes_alghorithm/tree/1.0
First fully working code version.
- 2 - 3m 41.62s
- 4 - 1m 56.61s
- 8 - 1m 29.05s

## 1.1 https://github.com/lnxmen/brandes_alghorithm/tree/1.1
Change: keep final (and temporary for single vertex computation) result counters in unordered_map instead of map.
- 2 - 2m 49.14s
- 4 - 1m 43.60s
- 8 - 1m 17.46s

### Used CPU:
```
Model: Intel(R) Core(TM) i7-2820QM CPU @ 2.30GHz
BogoMIPS:              4590.66
```