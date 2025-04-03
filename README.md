## 🔹 RLE Compression Overview

This is a small yet efficient **RLE (Run-Length Encoding)** implementation designed for **coarse-data compression**, particularly suitable for **flash binary files**.

---

### 📁 Input & Output

- Given an input file named **`input.bin`**, the executable will generate:
  - **`compress.bin`** – the compressed version of the input.
  - **`decompress.bin`** – the decompressed result, which should be **identical to `input.bin`**.

---

### ⚙️ Compression Details

- Compression is performed at the **byte level**.
- The maximum compression bandwidth for one run is **255 (0xFF)** consecutive identical bytes.

---

### 📌 Example with Annotations

- **input.bin:**  
  `0x1A` `0x1A` `0x1A` `0x1A` `0x1B` `0x1C` `0x1D` `0x1A` `0x1A` `0x1F` `0x55` `0x77` `0x55` `0x55` ... `0x55`

- **compress.bin:**  
  `0x1A` `0x1A` **`0x02`** `0x1B` `0x1C` `0x1D` `0x1A` `0x1A` **`0x00`** `0x1F` `0x55` `0x77` `0x55` `0x55` **`0xFD`**

- **explanation:**  
  `0x1A` `0x1A` **`0x02`**  
  → Represents 4 consecutive `0x1A` bytes (`0x02` means 2 additional repeats beyond the first two)

  `0x1B` `0x1C` `0x1D`  
  → Non-repeated bytes are stored as-is (no compression applied)

  `0x1A` `0x1A` **`0x00`**  
  → Only 2 `0x1A` bytes; `0x00` indicates no additional repetition (just the two)

  `0x1F`  
  → A single non-repeating byte; stored directly

  `0x55` `0x77` `0x55` `0x55` ... `0x55`  
  → Ends with a long run of repeated `0x55` bytes

  **`0xFD`**  
  → Indicates 253 additional `0x55` bytes after the first two → total of 255 `0x55` bytes
