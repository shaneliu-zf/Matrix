# Matrix 矩陣

## 宣告
1. 設定列數、行數，a為對角線上每一元素之初始值，其餘皆為0
```cpp
Matrix m(int row,int column，int a=0);
```
2. 直接載入二維vector
```cpp
Matrix m(std::vector<std::vector<double>> a);
```

## 取得資料
### 行數
```cpp
int ans = m.column();
```
### 列數
```cpp
int ans = m.row();
```
### 元素
```cpp
double ans = m[i][j];
```

## 運算

### 加法

```cpp
Matrix c = m1 + m2;
```

### 減法

```cpp
Matrix c = m1 - m2;
```

### 乘法
```cpp
Matrix c = m1 * m2;
```

### 反矩陣
```cpp
Matrix ans = inverse(m);
```
### 行列式
```cpp
double ans = det(m);
```
### 子行列式
```cpp
Matrix ans = cot(m,i,j);
```
### 轉置矩陣
```cpp
Matrix ans = T(m);
```
### 伴隨矩陣
```cpp
Matrix ans = adj(m);
```
### 餘子矩陣
```cpp
Matrix ans = T(adj(m));
```
