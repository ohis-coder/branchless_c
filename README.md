# branchless_c 

**High-performance, deterministic bitwise primitives in pure C.**

`branchless_c` is a collection of mathematical kernels designed to eliminate conditional branching (`if/else`, `ternary`) in performance-critical execution paths. By replacing jumps with data-dependency masks, these primitives ensure a saturated CPU pipeline and zero branch-misprediction penalties.

---

##  The Philosophy: Determinism over Speculation

Modern CPUs use sophisticated branch predictors to "guess" the path of your code. When data is random—such as filtering 100k+ mechanical parts in **Mechswift**—the predictor fails.

* **The Cost:** A single misprediction can cost **15–20 clock cycles** as the pipeline flushes.
* **The Solution:** Branchless logic converts control-flow into data-flow. The latency is constant ($O(1)$), regardless of the input distribution.

---

##  Implementation Highlights

### 1. The Multiplexer (MUX) Pattern
Instead of a jump, we use a "Ghost" (XOR) and a "Wall" (Mask) to select values.
```c
// Returns b if flag is 1, else returns a
int select_branchless(int a, int b, int flag) {
    int mask = -flag; // Creates a 'Wall' of 0xFFFFFFFF or 0x00000000
    return a ^ ((a ^ b) & mask);
}
```
2. Branchless Absolute Value

Utilizes the sign-bit to perform a conditional Two's Complement negation without a comparison.

```
int abs_branchless(int x) {
    int mask = x >> 31; // All 1s for negative, 0s for positive
    return (x ^ mask) - mask;
}
```
3. The "Lonely Bit" (Power of Two)

A binary cascade trick used in high-speed memory allocators to verify alignment and power-of-two constraints.
```
int is_power_of_two(int x) {
    return (x > 0) && ((x & (x - 1)) == 0);
}
```

4. Branchless Maximum

Comparing two values and returning the largest without a single jump instruction.
```
int max_branchless(int a, int b) {
    return a ^ ((a ^ b) & (-(a < b)));
}
```

5. Branchless Priority Filter
A "best-fit" allocator that selects the smallest possible memory bucket (10KB, 30KB, 50KB) for a given input size without using a single jump. It uses a "Waterfall" pattern where the data "falls" into the smallest fit via bitwise masks.
```
int current_selection = s3;
	
	int s2_mask = (s2 - x) >> 31;
	current_selection ^= (current_selection ^ s2) & ~s2_mask;
	int s1_mask = (s1 - x) >> 31;
	current_selection ^= (current_selection ^ s1) & ~s1_mask;
```

6. Branchless Advanced Example w Cartesisan Products: Branchless Rules Engine for Mechanic Booking.
Instead of storing a 3×4 lookup table in memory or using if/switch, we pack the entire permission matrix into a single 16-bit integer and do a branchless lookup. This pattern scales beautifully for high-frequency matching systems.
```
uint16_t ruleset = (0b0011 << 8) |  // Night rules
				   (0b1110 << 4) |  // Afternoon rules
 			       (0b1110 << 0);   // Morning rules; 
```

Performance & Use Cases
Feature	- Benefit
Zero Branching - Prevents CPU pipeline stalls on random data.
Constant Time	- Critical for cryptographic and real-time systems.
SIMD Ready	- These patterns are easily vectorized for massive throughput.

Targeted Applications:

Real-time Search Engines: High-speed filtering in the Mechswift parts engine.

Graphics/Games: Fast bounding-box and collision detection logic.

Embedded Systems: Maximizing cycles on low-power hardware.

gcc -O3 main.c -o branchless_test
./branchless_test

Developed during a 2 AM deep-dive into Computer Architecture and Discrete Mathematics.
