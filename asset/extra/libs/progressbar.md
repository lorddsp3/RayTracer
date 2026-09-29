### `progressbar()`

- **Purpose:** Default constructor.
- **What it does:** Initializes an empty progress bar with default values (`progress = 0`, `n_cycles = 0`, `last_perc = -1`).
- **When to use:** When you declare the progress bar before knowing the total loop count. You must call `set_niter()` before updating.

```cpp
progressbar bar;
bar.set_niter(100);

```

---

### `progressbar(int n)`

- **Purpose:** Parameterized constructor.
- **What it does:** Directly sets the total number of iterations or loop cycles (`n_cycles = n`).
- **When to use:** When you know the exact total count at the moment of creating the bar.

```cpp
progressbar bar(500); // 500 total steps

```

---

### `void set_niter(int iter)`

- **Purpose:** Sets the total number of iterations.
- **Parameters:** `iter` — Total number of steps/cycles expected.
- **What it does:** Updates `n_cycles`. Throws an error (`std::invalid_argument`) if `iter` is 0 or negative.
- **When to use:** If you used the default constructor `progressbar()`, call this before starting your loop.

```cpp
bar.set_niter(1000);

```

---

### `void reset()`

- **Purpose:** Resets the progress bar back to its starting state.
- **What it does:** Sets `progress` back to `0` and `last_perc` back to `-1`.
- **When to use:** When reusing the same progress bar instance for multiple tasks or loops sequentially.

```cpp
bar.reset();
bar.set_niter(200);

```

---

### `void update()`

- **Purpose:** Advances the progress bar by one step and updates the terminal display.
- **What it does:**

1. Calculates the current percentage completed based on `progress` and `n_cycles`.
2. Compares the current percentage with `last_perc`. If it hasn't changed, it skips redrawing (preventing terminal lag).
3. Uses `\r` to reset the cursor to the start of the line and renders the updated `{#####----}` visual alongside the percentage.
4. Increments the `progress` counter.
5. Automatically prints a new line (`\n`) once `progress` reaches `n_cycles`.

- **When to use:** Call this once inside your loop on every iteration.

```cpp
for (int i = 0; i < total; ++i) {
    // perform your work here
    bar.update();
}

```

---

### Example code

```
#include <iostream>
#include <thread>
#include <chrono>

#include "asset/extra/libs/progressbar.hpp"

int main() {

    int N = 10000;

    progressbar bar(N);
    std::cerr << std::endl;

    N = 5000;
    bar.set_niter(N);
    bar.reset();
    for ( int i = 0; i < N; i++ ) {

        bar.update();

        // the program...
        std::this_thread::sleep_for( std::chrono::microseconds(300) );
    }

    std::cerr << std::endl;
    bar.reset();
    return 0;
}
```

---
