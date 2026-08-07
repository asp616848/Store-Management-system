# Store Management System

A console-based store inventory and accounts management system written in C++, built to practice object-oriented programming (inheritance, polymorphism, operator overloading) and core data structures (vectors, priority queues, file-backed persistence).

**Live demo / design overview:** https://ims0.my.canva.site/

## Overview

The system models a small store with two areas that a single running program switches between: an **Accounts** module (login, customers, sellers) and an **Inventory** module (products and stock). Data for both is persisted to disk as CSV, so state survives between runs.

## Features

**Accounts**
- Base `Account` class with username/password authentication, extended by `CustomerAccount` (has a balance and running expenditure) and `SellerAccount`/`MerchantAccount`.
- Create customer and seller accounts, log in, and route to role-specific menus.
- Customers can top up/update their balance; sellers can view all customers' balances.
- Account credentials and balances are obfuscated on disk with a Caesar-cipher-based `encrypt`/`decrypt` before being written to `users.csv`.
- "Highest spending users" report, computed with a `priority_queue` ordered by expenditure.

**Inventory**
- `Product` class (id, name, category, price, quantity, sales) with `operator<` support so products can be ranked.
- Add, remove, find, and update products by ID.
- View the full product catalog.
- Save/load the catalog to/from `inventory.csv`.
- "Most selling products" report via a `priority_queue` ordered by total units sold.
- Automatic **low-stock alert** on login/menu access when a product's quantity drops to 4 or fewer.

**Store / Checkout**
- `Store` ties accounts and inventory together and drives the two text menus (`run()` for accounts, `runInv()` for inventory).
- Logged-in customers can make purchases: pick a product by ID, choose a quantity (validated against available stock), add multiple items to a running cart, and check out — the purchase decrements stock, deducts the customer's balance, and updates the product's sales counter and the customer's total expenditure.
- Insufficient balance is detected and blocks the purchase.

## Tech stack

- **Language:** C++ (C++11 or later)
- **Standard library only:** `<vector>`, `<queue>` (`std::priority_queue`), `<fstream>`/`<sstream>` for CSV persistence, `<string>` — no external dependencies
- **Persistence:** plain CSV files (`users.csv`, `inventory.csv`) read/written next to the executable
- **Build tooling:** compiled directly with GCC/Clang (a VS Code `tasks.json`/`launch.json` is included for build-and-debug inside the editor)

## Project layout

```
multifile/
├── main.cpp          # entry point, chooses Accounts or Inventory flow
├── store.hpp/.cpp     # Store: menus, login, purchases, CSV persistence
├── accounts.hpp/.cpp  # Account / CustomerAccount / MerchantAccount
├── inventory.hpp/.cpp # Inventory: CRUD over products
├── product.hpp/.cpp   # Product model
├── users.csv          # persisted accounts (encrypted)
├── inventory.csv      # persisted product catalog
├── TestAccounts/      # sample manual test transcripts for the accounts flow
├── TestInventory/     # sample manual test transcripts for the inventory flow
└── EdgeCasesStore/    # notes on known edge cases
```

## Build & run

Requires a C++ compiler (g++ or clang++).

```bash
git clone https://github.com/asp616848/Store-Management-system.git
cd Store-Management-system/multifile

g++ main.cpp store.cpp inventory.cpp accounts.cpp product.cpp -o store
./store
```

On startup you'll be asked whether to enter the **Accounts** menu (`1`) or the **Inventory** menu (`0`); both stay in a loop until you quit (`Q`/`E`), at which point accounts and inventory are saved back to `users.csv` and `inventory.csv`.

## Status

This is a learning/portfolio project and is functionally complete for its original scope (accounts + inventory + purchasing flow), but is not hardened for production use — passwords are obfuscated with a simple Caesar cipher rather than a real hashing scheme, and there is no automated test suite (see `TestAccounts/` and `TestInventory/` for manual test transcripts).

## Contributing

Bug reports and pull requests are welcome — open an issue or PR with suggested improvements.
