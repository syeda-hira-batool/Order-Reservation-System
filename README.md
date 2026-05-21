~ Order Reservation System


~ Overview:

This project was developed as the final submission for a Programming Fundamentals course. Written entirely in C, it implements a working restaurant order system where customers register, browse a fixed menu, place and manage orders, and receive a calculated bill — all through a text-based console interface. Data is persisted across sessions using file handling.

~ Features:

- Customer registration (name, email, phone number)
- Randomised order ID generation using `srand` / `rand`
- Interactive menu with 10 food items
- Place order with multiple items
- View current order
- Search any order by Order ID
- Modify an existing order by Order ID
- Cancel an order by Order ID (uses a temp file swap)
- Bill calculation with recursive summation
- Delivery option (+50 RS charge) or free Pickup
- Multi-customer loop — system stays open for the next customer

---

~ Project Structure:

```
Order-Reservation-System/
│
├── Code_Snippet.c     # Full program — all functions in one C file
├── OrderFile.txt      # Persistent order data (auto-created on first run)
└── temp.txt           # Temporary file used during order cancellation/modification
```

~ Workflow:

1. **Register** — Enter your name, email, and phone number. A random Order ID is generated and saved.
2. **Place Order** — Choose how many items you want, then enter item numbers from the menu.
3. **View Order** — Optionally display the current session's order.
4. **Search Order** — Look up any order by its Order ID from the file.
5. **Change Order** — Replace an existing order's items by providing its Order ID.
6. **Calculate Bill** — Reads the latest order from file and sums prices recursively.
7. **Choose Delivery** — Pay +50 RS for home delivery, or choose free Pickup.
8. **Cancel Order** — Remove an order by ID using a temp file swap.
9. **Next Customer** — Loop back to the start for the next customer.



~ C Concepts Demonstrated:

| Concept | Where Used |
|---|---|
| **Functions** | Each feature is a separate function (`registration`, `Order`, `BillCalculation`, `Delivery`, etc.) |
| **File Handling** | `fopen`, `fgets`, `fprintf`, `fclose` for persistent read/write; `remove`/`rename` for cancellation |
| **Recursion** | `recursiveSum()` computes the total bill recursively over a price array |
| **Strings & `string.h`** | `strcmp`, `strncmp`, `strcat`, `strcpy`, `sscanf` for order searching and parsing |
| **Random Number Generation** | `srand(time(NULL))` + `rand()` to generate unique Order IDs |
| **Loops & Conditionals** | `while` loops for multi-item ordering and multi-customer sessions |
| **Arrays** | `price[]` array stores item prices for bill calculation |
| **Structs / Modular Design** | Procedural decomposition — each action is an independent, reusable function |

---

> This is the original procedural C version of the project. The OOP refactor in C++ is available at [Order-Reservation-System-with-OOP-concepts](https://github.com/syeda-hira-batool/Order-Reservation-System-with-OOP-concepts).
