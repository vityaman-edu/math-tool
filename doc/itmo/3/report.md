# Лабораторная работа 3: Численное интегрирование

## Введение

|         |     |
| ------- | --- |
| Вариант | 17  |

## Вычислительная часть

|          |                                |
| -------- | ------------------------------ |
| Функция  | $3 x ^ 3 - 4 x ^ 2 + 7 x - 17$ |
| Интервал | [1, 2]                         |

### Вычисление вручную

$$f(x) = 3 x ^ 3 - 4 x ^ 2 + 7 x - 17$$

$$\int f(x) =$$

$$3 x ^ 3 - 4 x ^ 2 + 7 x - 17 =$$

$$\frac{3x^4}{4}-\frac{4x^3}{3} + \frac{7x^2}{2} - 17x + const$$

$$F(x) = \frac{3x^4}{4}-\frac{4x^3}{3} + \frac{7x^2}{2} - 17x$$

$$\int_{1}^{2}f(x) = F(2) - F(1) = -\frac{55}{12} = -4.583(3)$$

### Вычисление по формуле Ньютона-Котеса при n = 5

```bash
$ math-tool integrator cotes5 1 2 0.0001
6
Report
Taken method: Cotes n = 5
Scope: [1.000000, 2.000000]
Accuracy: 0.0001
Result: -4.58341
```

| n   | size  | prev     | curr     | diff        |
| --- | ----- | -------- | -------- | ----------- |
| 1   | 8     | -4.92739 | -4.75271 | 0.174676    |
| 2   | 16    | -4.75271 | -4.66735 | 0.0853653   |
| 3   | 32    | -4.66735 | -4.62517 | 0.0421784   |
| 4   | 64    | -4.62517 | -4.60421 | 0.0209617   |
| 5   | 128   | -4.60421 | -4.59376 | 0.0104488   |
| 6   | 256   | -4.59376 | -4.58854 | 0.00521638  |
| 7   | 512   | -4.58854 | -4.58594 | 0.00260618  |
| 8   | 1024  | -4.58594 | -4.58464 | 0.00130259  |
| 9   | 2048  | -4.58464 | -4.58398 | 0.000651167 |
| 10  | 4096  | -4.58398 | -4.58366 | 0.000325552 |
| 11  | 8192  | -4.58366 | -4.5835  | 0.000162768 |
| 12  | 16384 | -4.5835  | -4.58341 | 8.13822e-05 |

### Вычисление методом средних прямоугольников

```bash
$ math-tool integrator rect-m 1 2 0.0001
6
Report
Taken method: Rectangle Middle
Scope: [1.000000, 2.000000]
Accuracy: 0.0001
Result: -4.58335
```

| n   | size | prev     | curr     | diff        |
| --- | ---- | -------- | -------- | ----------- |
| 1   | 8    | -4.63281 | -4.5957  | 0.0371094   |
| 2   | 16   | -4.5957  | -4.58643 | 0.00927734  |
| 3   | 32   | -4.58643 | -4.58411 | 0.00231934  |
| 4   | 64   | -4.58411 | -4.58353 | 0.000579834 |
| 5   | 128  | -4.58353 | -4.58338 | 0.000144958 |
| 6   | 256  | -4.58338 | -4.58335 | 3.62396e-05 |

### Вычисление по формуле Трапеций

```bash
$ math-tool integrator trapeze 1 2 0.0001
6
Report
Taken method: Trapeze
Scope: [1.000000, 2.000000]
Accuracy: 0.0001
Result: -4.58331
```

| n   | size | prev     | curr     | diff        |
| --- | ---- | -------- | -------- | ----------- |
| 1   | 8    | -4.48438 | -4.55859 | 0.0742188   |
| 2   | 16   | -4.55859 | -4.57715 | 0.0185547   |
| 3   | 32   | -4.57715 | -4.58179 | 0.00463867  |
| 4   | 64   | -4.58179 | -4.58295 | 0.00115967  |
| 5   | 128  | -4.58295 | -4.58324 | 0.000289917 |
| 6   | 256  | -4.58324 | -4.58331 | 7.24792e-05 |

### Вычисление по формуле Симпсона

```bash
$ math-tool integrator simpson 1 2 0.0001
6
Report
Taken method: Simpson
Scope: [1.000000, 2.000000]
Accuracy: 0.0001
Result: -4.58333
```

| n   | size | prev     | curr     | diff        |
| --- | ---- | -------- | -------- | ----------- |
| 1   | 8    | -4.58333 | -4.58333 | 1.77636e-15 |

### Функция с разрывом - расходящийся интеграл

```bash
$ math-tool integrator simpson -1 2 0.0001
7
Report
Taken method: Simpson
Scope: [-1.000000, 2.000000]
Accuracy: 0.0001
No result: Can't integrate given function, maybe it diverges in given interval
```

| n   | size    | prev     | curr     | diff    |
| --- | ------- | -------- | -------- | ------- |
| 1   | 8       | 3.71662  | -2.32982 | 6.04644 |
| 2   | 16      | -2.32982 | 3.71615  | 6.04596 |
| 3   | 32      | 3.71615  | -2.32985 | 6.046   |
| 4   | 64      | -2.32985 | 3.71615  | 6.046   |
| 5   | 128     | 3.71615  | -2.32985 | 6.046   |
| 6   | 256     | -2.32985 | 3.71615  | 6.046   |
| 7   | 512     | 3.71615  | -2.32985 | 6.046   |
| 8   | 1024    | -2.32985 | 3.71615  | 6.046   |
| 9   | 2048    | 3.71615  | -2.32985 | 6.046   |
| 10  | 4096    | -2.32985 | 3.71615  | 6.046   |
| 11  | 8192    | 3.71615  | -2.32985 | 6.046   |
| 12  | 16384   | -2.32985 | 3.71615  | 6.046   |
| 13  | 32768   | 3.71615  | -2.32985 | 6.046   |
| 14  | 65536   | -2.32985 | 3.71615  | 6.046   |
| 15  | 131072  | 3.71615  | -2.32985 | 6.046   |
| 16  | 262144  | -2.32985 | 3.71615  | 6.046   |
| 17  | 524288  | 3.71615  | -2.32985 | 6.046   |
| 18  | 1048576 | -2.32985 | 3.71615  | 6.046   |
| 19  | 2097152 | 3.71615  | -2.32985 | 6.046   |
| 20  | 4194304 | -2.32985 | 3.71615  | 6.046   |

```bash
[vityaman@vityaman math-tool]$ ./build/math-tool integrator simpson 0 2 0.0001
7
Report
Taken method: Simpson
Scope: [0.000000, 2.000000]
Accuracy: 0.0001
No result: Can't integrate given function, maybe it diverges in given interval
```

| n   | size    | prev | curr | diff |
| --- | ------- | ---- | ---- | ---- |
| 1   | 8       | inf  | inf  | nan  |
| 2   | 16      | inf  | inf  | nan  |
| 3   | 32      | inf  | inf  | nan  |
| 4   | 64      | inf  | inf  | nan  |
| 5   | 128     | inf  | inf  | nan  |
| 6   | 256     | inf  | inf  | nan  |
| 7   | 512     | inf  | inf  | nan  |
| 8   | 1024    | inf  | inf  | nan  |
| 9   | 2048    | inf  | inf  | nan  |
| 10  | 4096    | inf  | inf  | nan  |
| 11  | 8192    | inf  | inf  | nan  |
| 12  | 16384   | inf  | inf  | nan  |
| 13  | 32768   | inf  | inf  | nan  |
| 14  | 65536   | inf  | inf  | nan  |
| 15  | 131072  | inf  | inf  | nan  |
| 16  | 262144  | inf  | inf  | nan  |
| 17  | 524288  | inf  | inf  | nan  |
| 18  | 1048576 | inf  | inf  | nan  |
| 19  | 2097152 | inf  | inf  | nan  |
| 20  | 4194304 | inf  | inf  | nan  |

## Анализ

Начнем со случая, когда функция терпит разрыв в
точке на интервале. Если несобственный интеграл
расходится, то его интеграл стремится к бесконечности,
поэтому при каждом новом приближении мы получаем все большее
и большее число в результате, поэтому я просто
ограничил количество интераций 20ю, и если это кол-во
превышено кидаю ошибку.

В целом, сразу видно, насолько хорош Симпсон, хотя
это на самом деле из-за того, что наша исходная функция
является полиномом 4ой степени и данный метод своими
приближениями очень точно подходит под данную модель.

Метод трапеции и прямоугольников работают примерно одинаково.
А вот формула Ньютона-Котеса при n = 5 расстроила - не
стоила она потраченных сил. А все почему? Потому что
интерполяционные многочлены подвели.

## Программная реализация

```c++

template <typename T>
using TrivialMethod = std::function<T(Function<T>, Interval<T>)>;

template <typename T>
using Method = std::function<T(Function<T>, Partition<T>)>;

template <typename T>
using PointPeeker = std::function<T(Interval<T>)>;

template <typename T>
TrivialMethod<T> trivial0(PointPeeker<T> peek) noexcept {
  return [peek](auto f, auto interval) {
    return f(peek(interval)) * interval.length();
  };
}

template <typename T>
TrivialMethod<T> trivial1() noexcept {
  return [](auto f, auto interval) {
    auto left = f(interval.left());
    auto right = f(interval.right());
    return (left + right) / 2 * interval.length();
  };
}

template <typename T>
TrivialMethod<T> trivial2() noexcept {
  return [](auto f, auto interval) {
    auto a = interval.left();
    auto b = interval.right();
    return (b - a) / 6 * (
        + 1 * f(a) 
        + 4 * f((a + b) / 2) 
        + 1 * f(b)
    );
  };
}

template <typename T>
TrivialMethod<T> trivial5() noexcept {
  return [](auto f, auto interval) {
    const auto s = interval.left();
    const auto l = interval.length() / 6;
    return interval.length() / 288 * (                     
        + 19 * f(s + 0 * l)
        + 75 * f(s + 1 * l) 
        + 50 * f(s + 2 * l) 
        + 50 * f(s + 3 * l) 
        + 75 * f(s + 4 * l) 
        + 19 * f(s + 5 * l) 
    );
  };
}

template <typename T>
class Cotes {
public:
  explicit Cotes(TrivialMethod<T> trivial)
      : trivialAreaUnderGraph(trivial) {}

  T areaUnderGraph(Function<T> function, Partition<T> partition) noexcept {
    T sum = 0;
    for (auto interval : partition) {
      sum += trivialAreaUnderGraph(function, interval);
    }
    return sum;
  }

private:
  TrivialMethod<T> trivialAreaUnderGraph;
};

template <typename T>
class Approx {
public:
  explicit Approx(T epsilon, Cotes<T> cotes)
      : epsilon(epsilon), cotes(cotes) {}

  T integrate(Function<T> f, Interval<T> scope) {
    auto size = 4;

    auto prev = cotes.areaUnderGraph(f, Partition<T>(scope, size));
    for (Index i = 0; i < iterationsLimit; i++) {
      size *= 2;

      auto curr = cotes.areaUnderGraph(f, Partition<T>(scope, size));

      if (std::abs(prev - curr) < epsilon) {
        return curr;
      }

      prev = curr;
    };
    throw Error::ProcessDiverges(
        "Can't integrate given function, "
        "maybe it diverges in given interval"
    );
  }

private:
  Count iterationsLimit = 20;
  T epsilon;
  Cotes<T> cotes;
};
```

## Вывод

Выполняя данную лабораторную работу я познакомился с
основными численными методами интегрирования.

Интегрирование - вычислительно сложная задача, то есть
для нее требуется много ресурсов. Для сильно скачущих
функциях требуются довольно мелкое разбиение из-за
чего колчество итераций сильно возрастает. Кроме того
мы увеличиваем количество этих итераций при каждой неудаче.

С расходящимися интегралами могут быть проблемы: мы можем
попытаться вычислить значение функции на интервале, на котором
она не определена и получить Undefined Behaviour, а если она
будет просто стремится к бесконечности на заданном интервале,
мы просто потратим много сил на вычисление и в конце-концов 
сдадимся.
